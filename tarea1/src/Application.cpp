#include <sys/resource.h>
#include <sys/time.h>
#include <exception>

#include "Cli/Cli.hh"
#include "TraceFile/TraceFile.hh"
#include "TraceLine/TraceLine.hh"

int main(int argc, char* argv[]) {
  const clock_t begin_time = clock();

  int who = RUSAGE_SELF;
  struct rusage usage;
  int ret;

  CLI* cli = new CLI(argv);
  cli->testCli(argc, argv);

  TraceFile* tfr = new TraceFile("./data/art.trace.gz");
  signed int i = 0;

  TraceLine* traceLine;
  traceLine = TraceLine::makeTraceLine(tfr->currLine());
  while (tfr->nextLine()) {
    if (i % 1000 == 0) {
      std::cout << "Dirección:" << traceLine->getDireccion() << std::endl
                << "IC:" << traceLine->getIC() << std::endl
                << "LS:" << traceLine->getLS() << std::endl;
      std::cout << "Ejecución hasta " << std::dec << i << " en "
                << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                << std::endl
                << std::endl;
  ret = getrusage(who, &usage);
  std::cout << "Memoria utilizada - ru_maxrss:\t" << usage.ru_maxrss << " kB" << std::endl;
  std::cout << "Memoria utilizada - ru_minflt:\t" << usage.ru_minflt << std::endl;
  std::cout << "Memoria utilizada - ru_majflt:\t" << usage.ru_majflt << std::endl;
  std::cout << "Memoria utilizada - ru_nvcsw:\t" << usage.ru_nvcsw << std::endl;
  std::cout << "Memoria utilizada - ru_nivcsw:\t" << usage.ru_nivcsw << std::endl;
    }
    delete traceLine;
    traceLine = NULL;
    i++;
    if (i > 5400) break;
  };

  std::cout << "Cuenta Lineas: " << std::dec << i << std::endl;
  std::cout << "Ejecución en " << float(clock() - begin_time) / CLOCKS_PER_SEC
            << "s" << std::endl;

}