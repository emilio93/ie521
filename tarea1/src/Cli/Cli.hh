#ifndef CLASS_CLI
#define CLASS_CLI

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "Cli/CliOption.hh"
#include "Cache/Cache.hh"
#include "Cache/CacheRP.hh"
#include "TraceLine/TraceLine.hh"

class CLI {
 private:
  std::vector<std::string> args = std::vector<std::string>();
  
  std::map<CliOption, std::string> opts = std::map<CliOption, std::string>();

  void getPairs();

 public:
  explicit CLI(char* argv[]);

  std::map<CliOption, std::string> getOpts();

  void testCli(int argc, char* argv[]);
};

#endif