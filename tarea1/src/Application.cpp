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

  // CLI* cli = new CLI(argv);
  // cli->testCli(argc, argv);

  TraceFile* tfr = new TraceFile("./data/art.trace.gz");
  signed int i = 0;

  if (!tfr->nextLine()) std::cout << "Error en el archivo utilizado" << '\n';
  TraceLine* traceLine = TraceLine::makeTraceLine(tfr->currLine());
  std::cout << "hola" << '\n';
  do {
    // traceLine->update(tfr->currLine());
    if (i % 1000 == 0) { 
      std::cout <<  tfr->currLine()<< '\n';
      std::cout << "Dirección:" << traceLine->getDireccion() << std::endl
                << "IC:" << traceLine->getIC() << std::endl
                << "LS:" << traceLine->getLS() << std::endl;
      std::cout << "Ejecución hasta " << std::dec << i << " en "
                << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                << std::endl
                << std::endl;
      ret = getrusage(who, &usage);
      std::cout << "Memoria utilizada - maxrss:\t" << usage.ru_maxrss << "kB"
                << std::endl
                << "Memoria utilizada - minflt:\t" << usage.ru_minflt
                << std::endl
                << "Memoria utilizada - majflt:\t" << usage.ru_majflt
                << std::endl
                << "Memoria utilizada - nvcsw:\t" << usage.ru_nvcsw << std::endl
                << "Memoria utilizada - nivcsw:\t" << usage.ru_nivcsw
                << std::endl;
    }
    i++;
    // if (i > 50000) break;
  } while (tfr->nextLine());

  delete traceLine;
  traceLine = NULL;

  std::cout << "Cuenta Lineas: " << std::dec << i << std::endl;
  std::cout << "Ejecución en " << float(clock() - begin_time) / CLOCKS_PER_SEC
            << "s" << std::endl;
}