#ifndef CLASS_CACHE_NRU
#define CLASS_CACHE_NRU

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "Cache/Cache.hh"

class CacheNRU : public Cache {
 public:
  //! Runs the tests on the cache with the given parameters and assign results.
  void runTest();
  explicit CacheNRU(unsigned int size, unsigned int associativity,
                    unsigned int blockSize, CacheRP cacheRP,
                    unsigned int missPenalty);

  static Cache* makeCache(unsigned int size, unsigned int associativity,
                          unsigned int blockSize, CacheRP cacheRP,
                          unsigned int missPenalty);
};

#endif
