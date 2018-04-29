#ifndef ABSTRACT_CLASS_TRACE_LINE
#define ABSTRACT_CLASS_TRACE_LINE

#include <string>

//! Single serialized line from a trace file
/*!
 * A line from a trace file show info...
 */
class TraceLine {
 protected:

  /**
   * @brief Load/Store flag indicates if line did a load or store action
   *
   */
  int LS;

  /**
   * @brief the mem address requested by the line
   *
   */
  long int Direccion;

  /**
   * @brief the quantity of previous instructions which did not access the memory
   *
   */
  int IC;
 public:

  /**
   * @brief Destroy the Trace Line object
   *
   */
  ~TraceLine() { ; }

  /**
   * @brief get the load/store flag. 0 is load, 1 is store
   *
   * @return int 0 if load, 1 if flag
   */
  virtual int getLS() = 0;

  /**
   * @brief Get the read address
   *
   * @return long int the read address converted from hex representation
   */
  virtual long int getDireccion() = 0;

  /**
   * @brief get the previous instruction counts which did not access the memory
   *
   * @return int instruction count
   */
  virtual int getIC() = 0;

  /**
   * @brief update the traceline by reading a string which should be formatted
   *
   * @param line the formated string to be read
   */
  virtual void update(std::string* line) = 0;

  /**
   * @brief Identifies the format of a line and creates the corresponding TraceLine implementation
   *
   * @param traceLineStr the string to be identified
   * @return TraceLine* the created TraceLine
   */
  static TraceLine* makeTraceLine(std::string* traceLineStr);
};

#endif
