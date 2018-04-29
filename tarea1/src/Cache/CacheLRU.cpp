#include "Cache/CacheLRU.hh"

CacheLRU::CacheLRU(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, tfr) {
  this->initLruList();
};


typedef boost::bimap<long int, long int> bimap;
typedef bimap::left_map::iterator left_it;
typedef bimap::value_type bimapValue;

void CacheLRU::initLruList() {
  // each set has a lru table
  this->lruList = new std::vector<bimap*>();
  int tagCounter;
  for (size_t i = 0; i < this->associativity; i++) {
    tagCounter = 0;
    this->lruList->push_back(new bimap());
    for (size_t j = 0; j < this->cacheLines; j++) {
      this->lruList->at(i)->insert(bimapValue(j, tagCounter++));
    }
  }

}
void CacheLRU::access(TraceLine* traceLine) {
  // Miss
  if (!this->isHit) {
    // replace tag in cache
    long int oldTag = this->lruList->at(this->index)->left.at(0); // lru tag
    this->cache->at(this->index)->erase(oldTag);
    this->cache->at(this->index)->insert({this->tag, new CacheInfo(1,1)});

    // reorder map and push new val
    left_it it_end = this->lruList->at(this->index)->left.end();
    for (size_t i = 0; i < this->lruList->at(this->index)->size(); i++) {

      if (i == this->lruList->at(this->index)->size()-1){
        this->lruList->at(this->index)->insert(bimapValue(i, this->tag));
      } else {
        this->lruList->at(this->index)->insert(bimapValue(i, this->lruList->at(this->index)->left.at(i+1)));
      }
    }
  } else { // HIT
    // nothing to do in the cache

    // reorder the lru list
  }
};

void CacheLRU::getCacheAddress() {

};

void CacheLRU::setCacheAddress() {

};
