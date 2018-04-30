#ifndef UTIL_CLASS
#define UTIL_CLASS

#include <exception>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @Author: Emilio Rojas
 * @Desc: Util(Utility) class provides static functions that are abstract enough
 * to be used in many contexts.
 */
class Util {
 private:
  template <typename Out>
  //! Split function helper
  static void split(const std::string& s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      *(result++) = item;
    }
  }

 public:
  //! Checks if the given input string is an int.
  static bool isInt(const std::string& s) {
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
      return false;
    char* p;
    std::strtol(s.c_str(), &p, 10);
    return (*p == 0);
  }

  //! Checks if the given input string is a float.
  static bool isFloat(const std::string& s) {
    std::istringstream iss(s);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
  }

  //! Splits a string with a given delimiter.
  static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
  }

  //! Checks for a regex match
  static bool isRegexMatch(const std::string& in, const std::string& re) {
    std::smatch m;
    return std::regex_match(in, m, std::regex(re));
  }

  //! Returns a vector of strings with the regex matches, 'in' against regex
  //! string 're'.
  static std::vector<std::string>* regexMatches(
      const std::string& in, const std::string& re,
      std::vector<std::string>* matches) {
    std::vector<std::string>::iterator it;
    std::smatch m;
    std::regex_search(in, m, std::regex(re));

    if (m.empty()) {
      std::cout << "input=[" << in << "], regex=[" << re << "]: NO MATCH\n";
    } else {
      it = matches->begin();
      for (std::size_t n = 1; n < m.size(); ++n) {
        std::string str;
        str = m[m.size() - n].str().data();
        it = matches->insert(it++, str);
      }
    }
    return matches;
  }
};

#endif
