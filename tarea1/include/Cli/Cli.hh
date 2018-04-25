#ifndef CLASS_CLI
#define CLASS_CLI

#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "Cache/Cache.hh"
#include "Cache/CacheRP.hh"
#include "Cli/CliOption.hh"
#include "TraceLine/TraceLine.hh"

class CLI {
 private:
  std::vector<std::string> args;

  std::map<CliOption, std::string> opts;

  void getPairs();

 public:
  explicit CLI(char* argv[]);

  std::map<CliOption, std::string> getOpts();

  void testCli(int argc, char* argv[]);
};

#endif