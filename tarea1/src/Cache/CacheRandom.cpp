#include "Cache/CacheRandom.hh"

CacheRandom::CacheRandom(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, tfr) {
  this->randEl = std::default_random_engine(this->r());
  this->uniformDist = std::uniform_int_distribution<int>(0, this->cacheLines-1);
};

void CacheRandom::access(TraceLine* traceLine){
  if (!this->isHit) {
    auto it = this->cache->at(this->index)->begin();
    std::advance(it, this->uniformDist(this->randEl));
    if (it->second->dirtyBit) {
      this->setDirtyEvictions(this->getDirtyEvictions() + 1);
      // here the cache should write to main memory
    }
    this->cache->at(this->index)->erase(it);
    this->cache->at(this->index)->insert_or_assign(this->tag, new CacheInfo(0, 1));
  }
};
