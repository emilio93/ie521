#include "Cli/Cli.hh"

CLI::CLI(char* argv[]) {
  unsigned i = 0;
  while (argv[i]) {
    i++;
  };
  this->args = std::vector<std::string>(argv, argv + i);
  this->getPairs();
}

void CLI::getPairs() {
  for (unsigned int i = 1; i < this->args.size(); i++) {
    if (checkOption(stringToCliOption(this->args.at(i)))) {
      if (i == this->args.size() - 1) {
        throw std::invalid_argument("Argumento incompleto \"" +
                                    this->args.at(i) + "\"");
      }
      if (!checkOptionValue(stringToCliOption(this->args.at(i)),
                            this->args.at(i + 1))) {
        throw std::invalid_argument("Argumento no aceptado \"" +
                                    this->args.at(i) + " " +
                                    this->args.at(i + 1) + "\"");
      }
      this->opts.insert(
          {stringToCliOption(this->args.at(i)), this->args.at(i + 1)});
      i++;
    }
  }
  try {
    this->getOpts().at(TRACE_FILENAME);
  } catch (std::out_of_range& e) {
    // default trace file path
    this->opts.insert({TRACE_FILENAME, "data/art.trace.gz"});
  }
  try {
    this->getOpts().at(CYCLE_MUL);
  } catch (std::out_of_range& e) {
    // default CYCLE_MUL
    this->opts.insert({CYCLE_MUL, "1"});
  }

  try {
    this->getOpts().at(TAMANO_CACHE);
    this->getOpts().at(TAMANO_LINEA);
    this->getOpts().at(ASOCIATIVIDAD);
    this->getOpts().at(POLITICA_REMPLAZO);
    this->getOpts().at(MISS_PENALTY);
  } catch (std::out_of_range& e) {
    throw std::invalid_argument("Error: parámetros incompletos");
  }
  return;
}

std::map<CliOption, std::string> CLI::getOpts() { return this->opts; }
