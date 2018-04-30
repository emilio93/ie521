#include "Cache/CacheSRRIP.hh"

CacheSRRIP::CacheSRRIP(unsigned int size, unsigned int associativity,
                   unsigned int blockSize, CacheRP cacheRP,
                   unsigned int missPenalty, TraceFile* tfr)
    : Cache(size, associativity, blockSize, cacheRP, missPenalty, tfr) {

};

void CacheSRRIP::access(TraceLine* traceLine){

};
