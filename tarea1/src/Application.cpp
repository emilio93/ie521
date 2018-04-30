#include <sys/resource.h>
#include <sys/time.h>
#include <exception>
#include <iomanip>
#include <iostream>

#include "Cache/Cache.hh"
#include "Cli/Cli.hh"
#include "Cli/CliOption.hh"
#include "TraceFile/TraceFile.hh"
#include "TraceLine/TraceLine.hh"

void printCacheInfo(Cache* cache, char separator, int parWidth, int valWidth);
void printCacheResults(Cache* cache, char separator, int parWidth,
                       int valWidth);

int main(int argc, char* argv[]) {
  const clock_t begin_time = clock();

  CLI* cli = NULL;
  try {
    cli = new CLI(argv);
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return 0;
  }

  TraceFile* tfr = NULL;
  try {
    tfr = new TraceFile(cli->getOpts().at(TRACE_FILENAME));
  } catch (boost::iostreams::zlib_error& e) {
    std::cout << e.what() << std::endl;
    return 0;
  }

  Cache* cache;
  try {
    cache =
        Cache::makeCache(std::stoi(cli->getOpts().at(TAMANO_CACHE)),
                         std::stoi(cli->getOpts().at(ASOCIATIVIDAD)),
                         std::stoi(cli->getOpts().at(TAMANO_LINEA)),
                         stringToCacheRP(cli->getOpts().at(POLITICA_REMPLAZO)),
                         std::stoi(cli->getOpts().at(MISS_PENALTY)), tfr);
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return 0;
  }

  if (cache == NULL) {
    std::cout << "Error: Politica de remplazo no implementada" << std::endl;
    return 0;
  }

  const char separator = ' ';
  const int parWidth = 40;
  const int valWidth = 8;

  printCacheInfo(cache, separator, parWidth, valWidth);

  signed int i = 0;

  cache->simulate();

  delete tfr;
  tfr = NULL;

  delete cli;
  cli = NULL;

  printCacheResults(cache, separator, parWidth, valWidth);

  delete cache;
  cache = NULL;

  std::cout << "Ejecución en " << float(clock() - begin_time) / CLOCKS_PER_SEC
            << "s" << std::endl;
}

void printCacheInfo(Cache* cache, char separator, int parWidth, int valWidth) {
  std::cout << "-----------------" << std::endl;
  std::cout << "Cache parameters:" << std::endl;
  std::cout << "-----------------" << std::endl;
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Cache Size(KB):";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getSize() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Cache Associativity:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getAssociativity() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Cache Block Size(bytes):";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getBlockSize() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Cache replacement policy:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cacheRPToString(cache->getCacheRP()) << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Miss penalty(cyc):";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getMissPenalty() << std::endl;
  std::cout << std::endl;
}

void printCacheResults(Cache* cache, char separator, int parWidth,
                       int valWidth) {
  std::cout << "-------------------" << std::endl;
  std::cout << "Simulation results:" << std::endl;
  std::cout << "-------------------" << std::endl;
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Execution time(cycles):";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getSimResults() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "instructions:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getInstructions() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Memory accesses:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getMemAccesses() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Overall miss rate:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getMissRate() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Read miss rate:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getRdMissRate() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Average memory access time (cycles):";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getAvgMemAccessTime() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Dirty evictions:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getDirtyEvictions() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Load misses:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getLoadMisses() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Store misses:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getStoreMisses() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Total misses:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getTotalMisses() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Load hits:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getLoadHits() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Store hits:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getStoreHits() << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Total hits:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << cache->getTotalHits() << std::endl;

              std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "CPI:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << ((float)cache->getSimResults()/(float)cache->getInstructions()) << std::endl;

  std::cout << std::endl;
}
