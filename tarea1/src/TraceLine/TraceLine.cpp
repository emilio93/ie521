
#include <string>

#include "TraceLine/SimpleTraceLine.hh"
#include "TraceLine/StdTraceLine.hh"
#include "TraceLine/TraceLine.hh"
#include "Util.hh"

//
/**
 * @Author: Emilio Rojas
 * @Date: 2018-04-15
 * @Desc:  Check the TraceLine implementation regular expresion against
 * given line to decide which implementation to instantiate.
 * fails to not instantiate nothing and return NULL.
 */
TraceLine *TraceLine::makeTraceLine(std::string traceLineStr) {
  if (Util::isRegexMatch(traceLineStr, StdTraceLine::getRe())) {
    return StdTraceLine::parse(traceLineStr);
  } else if (Util::isRegexMatch(traceLineStr, SimpleTraceLine::getRe())) {
    return SimpleTraceLine::parse(traceLineStr);
  }
  return NULL;
}