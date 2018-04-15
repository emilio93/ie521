#include "Cli/Cli.hh"

int main(int argc, char* argv[]) {
  CLI* cli = new CLI(argv);
  cli->testCli(argc, argv);
  return 0;
}
