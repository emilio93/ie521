#include "Cache/CacheLRU.hh"

CacheLRU::CacheLRU(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, tfr) {
  this->lruList = std::vector<LruList>();
  this->lruMap = std::vector<LruMap>();

  // create lru lists and maps for each set
  for (size_t i = 0; i < this->getAssociativity(); i++) {
    LruList setN = LruList();
    this->lruList.push_back(setN);

    LruMap mapN = LruMap();
    this->lruMap.push_back(mapN);
    for (size_t j = 0; j < this->cacheLines; j++) {
      this->lruList.at(i).push_front(j);
      this->lruMap.at(i).insert_or_assign(j, this->lruList.at(i).begin());
    }
  }
};

CacheLRU::~CacheLRU() { ; }

void CacheLRU::access(TraceLine* traceLine) {
  if (this->isHit) {  // hit

    // move to front of list
    auto begin = std::begin(lruList.at(this->index));
    auto it = this->lruMap.at(this->index).at(this->tag);
    this->lruList.at(this->index)
        .splice(begin, this->lruList.at(this->index), it);

    // update element mapping
    this->lruMap.at(this->index)
        .insert_or_assign(this->tag, this->lruList.at(this->index).begin());

  } else {  // miss
    auto it =
        this->cache.at(this->index).find(this->lruList.at(this->index).back());
    if (this->cache.at(this->index)
            .find(this->lruList.at(this->index).back())
            ->second.dirtyBit &&
        this->cache.at(this->index)
            .find(this->lruList.at(this->index).back())
            ->second.valid) {
      this->setDirtyEvictions(this->getDirtyEvictions() + 1);
    }

    // remove lru item
    this->cache.at(this->index).erase(this->lruList.at(this->index).back());
    this->lruMap.at(this->index).erase(this->lruList.at(this->index).back());
    this->lruList.at(this->index).pop_back();

    // always push the new element on miss
    this->lruList.at(this->index).push_front(this->tag);
    // map the element
    this->lruMap.at(this->index)
        .insert_or_assign(this->tag, this->lruList.at(this->index).begin());
    // insert element to cache, not dirty, valid
    this->cache.at(this->index).insert_or_assign(this->tag, CacheInfo(0, 1));
  }
};
