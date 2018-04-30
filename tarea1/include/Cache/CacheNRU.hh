#ifndef CLASS_CACHE_NRU
#define CLASS_CACHE_NRU

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "Cache/Cache.hh"
#include "TraceFile/TraceFile.hh"



struct NruNode {
  long int tag;
  bool nruBit;
  NruNode(long int tag, bool nruBit) {
    this->tag = tag;
    this->nruBit = nruBit;
  };
};

typedef std::list<NruNode> NruList;
typedef std::unordered_map<long int, NruList::iterator> NruMap;

class CacheNRU : public Cache {
  private:

  // Keeps the nru list
  std::vector<NruList> nruList;

  // maps the nru List for fast access maps the nru list to the cache
  std::vector<NruMap> nruMap;

  static bool isNru(const NruNode& nruNode);

 public:
  //! Runs the tests on the cache with the given parameters and assign results.
  explicit CacheNRU(unsigned int size, unsigned int associativity,
                    unsigned int blockSize, CacheRP cacheRP,
                    unsigned int missPenalty, float cycMult, TraceFile* tfr);
  //! Single memory access implemented to satisfy nru rp.
  void access(TraceLine* traceLine);
};

#endif
