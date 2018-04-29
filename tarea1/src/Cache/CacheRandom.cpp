
#include <string>

#include "Cache/CacheRandom.hh"

CacheRandom::CacheRandom(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, tfr) {

};

void CacheRandom::access(TraceLine* traceLine){

};
