#ifndef CLASS_CACHE_LRU
#define CLASS_CACHE_LRU

#include <bitset>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>
#include <set>

#include <boost/bimap.hpp>

#include "Cache/Cache.hh"
#include "TraceFile/TraceFile.hh"

struct CacheLRUInfo : public CacheInfo {
  unsigned int lruPos;
  CacheLRUInfo(bool db, bool v, unsigned int lruPos) : CacheInfo(db, v) {
    this->lruPos = lruPos;
  }
};

class CacheLRU : public Cache {
 private:

  //! lruList keeps track of the cache elements with lru rp.
  std::vector<boost::bimap<long int, long int>*>* lruList;

  /**
   * @brief initializes the lruList
   *
   */
  void initLruList();

  void getCacheAddress();

  void setCacheAddress();

 public:
  //! Constructor sets parameters of the cache and the trace File reference.
  explicit CacheLRU(unsigned int size, unsigned int associativity,
                    unsigned int blockSize, CacheRP cacheRP,
                    unsigned int missPenalty, TraceFile* tfr);

  //! Single memory access implemented to satisfy lru rp.
  void access(TraceLine* traceLine);
};

#endif
