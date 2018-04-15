#ifndef ABSTRACT_CLASS_CACHE
#define ABSTRACT_CLASS_CACHE

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "Cache/CacheRP.hh"
#include "TraceLine/TraceLine.hh"
class CacheLRU;

class Cache {
 protected:
  //! Vector of actions done on the cache is the representation of the Trace.
  std::vector<TraceLine> TraceLines;

  // CACHE PROPERTIES

  //! Size of the cache.
  unsigned int size;

  //! Assicuativity of the cache.
  unsigned int associativity;

  //! Block size of the cache.
  unsigned int blockSize;

  //! Replacement Policy of the cache.
  CacheRP cacheRP;

  //! Penalty cycles when a miss occurs.
  unsigned int missPenalty;

  // RESULTS

  //! Simulation results: heightExecution time(cycles)
  unsigned int simResults;

  //! Instructions
  unsigned int instructions;

  //! Memory accesses
  unsigned int memAccesses;

  //! Overall miss rate
  float missRate;

  //! Read miss rate
  float RdMissRate;

  //! CPU time (cycles):
  float cpuTime;

  //! Average memory access time (cycles):
  float avgMemAccessTime;

  //! Dirty evictions:
  unsigned int dirtyEvictions;

  // Load misses:
  unsigned int loadMisses;

  // Store misses:
  unsigned int storeMisses;

  // Total misses:
  unsigned int totalMisses;

  // Load hits:
  unsigned int loadHits;

  // Store hits:
  unsigned int storeHits;

  // Total hits:
  unsigned int totalHits;

 public:
  ~Cache() { ; }

  //! Runs the tests on the cache with the given parameters and assign results.
  virtual void runTest() = 0;

  static Cache *makeCache(CacheRP cacheRP);
};

#endif