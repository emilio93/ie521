#ifndef CLASS_CACHE_SRRIP
#define CLASS_CACHE_SRRIP

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "Cache/Cache.hh"
#include "TraceFile/TraceFile.hh"

class CacheSRRIP : public Cache {
 public:
  //! Runs the tests on the cache with the given parameters and assign results.
  explicit CacheSRRIP(unsigned int size, unsigned int associativity,
                    unsigned int blockSize, CacheRP cacheRP,
                    unsigned int missPenalty, TraceFile* tfr);

  void access(TraceLine* traceLine);
};

#endif
