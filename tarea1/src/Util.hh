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
 * @Date: 2018-04-14
 * @Desc: Util(Utility) class provides functions that are abstract enough
 * to be used in many contexts.
 */
class Util {
 private:
  template <typename Out>
  static void split(const std::string& s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      *(result++) = item;
    }
  }

 public:
  static bool isInt(const std::string& s) {
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
      return false;

    char* p;
    std::strtol(s.c_str(), &p, 10);

    return (*p == 0);
  }

  static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
  }

  static bool isRegexMatch(const std::string& in, const std::string& re) {
    std::smatch m;
    return std::regex_match(in, m, std::regex(re));
  }

  static std::vector<std::string> regexMatches(const std::string& in,
                                               const std::string& re) {
    std::vector<std::string> matches;
    std::vector<std::string>::iterator it;
    std::smatch m;
    std::regex_search(in, m, std::regex(re));

    if (m.empty()) {
      std::cout << "input=[" << in << "], regex=[" << re << "]: NO MATCH\n";
    } else {
      it = matches.begin();
      for (std::size_t n = 1; n < m.size(); ++n) {
        std::string str;
        str = m[m.size() - n].str().data();
        it = matches.insert(it++, str);
      }
    }
    return matches;
  }
};

#endif