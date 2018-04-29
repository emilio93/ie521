
#include <string>

#include "TraceLine/SimpleTraceLine.hh"
#include "TraceLine/TraceLine.hh"
#include "Util.hh"

TraceLine *TraceLine::makeTraceLine(std::string *traceLineStr) {
  return SimpleTraceLine::parse(traceLineStr);
}
