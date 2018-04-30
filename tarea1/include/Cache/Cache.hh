#ifndef ABSTRACT_CLASS_CACHE
#define ABSTRACT_CLASS_CACHE

#include <cmath>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "Cache/CacheRP.hh"
#include "TraceFile/TraceFile.hh"
#include "TraceLine/TraceLine.hh"

class CacheLRU;
class CacheNRU;
class CacheRandom;

struct CacheInfo {
  bool dirtyBit;
  bool valid;
  CacheInfo(bool db, bool v) {
    this->dirtyBit = db;
    this->valid = v;
  }
};

class Cache {
 protected:
  // Address length in bits
  static const int ADDRESS_LENGTH = 32;

  /**
   * @brief file to read the mem accesses from
   *
   */
  TraceFile* tfr;

  // -------------------------------------------
  // CACHE PROPERTIES
  // -------------------------------------------

  /**
   * @brief Size of the cache
   *
   */
  unsigned int size;

  /**
   * @brief Assicuativity of the cache
   *
   */
  unsigned int associativity;

  /**
   * @brief Block size of the cache
   *
   */
  unsigned int blockSize;

  /**
   * @brief Replacement Policy of the cache
   *
   */
  CacheRP cacheRP;

  /**
   * @brief Penalty cycles when a miss occurs
   *
   */
  unsigned int missPenalty;

  /**
   * @brief Cache lines
   *
   */
  unsigned int cacheLines;

  // -------------------------------------------
  // SIMULATION RESULTS
  // -------------------------------------------

  /**
   * @brief Simulation results: heightExecution time(cycles)
   *
   */
  unsigned int simResults;

  /**
   * @brief Instructions
   *
   */
  unsigned int instructions;

  /**
   * @brief Memory accesses
   *
   */
  unsigned int memAccesses;

  /**
   * @brief Overall miss rate
   *
   */
  float missRate;

  /**
   * @brief Read miss rate
   *
   */
  float RdMissRate;

  /**
   * @brief CPU time (cycles)
   *
   */
  float cpuTime;

  /**
   * @brief Average memory access time (cycles)
   *
   */
  float avgMemAccessTime;

  /**
   * @brief Dirty evictions
   *
   */
  unsigned int dirtyEvictions;

  /**
   * @brief Load misses
   *
   */
  unsigned int loadMisses;

  /**
   * @brief Store misses
   *
   */
  unsigned int storeMisses;

  /**
   * @brief Total misses
   *
   */
  unsigned int totalMisses;

  /**
   * @brief Load hits
   *
   */
  unsigned int loadHits;

  /**
   * @brief Store hits
   *
   */
  unsigned int storeHits;

  /**
   * @brief Total hits
   *
   */
  unsigned int totalHits;

  // -------------------------------------------
  // ADDRESS PARTS
  // -------------------------------------------

  /**
   * @brief tag mask to extract tag from address.
   *
   */
  long int tagMask;

  /**
   * @brief index mask to extract index from address.
   *
   */
  long int indexMask;

  /**
   * @brief offset mask to extract offset from address.
   *
   */
  long int offsetMask;

  /**
   * @brief Quantity of bits for the offset
   *
   */
  int offsetBits;

  /**
   * @brief Quantity of bits for the index
   *
   */
  int indexBits;

  /**
   * @brief Quantity of bits for the tag
   *
   */
  int tagBits;

  // CURRENT STATE

  /**
   * @breif Current address tag
   *
   */
  long int tag;

  /**
   * @breif Current address index
   *
   */
  long int index;

  /**
   * @breif Current address offset
   *
   */
  long int offset;

  /**
   * @brief Indicates if current access is a hit
   *
   */
  bool isHit;
  float cycMult;

  /**
   * @breif cache mem stores tags. Sets of lines
   * access as this->cache->at(setNo)->at(lineNo)
   *
   */
  std::vector<std::unordered_map<long int, CacheInfo>> cache;

  /**
   * @brief Construct a new Cache object
   *
   * @param size size of the cache
   * @param associativity associativity of the cache
   * @param blockSize cache block size
   * @param cacheRP cache replacement policy
   * @param missPenalty cache miss penalty
   * @param tfr trace file to simulate
   */
  Cache(unsigned int size, unsigned int associativity, unsigned int blockSize,
        CacheRP cacheRP, unsigned int missPenalty, float cycMult, TraceFile* tfr);

 public:
  /**
   * @brief Destroy the Cache object
   *
   */
  ~Cache();

  /**
   * @breif Runs the tests on the cache with the given parameters and assign
   * results
   *
   */
  virtual void access(TraceLine* traceLine) = 0;

  /**
   * @brief Initialize cache representation as a vector of vectors(sets of
   * lines)
   *
   */
  void initCache();

  /**
   * @brief run simulation of the trace file on the current cache
   *
   */
  void simulate();

  /**
   * @brief Returns cache info as a string
   *
   * @return std::string cache info string
   */
  std::string toString();

  /**
   * @brief Initialize a cache with the given parameters
   *
   * @param size cache size
   * @param associativity cache associativity
   * @param blockSize cache clock size
   * @param cacheRP cache replacement policy
   * @param missPenalty cache miss penalty
   * @param tfr trace file to read mem accesses
   * @return Cache* reference to created cache
   */
  static Cache* makeCache(unsigned int size, unsigned int associativity,
                          unsigned int blockSize, CacheRP cacheRP,
                          unsigned int missPenalty, float cycMult, TraceFile* tfr);

  /**
   * @brief Set the Address Masks for offset, index and tag for the built cache
   *
   */
  void setAddressMasks();

  /**
   * @brief Obtains the offset, index and tag of the current address
   *
   * @param traceLine current trace line with address
   */
  void mapAddress(TraceLine* traceLine);

  /**
   * @brief Set the TraceFile object
   *
   */
  void setTfr(TraceFile*);

  /**
   * @brief Get the cache size
   *
   * @return unsigned int cache size
   */
  unsigned int getSize();

  /**
   * @brief Get the cache associativity
   *
   * @return unsigned int cache associativity
   */
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
