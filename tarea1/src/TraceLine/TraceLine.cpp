
#include <string>

#include "TraceLine/SimpleTraceLine.hh"
#include "TraceLine/TraceLine.hh"
#include "Util.hh"

//
/**
 * @Author: Emilio Rojas
 * @Date: 2018-04-15
 * @Desc: Returns a traceline
 */
TraceLine *TraceLine::makeTraceLine(std::string *traceLineStr) {
  return SimpleTraceLine::parse(traceLineStr);
}
