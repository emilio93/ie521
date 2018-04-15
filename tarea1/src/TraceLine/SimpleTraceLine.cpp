
#include <string>

#include "TraceLine/SimpleTraceLine.hh"
#include "TraceLine/TraceLine.hh"
#include "Util.hh"

const std::string SimpleTraceLine::re(
    "\\s*#\\s+(0|1)\\s+([a-f0-9]{8})\\s+([0-9-]+)\\s*");
// # 0 300e20d8 2
// # 0 3026e398 5
// # 0 30192830 1
// # 1 30192830 3
// # 0 300049d0 1
// # 0 30004960 3
// # 0 30004a30 2

const std::string SimpleTraceLine::getRe() { return SimpleTraceLine::re; }

TraceLine* SimpleTraceLine::parse(std::string line) {
  int LS;
  long int Direccion;
  int IC;

  std::vector<std::string> items;
  if (Util::isRegexMatch(line, SimpleTraceLine::getRe())) {
    items = Util::regexMatches(line, SimpleTraceLine::getRe());
  }

  try {
    LS = std::stoi(items.at(0));
    Direccion = std::stoul(items.at(1), 0, 16);
    IC = std::stoi(items.at(2));
  } catch (std::invalid_argument& e) {
    std::cout << "std::invalid_argument what : " << e.what() << std::endl;
    return NULL;
  }
  TraceLine* traceLine = new SimpleTraceLine(LS, Direccion, IC);
  return traceLine;
}
SimpleTraceLine::SimpleTraceLine(int LS, long int Direccion, int IC) {
  this->setLS(LS);
  this->setDireccion(Direccion);
  this->setIC(IC);
}

int SimpleTraceLine::getLS() { return this->LS; }
long int SimpleTraceLine::getDireccion() { return this->Direccion; }
int SimpleTraceLine::getIC() { return this->IC; }

void SimpleTraceLine::setLS(int LS) { this->LS = LS; }
void SimpleTraceLine::setDireccion(long int Direccion) {
  this->Direccion = Direccion;
}
void SimpleTraceLine::setIC(int IC) { this->IC = IC; }