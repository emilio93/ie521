#ifndef CLASS_SIMPLE_TRACE_LINE
#define CLASS_SIMPLE_TRACE_LINE

#include <string>
#include "TraceLine/TraceLine.hh"

/**
 * @brief Implementa a TraceLine
 *
 */
class SimpleTraceLine final : public TraceLine {
 private:
  /**
   * @brief Construct a new Simple Trace Line object. A private constructor
   * makes sure this class is only instantiated via TraceLine::makeTraceLine(std::string)
   *
   * @param LS initial ls value
   * @param Direccion initial mem address
   * @param IC initial ic value
   */
  explicit SimpleTraceLine(int LS, long int Direccion, int IC);

 public:

  /**
   * @brief parses a line and returns a new instance of a SimpleTraceLine
   *
   * @param line string to be parsed
   * @return TraceLine* TraceLine created
   */
  static TraceLine* parse(std::string* line);

  /**
   * @brief updates the trace line from a new string
   *
   * @param line string containing the updated info
   */
  void update(std::string* line);

  /**
   * @brief get the ls value
   *
   * @return int the ls value
   */
  int getLS();

  /**
   * @brief Get the mem address
   *
   * @return long int the mem address
   */
  long int getDireccion();

  /**
   * @brief get the ic
   *
   * @return int the ic
   */
  int getIC();

  /**
   * @brief set the ls value
   *
   * @param LS ls value to be set
   */
  void setLS(int LS);

  /**
   * @brief set the mem address
   *
   * @param Direccion the mem address to be set
   */
  void setDireccion(long int Direccion);

  /**
   * @brief set the ic value
   *
   * @param IC the ic value to be set
   */
  void setIC(int IC);
};

#endif
