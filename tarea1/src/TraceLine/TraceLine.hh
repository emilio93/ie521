#ifndef ABSTRACT_CLASS_TRACE_LINE
#define ABSTRACT_CLASS_TRACE_LINE

#include <string>

//! Single serialized line from a trace file
/*!
 * A line from a trace file show info...
 */
class TraceLine {
 private:
 public:
  ~TraceLine() { ; }
  virtual int getLS() = 0;
  virtual long int getDireccion() = 0;
  virtual int getIC() = 0;
  virtual void update(std::string line) = 0;

  static TraceLine *makeTraceLine(std::string traceLineStr);
};

#endif