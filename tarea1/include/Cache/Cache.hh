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
class CacheNRU;

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

  std::string toString();

  static Cache *makeCache(unsigned int size, unsigned int associativity,
                          unsigned int blockSize, CacheRP cacheRP,
                          unsigned int missPenalty);

  unsigned int getSize();
  unsigned int getAssociativity();
  unsigned int getBlockSize();
  CacheRP getCacheRP();
  unsigned int getMissPenalty();

  void setSize(unsigned int size);
  void setAssociativity(unsigned int associativity);
  void setBlockSize(unsigned int blockSize);
  void setCacheRP(CacheRP cacheRP);
  void setMissPenalty(unsigned int missPenalty);

  unsigned int getSimResults();
  unsigned int getInstructions();
  unsigned int getMemAccesses();
  float getMissRate();
  float getRdMissRate();
  float getCpuTime();
  float getAvgMemAccessTime();
  unsigned int getDirtyEvictions();
  unsigned int getLoadMisses();
  unsigned int getStoreMisses();
  unsigned int getTotalMisses();
  unsigned int getLoadHits();
  unsigned int getStoreHits();
  unsigned int getTotalHits();

  void setSimResults(unsigned int simResults);
  void setInstructions(unsigned int instructions);
  void setMemAccesses(unsigned int memAccesses);
  void setMissRate(float missRate);
  void setRdMissRate(float RdMissRate);
  void setCpuTime(float cpuTime);
  void setAvgMemAccessTime(float avgMemAccessTime);
  void setDirtyEvictions(unsigned int dirtyEvictions);
  void setLoadMisses(unsigned int loadMisses);
  void setStoreMisses(unsigned int storeMisses);
  void setTotalMisses(unsigned int totalMisses);
  void setLoadHits(unsigned int loadHits);
  void setStoreHits(unsigned int storeHits);
  void setTotalHits(unsigned int totalHits);
};

#endif
