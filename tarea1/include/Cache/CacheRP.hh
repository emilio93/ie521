#ifndef ENUM_CACHE_RP
#define ENUM_CACHE_RP

#include <exception>
#include <string>

//! Cache Replacement Policies
/*!
 * Enabled Cache replacement policies. The struct is
 * used to help create the Cache object.
 */
enum CacheRP { LRU, NRU, SRRIP, RANDOM, INDEFINIDO };

std::string cacheRPToString(CacheRP opt);

CacheRP stringToCacheRP(std::string option);

#endif
