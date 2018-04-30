
#include "Cache/CacheRP.hh"

std::string cacheRPToString(CacheRP opt) {
  std::string option = "";
  switch (opt) {
    case LRU:
      option = "LRU";
      break;
    case NRU:
      option = "NRU";
      break;
    case SRRIP:
      option = "SRRIP";
      break;
    case RANDOM:
      option = "random";
      break;
    default:
      option = "";
  }
  return option;
}

CacheRP stringToCacheRP(std::string option) {
  CacheRP opt;
  if (option.compare("LRU") == 0) {
    opt = LRU;
  } else if (option.compare("NRU") == 0) {
    opt = NRU;
  } else if (option.compare("SRRIP") == 0) {
    opt = SRRIP;
  } else if (option.compare("random") == 0) {
    opt = RANDOM;
  } else {
    opt = INDEFINIDO;
  }
  return opt;
}
