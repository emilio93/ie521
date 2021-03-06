#include "Cache/CacheRandom.hh"

CacheRandom::CacheRandom(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty, float cycMult, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, cycMult, tfr) {
  this->randEl = std::default_random_engine(this->r());
  this->uniformDist = std::uniform_int_distribution<int>(0, this->cacheLines-1);
};

void CacheRandom::access(TraceLine* traceLine){
  if (!this->isHit) {

    auto random_it = std::next(this->cache.at(this->index).begin(), this->uniformDist(this->randEl));
    if (random_it->second.valid && random_it->second.dirtyBit && traceLine->getLS() == 0) {
      this->setDirtyEvictions(this->getDirtyEvictions() + 1);
      // here the cache should write to main memory
    }
    this->cache.at(this->index).erase(random_it);
    this->cache.at(this->index).insert_or_assign(this->tag, CacheInfo(traceLine->getLS() == 0 ? 0 : 1, 1));
  }
};
