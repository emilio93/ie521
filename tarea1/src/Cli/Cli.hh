#ifndef CLASS_CLI
#define CLASS_CLI

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "Cli/CliOption.hh"
#include "TraceLine/TraceLine.hh"

class CLI {
 private:
  std::vector<std::string> args = std::vector<std::string>();
  std::map<CliOption, std::string> opts = std::map<CliOption, std::string>();

  bool hasFlag(std::string command);
  void reconstructCommand();
  void countArgs(char* argv[]);
  void getPairs();

 public:
  std::map<CliOption, std::string> getOpts();

  explicit CLI(char* argv[]);
  void testCli(int argc, char* argv[]);
};

#endif