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
  // cli->testCli(argc, argv);

  TraceFile* tfr = new TraceFile("./data/art.trace.gz");
  signed int i = 0;

  if (!tfr->nextLine()) std::cout << "Error en el archivo utilizado" << '\n';
  std::cout << *tfr->currLine() << std::endl;
  TraceLine* traceLine = TraceLine::makeTraceLine(tfr->currLine());
  do {
    traceLine->update(tfr->currLine());
    i++;
    if (i%500000==0) std::cout << std::hex << traceLine->getDireccion() << std::endl;
    // if (i > 300) break;
  } while (tfr->nextLine());

  delete traceLine;
  traceLine = NULL;

  delete tfr;
  tfr = NULL;

  delete cli;
  cli = NULL;

  std::cout << "Cuenta Lineas: " << std::dec << i << std::endl;
  std::cout << "Ejecución en " << float(clock() - begin_time) / CLOCKS_PER_SEC
            << "s" << std::endl;
}