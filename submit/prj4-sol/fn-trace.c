#include "fn-trace.h"
#include "x86-64_lde.h"

#include "memalloc.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
  CALL_OP = 0xE8,
  RET_FAR_OP = 0xCB,
  RET_FAR_WITH_POP_OP = 0xCA,
  RET_NEAR_OP = 0xC3,
  RET_NEAR_WITH_POP_OP = 0xC2
};

static inline bool is_call(unsigned op) { return op == CALL_OP; }
static inline bool is_ret(unsigned op) {
  return
    op == RET_NEAR_OP || op == RET_NEAR_WITH_POP_OP ||
    op == RET_FAR_OP || op == RET_FAR_WITH_POP_OP;
}

typedef struct FnsData{
        FnInfo info;
} FnsData;

int findIt(FnsData arr[], void *address)
{
        for(int i = 0; i < 100; i++)
        {
                if(arr[i].info.address == address)
                {
                        return i;
                }
        }
        return -1;
}
FnInfo newFnInfo(void *address)
{
        FnInfo a =
        {
                address,
                0,
                1,
                0
        };
        return a;
}
int index = 0;

int comparator(const void *a, const void *b)
{
        if(((FnsData *)a)->info.address - ((FnsData *)b)->info.address < 0)
        {
                return -1;
        }
        else if(((FnsData *)a)->info.address - ((FnsData *)b)->info.address > 0)
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

const FnsData *
new_fns_data(void *rootFn)
{
        assert(sizeof(int) == 4);

        FnsData arr[100];
        for(int i = 0; i < 100; i++)
        {
                FnInfo something =
                {
                        0,
                        0,
                        0,
                        0
                };
                arr[i].info = something;
        }
        arr[0].info = newFnInfo(rootFn);
        unsigned char *cAddress = (unsigned char *)rootFn;
        void *nAddress;
        int counter = 0;
        for(int i = 0; i < 100; i++)
        {
                if(arr[i].info.nInCalls != 0)
                {
                        cAddress = (unsigned char *)arr[i].info.address;
                        while(true)
                        {
                                arr[i].info.length += get_op_length((void *)cAddress);
                                if(is_ret(*cAddress))
                                {
                                        break;
                                }
                                else if(is_call(*cAddress))
                                {
                                        arr[i].info.nOutCalls++;
                                        int *offset = (int *)(cAddress + 1);
                                        nAddress = (void *)(cAddress + 5 + *offset);

                                        if(findIt(arr, nAddress) == -1)
                                        {
                                                counter++;
                                                arr[counter].info = newFnInfo(nAddress);
                                        }
                                        else
                                        {
                                                arr[findIt(arr, nAddress)].info.nInCalls++;
                                        }
                                }
                                cAddress += get_op_length((void *)cAddress);
                        }
                }
        }
        qsort(arr, counter + 1, sizeof(FnsData), comparator);
        FnsData *ap = arr;
        return ap;
}

void
free_fns_data(FnsData *fnsData)
{
}

const FnInfo *
next_fn_info(const FnsData *fnsData, const FnInfo *lastFnInfo)
{
        lastFnInfo = &(fnsData[index].info);
        if(index < 100 && lastFnInfo->address != 0)
        {
                index++;
                return lastFnInfo;
        }
        else
        {
                return NULL;
        }
}
