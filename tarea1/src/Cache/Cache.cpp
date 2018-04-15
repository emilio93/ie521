#include <iostream>
#include <string>

#include "Cache/Cache.hh"
#include "Cache/CacheLRU.hh"
#include "Cache/CacheNRU.hh"

Cache* Cache::makeCache(unsigned int size, unsigned int associativity,
                        unsigned int blockSize, CacheRP cacheRP,
                        unsigned int missPenalty) {
  if (cacheRP == LRU) {
    CacheLRU* cache =
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
  result += std::to_string(this->size);

  result += "\nAsociatividad: ";
  result += std::to_string(this->associativity);
  result += "\nTamaño Línea: ";
  result += std::to_string(this->blockSize);

  result += "\nPolítica de Remplazo: ";
  result += cacheRPToString(this->cacheRP);

  result += "\nMiss Penalty: ";
  result += std::to_string(this->missPenalty);
  return result + "\n";
}