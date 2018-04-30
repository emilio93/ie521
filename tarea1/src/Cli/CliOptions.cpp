#include "Cli/CliOption.hh"

std::string cliOptionToString(CliOption opt) {
  std::string option = "";
  switch (opt) {
    case TAMANO_CACHE:
      option = "-t";
      break;
    case TAMANO_LINEA:
      option = "-l";
      break;
    case ASOCIATIVIDAD:
      option = "-a";
      break;
    case POLITICA_REMPLAZO:
      option = "-rp";
      break;
    case MISS_PENALTY:
      option = "-mp";
      break;
    case TRACE_FILENAME:
      option = "-f";
      break;
    case CYCLE_MUL:
      option = "-c";
      break;
    default:
      option = "";
  }
  return option;
}

CliOption stringToCliOption(std::string option) {
  CliOption opt;
  if (option.compare("-t") == 0) {
    opt = TAMANO_CACHE;
  } else if (option.compare("-l") == 0) {
    opt = TAMANO_LINEA;
  } else if (option.compare("-a") == 0) {
    opt = ASOCIATIVIDAD;
  } else if (option.compare("-rp") == 0) {
    opt = POLITICA_REMPLAZO;
  } else if (option.compare("-mp") == 0) {
    opt = MISS_PENALTY;
  } else if (option.compare("-f") == 0) {
    opt = TRACE_FILENAME;
  } else if (option.compare("-c") == 0) {
    opt = CYCLE_MUL;
  } else {
    opt = NO_OPTION;
  }

  return opt;
}

bool isRequired(CliOption opt) {
  bool isRequired = false;
  switch (opt) {
    case TAMANO_CACHE:
    case TAMANO_LINEA:
    case ASOCIATIVIDAD:
    case POLITICA_REMPLAZO:
    case MISS_PENALTY:
      isRequired = true;
      break;
    case TRACE_FILENAME:
    case CYCLE_MUL:
      isRequired = false;
    default:
      isRequired = false;
  }
}

bool checkOption(CliOption opt) { return opt != NO_OPTION; }

bool checkOptionValue(CliOption opt, std::string value) {
  if (opt == TRACE_FILENAME) {
    return true;
  }
  if (opt == TAMANO_CACHE || opt == TAMANO_LINEA || opt == ASOCIATIVIDAD ||
      opt == MISS_PENALTY) {
    return Util::isInt(value);
  } else if (opt == CYCLE_MUL) {
    return Util::isFloat(value);
  } else if (opt == POLITICA_REMPLAZO) {
    return value.compare("LRU") == 0 || value.compare("NRU") == 0 ||
           value.compare("SRRIP") == 0 || value.compare("random") == 0;
  }
  return false;
}
