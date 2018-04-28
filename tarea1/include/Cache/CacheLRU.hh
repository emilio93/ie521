#ifndef CLASS_CACHE_LRU
#define CLASS_CACHE_LRU

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "Cache/Cache.hh"

class CacheLRU : public Cache {
 public:
  //! Runs the tests on the cache with the given parameters and assign results.
  void runTest();
  explicit CacheLRU(unsigned int size, unsigned int associativity,
                    unsigned int blockSize, CacheRP cacheRP,
                    unsigned int missPenalty);
};

#endif
