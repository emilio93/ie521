#include "Cache/CacheSRRIP.hh"

CacheSRRIP::CacheSRRIP(unsigned int size, unsigned int associativity,
                       unsigned int blockSize, CacheRP cacheRP,
                       unsigned int missPenalty, float cycMult, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, cycMult, tfr) {
  this->srripList = std::vector<SRRIPList>();
  this->srripMap = std::vector<SRRIPMap>();

  // create lru lists and maps for each set
  for (size_t i = 0; i < this->getAssociativity(); i++) {
    SRRIPList setN = SRRIPList();
    this->srripList.push_back(setN);

    SRRIPMap mapN = SRRIPMap();
    this->srripMap.push_back(mapN);
    for (size_t j = 0; j < this->cacheLines; j++) {
      this->srripList.at(i).push_back(SRRIPNode(j, CacheSRRIP::RRPV_MAX));
      this->srripMap.at(i).insert_or_assign(j, this->srripList.at(i).end());
    }
  }
};

void CacheSRRIP::access(TraceLine* traceLine) {
  if (this->isHit) {
    // set rrpv to 0
    this->srripMap.at(this->index).at(this->tag)->rrpv = 0;
  } else {
    // search first max
    auto it = std::find_if(std::begin(this->srripList.at(this->index)),
                           std::end(this->srripList.at(this->index)),
                           CacheSRRIP::isRrpvMax);

    while (true) {
      if (it != this->srripList.at(this->index).end()) break;

      // increase all rrvp
      for (auto iter = this->srripList.at(this->index).begin();
           iter != this->srripList.at(this->index).end(); iter++) {
             iter->rrpv = iter->rrpv == CacheSRRIP::RRPV_MAX ? iter->rrpv : iter->rrpv+1;
      }

      // search max again
      it = std::find_if(std::begin(this->srripList.at(this->index)),
                        std::end(this->srripList.at(this->index)),
                        CacheSRRIP::isRrpvMax);
    }
    // count dirty eviction
    if (this->cache.at(this->index).at(it->tag).dirtyBit &&
        this->cache.at(this->index).at(it->tag).valid) {
      // add to dirty evictions
      this->setDirtyEvictions(this->getDirtyEvictions() + 1);
    }
    // remove elements
    this->cache.at(this->index).erase(it->tag);
    this->srripMap.at(this->index).erase(it->tag);
    // set new element
    it->rrpv = CacheSRRIP::RRPV_MAX - 1;
    it->tag = this->tag;
    this->srripMap.at(this->index).insert_or_assign(this->tag, it);
    this->cache.at(this->index).insert_or_assign(this->tag, CacheInfo(traceLine->getLS() == 0 ? 0 : 1, 1));
  }
};

bool CacheSRRIP::isRrpvMax(const SRRIPNode& srripNode) {
  return (srripNode.rrpv == CacheSRRIP::RRPV_MAX);
}
