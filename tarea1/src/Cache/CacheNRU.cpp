#include "Cache/CacheNRU.hh"

CacheNRU::CacheNRU(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty, float cycMult, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, cycMult, tfr) {
  this->nruList = std::vector<NruList>();
  this->nruMap = std::vector<NruMap>();

  // create lru lists and maps for each set
  for (size_t i = 0; i < this->getAssociativity(); i++) {
    NruList setN = NruList();
    this->nruList.push_back(setN);

    NruMap mapN = NruMap();
    this->nruMap.push_back(mapN);
    for (size_t j = 0; j < this->cacheLines; j++) {
      this->nruList.at(i).push_back(NruNode(j, 1));
      this->nruMap.at(i).insert_or_assign(j, this->nruList.at(i).end());
    }
  }
};

void CacheNRU::access(TraceLine* traceLine) {
  if (this->isHit) {
    // set nru bit to 0
    this->nruMap.at(this->index).at(this->tag)->nruBit = 0;
  } else {
    // search first 1
    auto it =
        std::find_if(std::begin(this->nruList.at(this->index)),
                     std::end(this->nruList.at(this->index)), this->isNru);
    if (it != this->nruList.at(this->index).end()) {
      // count dirty eviction
      if (this->cache.at(this->index).at(it->tag).dirtyBit &&
          this->cache.at(this->index).at(it->tag).valid) {
        // add to dirty evictions
        this->setDirtyEvictions(this->getDirtyEvictions() + 1);
      }
      // remove elements
      this->cache.at(this->index).erase(it->tag);
      this->nruMap.at(this->index).erase(it->tag);
      // set new element
      it->nruBit = 0;
      it->tag = this->tag;
      this->nruMap.at(this->index).insert_or_assign(this->tag, it);
      this->cache.at(this->index).insert_or_assign(this->tag, CacheInfo(0, 1));

    } else {  // no nru bits set to 1
      // count dirty eviction
      if (this->cache.at(this->index)
              .at(this->nruList.at(this->index).front().tag)
              .dirtyBit &&
          this->cache.at(this->index)
              .at(this->nruList.at(this->index).front().tag)
              .valid) {
        // add to dirty evictions
        this->setDirtyEvictions(this->getDirtyEvictions() + 1);
      }
      // set all nru bits to 1 and push to front
      for (auto iter = this->nruList.at(this->index).begin();
           iter != this->nruList.at(this->index).end(); iter++) {
             iter->nruBit = iter->nruBit+1;
      }
      // remove elements
      this->cache.at(this->index)
          .erase(this->nruList.at(this->index).front().tag);
      this->nruMap.at(this->index)
          .erase(this->nruList.at(this->index).front().tag);
      this->nruList.at(this->index).pop_front();

      // insert element to nru list, map and also to the cache
      this->nruList.at(this->index).push_front(NruNode(this->tag, 0));
      this->nruMap.at(this->index)
          .insert_or_assign(this->tag, this->nruList.at(this->index).begin());
      this->cache.at(this->index).insert_or_assign(this->tag, CacheInfo(0, 1));
    }
  }
};

bool CacheNRU::isNru(const NruNode& nruNode) { return nruNode.nruBit; }
