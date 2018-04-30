#ifndef CLASS_CACHE_RANDOM
#define CLASS_CACHE_RANDOM

#include <iostream>
#include <iterator>
#include <random>
#include <regex>
#include <string>
#include <vector>

#include "Cache/Cache.hh"
#include "Cache/CacheRP.hh"
#include "TraceFile/TraceFile.hh"
#include "TraceLine/TraceLine.hh"

class CacheRandom : public Cache {
 private:
  std::random_device r;
  std::default_random_engine randEl;

  //! Provides random number generation.
  std::uniform_int_distribution<int> uniformDist;

 public:
  //! Runs the tests on the cache with the given parameters and assign results.
  explicit CacheRandom(unsigned int size, unsigned int associativity,
                    unsigned int blockSize, CacheRP cacheRP,
                    unsigned int missPenalty, float cycMult, TraceFile* tfr);

  //! Single memory access implemented to satisfy random rp.
  void access(TraceLine* traceLine);
};

#endif
