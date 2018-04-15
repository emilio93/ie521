#include <iostream>

#include "Cache/Cache.hh"
#include "Cache/CacheLRU.hh"

Cache* Cache::makeCache(CacheRP cacheRP) {
  if (cacheRP == LRU) {
    CacheLRU* cache = new CacheLRU(1, 1, 1, LRU, 1);
    return cache;
  }
  return NULL;
}