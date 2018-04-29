#include "Cache/CacheNRU.hh"

CacheNRU::CacheNRU(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, tfr) {

};

void CacheNRU::access(TraceLine* traceLine){

};
