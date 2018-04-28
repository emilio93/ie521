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

int main(int argc, char* argv[]) {
  const clock_t begin_time = clock();

  CLI* cli = NULL;
  try {
    cli = new CLI(argv);
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return 0;
  }

  Cache* cache =
      Cache::makeCache(std::stoi(cli->getOpts().at(TAMANO_CACHE)),
                       std::stoi(cli->getOpts().at(ASOCIATIVIDAD)),
                       std::stoi(cli->getOpts().at(TAMANO_LINEA)),
                       stringToCacheRP(cli->getOpts().at(POLITICA_REMPLAZO)),
                       std::stoi(cli->getOpts().at(MISS_PENALTY)));

  const char separator = ' ';
  const int parWidth = 40;
  const int valWidth = 8;
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

  // std::cout << "Trace: " << cli->getOpts().at(TRACE_FILENAME) << std::endl;

  TraceFile* tfr = new TraceFile(cli->getOpts().at(TRACE_FILENAME));
  signed int i = 0;

  if (!tfr->nextLine()) std::cout << "Error en el archivo utilizado" << '\n';

  TraceLine* traceLine = TraceLine::makeTraceLine(tfr->currLine());
  do {
    traceLine->update(tfr->currLine());
    i++;
    // if (i%500000==0) std::cout << std::hex << traceLine->getDireccion() <<
    // std::endl;
    // if (i > 300) break;
  } while (tfr->nextLine());

  delete traceLine;
  traceLine = NULL;

  delete tfr;
  tfr = NULL;

  delete cli;
  cli = NULL;

  // std::cout << "Cuenta Lineas: " << std::dec << i << std::endl;
  // std::cout << "Ejecución en " << float(clock() - begin_time) /
  // CLOCKS_PER_SEC
  //           << "s" << std::endl;

  std::cout << "-------------------" << std::endl;
  std::cout << "Simulation results:" << std::endl;
  std::cout << "-------------------" << std::endl;
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Execution time(cycles):";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 1
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "instructions:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 2
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Memory accesses:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 3
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Overall miss rate:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 4
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Read miss rate:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 5
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Average memory access time (cycles):";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 5
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Dirty evictions:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 5
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Load misses:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 5
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Store misses:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 5
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Total misses:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 5
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Load hits:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 5
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Store hits:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 5
            << std::endl;

  std::cout << std::left << std::setw(parWidth) << std::setfill(separator)
            << "Total hits:";
  std::cout << std::left << std::setw(parWidth) << std::setfill(separator) << 5
            << std::endl;

  std::cout << std::endl;
}
