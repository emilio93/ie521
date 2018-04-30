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
  }
};

CacheLRU::~CacheLRU() { ; }

void CacheLRU::access(TraceLine* traceLine) {
  if (this->isHit) {  // hit

    try {
      this->lruList.at(this->index)
          .splice(this->lruList.at(this->index).begin(),
                  this->lruList.at(this->index),
                  this->lruMap.at(this->index).at(this->tag));
    } catch (const std::out_of_range& e) {
      std::cout << std::endl;
      std::cout << this->tag << "   " << e.what() << std::endl;
    }
    // update element mapping
    this->lruMap.at(this->index)
        .insert_or_assign(this->tag, this->lruList.at(this->index).begin());
    // No update required in the cache
    this->cache.at(this->index)
        .insert_or_assign(this->tag, CacheInfo(false, true));

  } else {  // miss
    try {
      // cache set is full
      if (this->lruList.at(this->index).size() == this->cacheLines) {

        if (this->cache.at(this->index).at(this->lruList.at(this->index).back()).dirtyBit) {
          this->setDirtyEvictions(this->getDirtyEvictions() + 1);
        }
        // remove lru item
        this->lruMap.at(this->index)
            .erase(this->lruList.at(this->index).back());
        this->cache.at(this->index)
            .erase(this->lruList.at(this->index).back());
        this->lruList.at(this->index).pop_back();
      }

      // always push the new element on miss
      this->lruList.at(this->index).push_front(this->tag);
      // map the element
      this->lruMap.at(this->index)
          .insert_or_assign(this->tag, this->lruList.at(this->index).begin());
      // insert element to cache, not dirty, valid
      this->cache.at(this->index)
          .insert_or_assign(this->tag, CacheInfo(false, true));
    } catch (std::out_of_range& e) {
      std::cout << e.what() << std::endl;
    }
  }
};
