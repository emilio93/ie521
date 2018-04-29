#ifndef CLASS_CACHE_LRU
#define CLASS_CACHE_LRU

#include <bitset>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <random>

#include "Cache/Cache.hh"
#include "TraceFile/TraceFile.hh"

class CacheLRU : public Cache {
 private:

  CacheInfo* readLru();

  void writeLru();

  std::vector<std::list<long int>> lruList;

 public:
  //! Constructor sets parameters of the cache and the trace File reference.
  explicit CacheLRU(unsigned int size, unsigned int associativity,
                    unsigned int blockSize, CacheRP cacheRP,
                    unsigned int missPenalty, TraceFile* tfr);

  //! Single memory access implemented to satisfy lru rp.
  void access(TraceLine* traceLine);
};

#endif
