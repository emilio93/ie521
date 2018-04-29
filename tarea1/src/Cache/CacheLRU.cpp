#include "Cache/CacheLRU.hh"

CacheLRU::CacheLRU(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, tfr) {

  this->lruList = std::vector<std::list<long int>>();

  for (size_t i = 0; i < this->getAssociativity(); i++) {
    std::list<long int> *setN = new std::list<long int>();
    this->lruList.push_back(*setN);
  }
};

void CacheLRU::access(TraceLine* traceLine) {
  if (traceLine->getLS() == 0) { // load
    CacheInfo* ci = this->readLru();
  } else { // store

  }

};

CacheInfo* CacheLRU::readLru() {
  std::unordered_map<long int, CacheInfo*>* currSet =
      this->cache->at(this->index);
  std::list<long int> currLru = this->lruList.at(this->index);

  if (this->isHit) { // hit
    std::list<long>::const_iterator begin = currLru.begin();
    std::list<long>::const_iterator oldTag = currLru.end();
    oldTag--;
    currLru.splice(begin, currLru, oldTag);
  } else { // miss
    if (currSet->size() == this->cacheLines) {
      std::unordered_map<long int, CacheInfo*>::const_iterator oldIt =
          currSet->find(currLru.back());
      currSet->erase(oldIt);
      currLru.pop_back();
    }
    // std::cout<<currLru<<std::endl;
    // currLru->push_front(this->tag);
    // currSet->insert_or_assign(this->tag, new CacheInfo(0, 1));

    return NULL;
  }
};

void CacheLRU::writeLru() {
  std::unordered_map<long int, CacheInfo*>* currSet =
      this->cache->at(this->index);

  // Miss
  if (!this->isHit) {
    // full cache
    if (currSet->size() == this->cacheLines) {
      std::unordered_map<long int, CacheInfo*>::const_iterator oldIt =
          currSet->find(this->tag);
      currSet->erase(oldIt);
      this->lruList.at(this->index).pop_back();
    }

    this->lruList.at(this->index).push_front(this->tag);
    CacheInfo* ci = new CacheInfo(0, 1);
    currSet->insert_or_assign(this->tag, ci);
  } else {  // Hit
    currSet->insert_or_assign(this->tag, new CacheInfo(0, 1));
  }
};
