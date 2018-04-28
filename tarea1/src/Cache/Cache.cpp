#include <iostream>
#include <string>

#include "Cache/Cache.hh"
#include "Cache/CacheLRU.hh"
#include "Cache/CacheNRU.hh"

Cache* Cache::makeCache(unsigned int size, unsigned int associativity,
                        unsigned int blockSize, CacheRP cacheRP,
                        unsigned int missPenalty) {
  if (cacheRP == LRU) {
    Cache* cache =
        new CacheLRU(size, associativity, blockSize, cacheRP, missPenalty);
    return cache;
  } else if (cacheRP == NRU) {
    CacheNRU* cache =
        new CacheNRU(size, associativity, blockSize, cacheRP, missPenalty);
    return cache;
  }
  return NULL;
}

std::string Cache::toString() {
  std::string result = "";
  result += "Tamaño: ";
  result += std::to_string(this->getSize());

  result += "\nAsociatividad: ";
  result += std::to_string(this->getAssociativity());

  result += "\nTamaño Línea: ";
  result += std::to_string(this->getBlockSize());

  result += "\nPolítica de Remplazo: ";
  result += cacheRPToString(this->getCacheRP());

  result += "\nMiss Penalty: ";
  result += std::to_string(this->getMissPenalty());
  return result + "\n";
}

unsigned int Cache::getSize() { return this->size; }
unsigned int Cache::getAssociativity() { return this->associativity; }
unsigned int Cache::getBlockSize() { return this->blockSize; }
CacheRP Cache::getCacheRP() { return this->cacheRP; }
unsigned int Cache::getMissPenalty() { return this->missPenalty; }

void Cache::setSize(unsigned int size) { this->size = size; }
void Cache::setAssociativity(unsigned int associativity) {
  this->associativity = associativity;
}
void Cache::setBlockSize(unsigned int blockSize) {
  this->blockSize = blockSize;
}
void Cache::setCacheRP(CacheRP cacheRP) { this->cacheRP = cacheRP; }
void Cache::setMissPenalty(unsigned int missPenalty) {
  this->missPenalty = missPenalty;
}

unsigned int Cache::getSimResults() { return this->simResults; }
unsigned int Cache::getInstructions() { return this->instructions; }
unsigned int Cache::getMemAccesses() { return this->memAccesses; }
float Cache::getMissRate() { return this->missRate; }
float Cache::getRdMissRate() { return this->RdMissRate; }
float Cache::getCpuTime() { return this->cpuTime; }
float Cache::getAvgMemAccessTime() { return this->avgMemAccessTime; }
unsigned int Cache::getDirtyEvictions() { return this->dirtyEvictions; }
unsigned int Cache::getLoadMisses() { return this->loadMisses; }
unsigned int Cache::getStoreMisses() { return this->storeMisses; }
unsigned int Cache::getTotalMisses() { return this->totalMisses; }
unsigned int Cache::getLoadHits() { return this->loadHits; }
unsigned int Cache::getStoreHits() { return this->storeHits; }
unsigned int Cache::getTotalHits() { return this->totalHits; }

void Cache::setSimResults(unsigned int simResults) {
  this->simResults = simResults;
}
void Cache::setInstructions(unsigned int instructions) {
  this->instructions = instructions;
}
void Cache::setMemAccesses(unsigned int memAccesses) {
  this->memAccesses = memAccesses;
}
void Cache::setMissRate(float missRate) { this->missRate = missRate; }
void Cache::setRdMissRate(float RdMissRate) { this->RdMissRate = RdMissRate; }
void Cache::setCpuTime(float cpuTime) { this->cpuTime = cpuTime; }
void Cache::setAvgMemAccessTime(float avgMemAccessTime) {
  this->avgMemAccessTime = avgMemAccessTime;
}
void Cache::setDirtyEvictions(unsigned int dirtyEvictions) {
  this->dirtyEvictions = dirtyEvictions;
}
void Cache::setLoadMisses(unsigned int loadMisses) {
  this->loadMisses = loadMisses;
}
void Cache::setStoreMisses(unsigned int storeMisses) {
  this->storeMisses = storeMisses;
}
void Cache::setTotalMisses(unsigned int totalMisses) {
  this->totalMisses = totalMisses;
}
void Cache::setLoadHits(unsigned int loadHits) { this->loadHits = loadHits; }
void Cache::setStoreHits(unsigned int storeHits) {
  this->storeHits = storeHits;
}
void Cache::setTotalHits(unsigned int totalHits) {
  this->totalHits = totalHits;
}
