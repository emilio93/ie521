
#include <string>

#include "Cache/CacheNRU.hh"

CacheNRU::CacheNRU(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty) {
  this->size = size;
  this->associativity = associativity;
  this->blockSize = blockSize;
  this->cacheRP = cacheRP;
  this->missPenalty = missPenalty;
};

void CacheNRU::runTest(){

};
