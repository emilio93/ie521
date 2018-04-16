#include "Cli/Cli.hh"

void CLI::getPairs() {
  for (int i = 1; i < this->args.size(); i++) {
    if (checkOption(stringToCliOption(this->args.at(i)))) {
      if (i == this->args.size()-1) {
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
  std::cout << std::endl;
  return;
}

CLI::CLI(char* argv[]) {
  unsigned i = 0;
  while (argv[i]) {
    i++;
  };
  this->args = std::vector<std::string>(argv, argv + i);
  this->getPairs();
}

std::map<CliOption, std::string> CLI::getOpts() { return this->opts; }

void CLI::testCli(int argc, char* argv[]) {
  // clang-format off
  // std::string str = "1 400667 15 -1 15 W - -         8            0       40066b            0 ADD      ADD_IMM";
  std::string str = "# 0 30004a30 2";
  // clang-format on

  TraceLine* traceLine = TraceLine::makeTraceLine(str);
  std::cout << "LS\t\t" << traceLine->getLS() << std::endl
            << "Direccion\t" << std::hex << traceLine->getDireccion()
            << std::endl
            << "IC\t\t" << traceLine->getIC() << std::endl;
  delete traceLine;

  Cache* cache;
  try {
    cache =
        Cache::makeCache(std::stoi(this->getOpts().at(TAMANO_CACHE)),
                         std::stoi(this->getOpts().at(ASOCIATIVIDAD)),
                         std::stoi(this->getOpts().at(TAMANO_LINEA)),
                         stringToCacheRP(this->getOpts().at(POLITICA_REMPLAZO)),
                         std::stoi(this->getOpts().at(MISS_PENALTY)));
  } catch (std::exception& e) {
    std::cout << "Error " << e.what() << std::endl << "Faltan Parámetros" << std::endl;
    return;
  }

  if (cache == NULL) return;

  std::cout << std::endl << "Cache"<< std::endl;
  std::cout << cache->toString() << std::endl;
}

