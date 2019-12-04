#include "cache-sim.h"

#include "memalloc.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

//itoa() implementation
//char *itoa(int value, char *buffer, int base)
//returns a string of the value converted to a different base
//---------------------------------------------------------
void swap(char *x, char *y) {
        char t = *x; *x = *y; *y = t;
}

char* reverse(char *buffer, int i, int j)
{
        while (i < j)
                swap(&buffer[i++], &buffer[j--]);
        return buffer;
}

char* itoa(int value, char* buffer, int base)
{
        if (base < 2 || base > 32)
                return buffer;
        int n = abs(value);
        int i = 0;
        while (n)
        {
                int r = n % base;
                if (r >= 10)
                        buffer[i++] = 65 + (r - 10);
                else
                        buffer[i++] = 48 + r;
                n = n / base;
        }
        if (i == 0)
                buffer[i++] = '0';
        if (value < 0 && base == 10)
                buffer[i++] = '-';
        buffer[i] = '\0';
        return reverse(buffer, 0, i - 1);
}
//---------------------------------------------------------

typedef struct CacheSimImpl {
        int **arr;
        unsigned s;
        unsigned S;
        unsigned E;
        unsigned b;
        unsigned t;
        unsigned m;
        Replacement replacement;
} CacheSim;

/** Create and return a new cache-simulation structure for a
 *  cache for main memory withe the specified cache parameters params.
 *  No guarantee that *params is valid after this call.
 */
CacheSim *
new_cache_sim(const CacheParams *params)
{
        CacheSim *cache = mallocChk(sizeof(CacheSim));

        cache->s = params->nSetBits;

        int S = 1;
        for(int i = 0; i < params->nSetBits; i++)
                S = S * 2;
        cache->S = S;
        //initialize sets
        cache->arr = mallocChk(cache->S * sizeof(int *));

        cache->E = params->nLinesPerSet;
        for(int i = 0; i < cache->S; i++)
        {
                //initialize lines in each set
                cache->arr[i] = mallocChk(cache->E * sizeof(int));
                for(int j = 0; j < cache->E; j++)
                {
                        cache->arr[i][j] = 0;
                }
        }

        cache->b = params->nLineBits;
        cache->t = params->nMemAddrBits - (cache->b + cache->s);
        cache->m = params->nMemAddrBits;
        cache->replacement = params->replacement;

        return cache;
}

/** Free all resources used by cache-simulation structure *cache */
void
free_cache_sim(CacheSim *cache)
{
        for(int i = 0; i < cache->S; i++)
                free(cache->arr[i]);
        free(cache->arr);
        free(cache);
}

/** Return result for addr requested from cache */
CacheResult
cache_sim_result(CacheSim *cache, MemAddr addr)
{
        CacheResult cr;

        //expressed in bits, NOT bytes
        char *nonPaddedAddr = mallocChk(cache->m * sizeof(char) + 1);
        char *sAddr = mallocChk(100);
        strcpy(sAddr, "");
        itoa(addr, nonPaddedAddr, 2);

        for(int i = 0; i < cache->m; i++)
                if(nonPaddedAddr[i] != '1' && nonPaddedAddr[i] != '0')
                        strcat(sAddr, "0");
        strcat(sAddr, nonPaddedAddr);
        free(nonPaddedAddr);

        char *sTag = mallocChk(cache->t * sizeof(char) + 1);
        strncpy(sTag, sAddr, cache->t);

        char *sSet = mallocChk(cache->s * sizeof(char) + 1);
        strncpy(sSet, sAddr + cache->t, cache->s);

        char *end;
        int set = strtoul(sSet, &end, 2);

        char *sBlock = mallocChk((cache->t + cache->s) * sizeof(char) + 1);
        strncpy(sBlock, sAddr, (cache->t + cache->s));
        int block = strtoul(sBlock, &end, 2);

        free(sBlock);
        free(sSet);
        free(sTag);
        free(sAddr);

        //if cache hit---------------------------------------------------------------
        for(int i = 0; i < cache->E; i++)
        {
                if(cache->arr[set][i] == block)
                {
                        cr.status = 0;
                        cr.replaceAddr = 0;

                        //keeping track of LRU element
                        if(cache->replacement == LRU_R)
                        {
                                int size = cache->E - 1;
                                //check for non initialized cells
                                for(int j = i; j <= size; j++)
                                        if(cache->arr[set][j] == 0)
                                                size = j;
                                //rotate array left because LRU is always arr[0]
                                int temp = cache->arr[set][i];
                                for(int j = i; j < size; j++)
                                        cache->arr[set][j] = cache->arr[set][j + 1];
                                cache->arr[set][size] = temp;
                        }
                        else if(cache->replacement == MRU_R)
                        {
                                //swap with last index only
                                int temp = cache->arr[set][i];
                                cache->arr[set][i] = cache->arr[set][cache->E - 1];
                                cache->arr[set][cache->E - 1] = temp;
                        }
                        return cr;
                }
        }

        //if cache miss without replace, fill in blank line-------------------------
        for(int i = 0; i < cache->E; i++)
                if(cache->arr[set][i] == 0)
                {
                        cache->arr[set][i] = block;
                        cr.status = 1;
                        cr.replaceAddr = 0;
                        return cr;
                }

        //if cache miss with replace------------------------------------------------
        cr.status = 2;

        char *sReplacedAddr = mallocChk(cache->m * sizeof(char) + 1);
        char *blockOffsets = mallocChk(cache->b * sizeof(char) + 1);
        strcpy(blockOffsets, "");
        for(int i = 0; i < cache->b; i++)
                strcat(blockOffsets, "0");

        //LRU replacement strategy, use first index
        if(cache->replacement == LRU_R)
        {
                itoa(cache->arr[set][0], sReplacedAddr, 2);
                strcat(sReplacedAddr, blockOffsets);
                int replacedAddr = strtoul(sReplacedAddr, &end, 2);
                cr.replaceAddr = replacedAddr;

                cache->arr[set][0] = block;

                int size = cache->E - 1;
                int temp = cache->arr[set][0];
                for(int i = 0; i < size; i++)
                        cache->arr[set][i] = cache->arr[set][i + 1];
                cache->arr[set][size] = temp;
        }
        //MRU replacement strategy, use last index
        else if(cache->replacement == MRU_R)
        {
                itoa(cache->arr[set][cache->E - 1], sReplacedAddr, 2);
                strcat(sReplacedAddr, blockOffsets);
                int replacedAddr = strtoul(sReplacedAddr, &end, 2);
                cr.replaceAddr = replacedAddr;

                cache->arr[set][cache->E - 1] = block;
        }
        //random replacement strategy
        else if(cache->replacement == RANDOM_R)
        {
                int randLine = rand() % cache->E;
                itoa(cache->arr[set][randLine], sReplacedAddr, 2);
                strcat(sReplacedAddr, blockOffsets);
                int replacedAddr = strtoul(sReplacedAddr, &end, 2);
                cr.replaceAddr = replacedAddr;

                cache->arr[set][randLine] = block;
        }

        free(blockOffsets);
        free(sReplacedAddr);
        return cr;
}
