#include <iostream>
#include <string>

#include "Cache/Cache.hh"
#include "Cache/CacheLRU.hh"
#include "Cache/CacheNRU.hh"

Cache* Cache::makeCache(unsigned int size, unsigned int associativity,
                        unsigned int blockSize, CacheRP cacheRP,
                        unsigned int missPenalty, TraceFile* tfr) {
  if (cacheRP == LRU) {
    Cache* cache =
        new CacheLRU(size, associativity, blockSize, cacheRP, missPenalty, tfr);
    return cache;
  } else if (cacheRP == NRU) {
    CacheNRU* cache =
        new CacheNRU(size, associativity, blockSize, cacheRP, missPenalty, tfr);
    return cache;
  }
  return NULL;
}

Cache::Cache(unsigned int size, unsigned int associativity,
             unsigned int blockSize, CacheRP cacheRP, unsigned int missPenalty,
             TraceFile* tfr) {
  this->setSize(size);
  this->setAssociativity(associativity);
  this->setBlockSize(blockSize);
  this->setCacheRP(cacheRP);
  this->setMissPenalty(missPenalty);
  this->setTfr(tfr);

  if (!tfr->nextLine())
    throw std::invalid_argument("Error en el archivo utilizado");

  this->setInstructions(0);
  this->setMemAccesses(0);
  this->setDirtyEvictions(0);
  this->setLoadHits(0);
  this->setLoadMisses(0);
  this->setStoreHits(0);
  this->setStoreMisses(0);
  this->setSimResults(0);

  this->initCache();

  // create offset, index and tag masks
  // for easy access to these elements
  // from a mem address.
  // Enables the following ints
  // this->offsetMask
  // this->indexMask
  // this->tagMask
  this->setAddressMasks();
};

void Cache::simulate() {
  unsigned int i = 0;
  TraceLine* traceLine = TraceLine::makeTraceLine(tfr->getLine());
  do {
    traceLine->update(tfr->getLine());
    i++;
    // cycles
    this->setInstructions(this->getInstructions() + traceLine->getIC());

    // mem accesses
    this->setMemAccesses(this->getMemAccesses() + 1);

    // set address parts. offset, index and tag
    this->mapAddress(traceLine);

    // always add as many cycles as instruction counts
    // possible miss penalty is added later on
    this->setSimResults(this->getSimResults() + traceLine->getIC());

    // asume we have a miss
    this->isHit = false;

    try {
      if (this->cache->at(this->index)->at(this->tag)->valid) {
        this->isHit = true;
      }
    } catch (const std::out_of_range& e) {
      this->isHit = false;
    }

    // update counters if hit
    if (this->isHit) {
      this->setTotalHits(this->getTotalHits() + 1);
      if (traceLine->getLS() == 0) {
        this->setLoadHits(this->getLoadHits() + 1);
      } else {
        this->setStoreHits(this->getStoreHits() + 1);
      }
    } else {
      this->setTotalMisses(this->getTotalMisses() + 1);
      // increace total cycles with miss penalty
      this->setSimResults(this->getSimResults() + this->getMissPenalty());
      if (traceLine->getLS() == 0) {
        this->setLoadMisses(this->getLoadMisses() + 1);
      } else {
        this->setStoreMisses(this->getStoreMisses() + 1);
      }
    }

    // replacement policy processing
    this->access(traceLine);
    if (i%50000 == 0) std::cout << i << std::endl;
    // if (i == 50000) break;
  } while (tfr->nextLine());

  this->setAvgMemAccessTime(this->getSimResults()/this->getInstructions());
  this->setCpuTime(0);

  delete traceLine;
  traceLine = NULL;
}

void Cache::setAddressMasks() {
  this->offsetBits = std::ceil(std::log2(this->getBlockSize()));
  this->indexBits =
      std::ceil(std::log2(this->getAssociativity()));
  this->tagBits = Cache::ADDRESS_LENGTH - (this->offsetBits + this->indexBits);

  this->offsetMask = std::exp2(offsetBits) - 1;
  this->indexMask = std::exp2(indexBits) - 1;
  this->indexMask = this->indexMask << offsetBits;
  this->tagMask = ~(offsetMask | indexMask);
}

void Cache::initCache() {
  // two-dimensional vector models the cache
  // first dimension is the set
  // second dimension is the line
  // value is the tag
  this->cache = new std::vector<std::unordered_map<long int, CacheInfo*>*>();
  this->cacheLines =
      this->getSize() * 1024 / this->getBlockSize() / this->getAssociativity();

  // make sure no tags are repeated
  int tagCounter;

  for (size_t i = 0; i < this->getAssociativity(); i++) {
    this->cache->push_back(new std::unordered_map<long int, CacheInfo*>());
    tagCounter = 0;
    for (size_t j = 0; j < this->cacheLines; j++) {
      this->cache->at(i)->insert({tagCounter++, new CacheInfo(0, 0)});
    }
  }
}

void Cache::mapAddress(TraceLine* traceLine) {
  this->offset = (this->offsetMask & traceLine->getDireccion());
  this->index =
      (this->indexMask & traceLine->getDireccion()) >> this->offsetBits;
  this->tag = (this->tagMask & traceLine->getDireccion()) >>
              (this->offsetBits + this->indexBits);

}

void Cache::setTfr(TraceFile* tfr) { this->tfr = tfr; }

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
