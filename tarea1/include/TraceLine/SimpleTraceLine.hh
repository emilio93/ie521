#ifndef CLASS_SIMPLE_TRACE_LINE
#define CLASS_SIMPLE_TRACE_LINE

#include <string>
#include "TraceLine/TraceLine.hh"

class SimpleTraceLine final : public TraceLine {
 private:
  int LS;
  long int Direccion;
  int IC;

  explicit SimpleTraceLine(int LS, long int Direccion, int IC);

 public:
  static TraceLine* parse(std::string* line);

  void update(std::string* line);  

  int getLS();
  long int getDireccion();
  int getIC();

  void setLS(int LS);
  void setDireccion(long int Direccion);
  void setIC(int IC);
};

#endif
