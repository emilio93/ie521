#ifndef ENUM_CLI_OPTION
#define ENUM_CLI_OPTION

#include <exception>
#include <string>

#include "Util.hh"

//! Cli options.
/*!
 * Options which can or must be used during the cli applicaction use
 */
enum CliOption {
  TAMANO_CACHE,
  TAMANO_LINEA,
  ASOCIATIVIDAD,
  POLITICA_REMPLAZO,
  MISS_PENALTY,
  NO_OPTION
};

std::string cliOptionToString(CliOption opt);

CliOption stringToCliOption(std::string option);

bool isRequired(CliOption opt);

bool checkOption(CliOption opt);

bool checkOptionValue(CliOption opt, std::string value);

#endif