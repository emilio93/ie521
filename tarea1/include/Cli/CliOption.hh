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
  TRACE_FILENAME,
  NO_OPTION
};

/**
 * @brief converts the CliOption element to a string representation
 *
 * @param opt CliOption element to convert
 * @return std::string the string representation of the CliOption element
 */
std::string cliOptionToString(CliOption opt);

/**
 * @brief converts a matching string to a CliOption element or NO_OPTION if no
 * match is found.
 *
 * @param option string to convert
 * @return CliOption converted CliOption element
 */
CliOption stringToCliOption(std::string option);

/**
 * @brief Indicates if a CliOption is required to proceed with the program
 *
 * @param opt CliOption element to check if is required
 * @return true CliOption element is required
 * @return false CliOption element is not required
 */
bool isRequired(CliOption opt);

/**
 * @brief Check if a CliOption element is valid
 *
 * @param opt CliOption element to check
 * @return true CliOption element is valid
 * @return false CliOption element is not valid
 */
bool checkOption(CliOption opt);

/**
 * @brief Checks if the value to set the CliOption element is valid
 *
 * @param opt CliOption element to check validity
 * @param value value to check validity
 * @return true value is valid for the given CliOption element
 * @return false value is not valid for the given CliOption element
 */
bool checkOptionValue(CliOption opt, std::string value);

#endif
