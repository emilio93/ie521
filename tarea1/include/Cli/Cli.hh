#ifndef CLASS_CLI
#define CLASS_CLI

#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "Cache/Cache.hh"
#include "Cache/CacheRP.hh"
#include "Cli/CliOption.hh"
#include "TraceLine/TraceLine.hh"

/**
 * @brief Defines Command Line Interface functionality.
 *
 */
class CLI {
 private:
  /**
   * @breif Input arguments via command line.
   *
   */
  std::vector<std::string> args;

  /**
   * @breif Read options via arguments.
   *
   */
  std::map<CliOption, std::string> opts;

  /**
   * @breif Read args to obtain options as a map.
   *
   */
  void getPairs();

 public:
  /**
   * @breif Constructor requires the args as a char array reference.
   *
   */
  explicit CLI(char* argv[]);

  /**
   * @breif Obtain read options.
   *
   */
  std::map<CliOption, std::string> getOpts();
};

#endif
