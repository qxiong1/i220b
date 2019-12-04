#ifndef _CACHE_SIM_
#define _CACHE_SIM_

//.1
/** Opaque implementation */
typedef struct CacheSimImpl CacheSim;

/** Replacement strategy */
typedef enum {
  LRU_R,         /** Least Recently Used */
  MRU_R,         /** Most Recently Used */
  RANDOM_R       /** Random replacement */
} Replacement;

/** A primary memory address */
typedef unsigned long MemAddr;

/** Parameters which specify a cache.
 *  Must have nMemAddrBits > nLineBits >= 2.
 */
typedef struct {
  unsigned nSetBits;       /** Text notation: s; # of sets is 2**this */
  unsigned nLinesPerSet;   /** Text notation: E; # of cache lines/set */
  unsigned nLineBits;      /** Text notation: b; # of bytes/line is 2**this */
  unsigned nMemAddrBits;   /** Text notation: m; # of bits in primary mem addr;
                               total primary addr space is 2**this */
  Replacement replacement; /** replacement strategy */
} CacheParams;


/** Create and return a new cache-simulation structure for a
 *  cache for main memory with the specified cache parameters params.
 *  No guarantee that *params is valid after this call.
 */
CacheSim *new_cache_sim(const CacheParams *params);

/** Free all resources used by cache-simulation structure *cache */
void free_cache_sim(CacheSim *cache);

typedef enum {
  CACHE_HIT,                  /** address found in cache */
  CACHE_MISS_WITHOUT_REPLACE, /** address not found, no line replaced */
  CACHE_MISS_WITH_REPLACE,    /** address not found in cache, line replaced */
  CACHE_N_STATUS              /** # of status values possible */
} CacheStatus;

typedef struct {
  CacheStatus status;  /** status of requested address */
  MemAddr replaceAddr; /** address of replaced line if status is
                        *  CACHE_MISS_WITH_REPLACE */
} CacheResult;

/** Return result for addr requested from cache */
CacheResult cache_sim_result(CacheSim *cache, MemAddr addr);
//.2

#endif //ifndef _CACHE_SIM_
