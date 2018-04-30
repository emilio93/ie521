#ifndef CLASS_CACHE_SRRIP
#define CLASS_CACHE_SRRIP

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "Cache/Cache.hh"
#include "TraceFile/TraceFile.hh"

/**
 * @brief Node in the list of current cache elements maps rrpv with tag.
 *
 */
struct SRRIPNode {
  long int tag;
  int rrpv;
  SRRIPNode(long int tag, int rrpv) {
    this->tag = tag;
    this->rrpv = rrpv;
  };
};

typedef std::list<SRRIPNode> SRRIPList;

typedef std::unordered_map<long int, SRRIPList::iterator> SRRIPMap;

/**
 * @brief SRRIP Cache replacement policy definition.
 *
 */
class CacheSRRIP : public Cache {
  private:

  // Keeps the srrip list
  std::vector<SRRIPList> srripList;

  // maps the srrip List for fast access maps the srrip list to the cache
  std::vector<SRRIPMap> srripMap;

  // m value for this policy
  static const int RRPV_MAX = 3;

  // checks if SRRIPNode's rrpv is max
  static bool isRrpvMax(const SRRIPNode& srripNode);

 public:
  //! Runs the tests on the cache with the given parameters and assign results.
  explicit CacheSRRIP(unsigned int size, unsigned int associativity,
                    unsigned int blockSize, CacheRP cacheRP,
                    unsigned int missPenalty, float cycMult, TraceFile* tfr);

  //! Single memory access implemented to satisfy srrip rp.
  void access(TraceLine* traceLine);
};

#endif
