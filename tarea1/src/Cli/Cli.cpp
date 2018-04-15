
#include "Cli/Cli.hh"

CLI::CLI(char* argv[]) {
  unsigned i = 0;
  while (argv[i]) {
    i++;
  };
  this->args = std::vector<std::string>(argv, argv + i);
}

bool CLI::hasFlag(std::string fullCommand) {}
void CLI::reconstructCommand() {}

void CLI::getPairs() {
  for (int i = 1; i != this->args.size(); i++) {
    if (checkOption(stringToCliOption(this->args.at(i)))) {
      if (i == this->args.size()) {
        std::cout << "Argumento incompleto \"" << this->args.at(i) << "\"\n";
        return;
      }
      if (!checkOptionValue(stringToCliOption(this->args.at(i)),
                            this->args.at(i + 1))) {
        std::cout << "Argumento no aceptado \"" << this->args.at(i) << " "
                  << this->args.at(i + 1) << "\"\n";
        return;
      }
      this->opts.insert(
          {stringToCliOption(this->args.at(i)), this->args.at(i + 1)});
      std::cout << "Opcion agregada \"" << this->args.at(i) << " "
                << this->args.at(i + 1) << "\"\n";
      i++;
    }
  }
  return;
}

void CLI::testCli(int argc, char* argv[]) {
  this->getPairs();
  // clang-format off
  // std::string str = "1 400667 15 -1 15 W - -         8            0       40066b            0 ADD      ADD_IMM";
  std::string str = "# 0 30004a30 2";
  // clang-format on
  TraceLine* traceLine = TraceLine::makeTraceLine(str);
  std::cout << "LS\t\t" << traceLine->getLS() << std::endl;
  std::cout << "Direccion\t" << std::hex << traceLine->getDireccion()
            << std::endl;
  std::cout << "IC\t\t" << traceLine->getIC() << std::endl;
}

std::map<CliOption, std::string> CLI::getOpts() { return this->opts; }
