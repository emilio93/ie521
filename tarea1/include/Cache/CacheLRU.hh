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

typedef std::list<long int> LruList;
typedef std::unordered_map<long int, LruList::iterator> LruMap;

class CacheLRU : public Cache {
 private:

  // Keeps the lru list
  std::vector<LruList> lruList;

  // maps the lru List for fast access
  std::vector<LruMap> lruMap;

 public:
  //! Constructor sets parameters of the cache and the trace File reference.
  explicit CacheLRU(unsigned int size, unsigned int associativity,
                    unsigned int blockSize, CacheRP cacheRP,
                    unsigned int missPenalty, float cycMult, TraceFile* tfr);
  ~CacheLRU();
  //! Single memory access implemented to satisfy lru rp.
  void access(TraceLine* traceLine);
};

#endif
