
#include <string>
#include <sstream>

#include <boost/algorithm/string/split.hpp>

#include "TraceLine/SimpleTraceLine.hh"
#include "TraceLine/TraceLine.hh"
#include "Util.hh"

TraceLine* SimpleTraceLine::parse(std::string* line) {
  std::istringstream iss(*line);
  std::string s;

  std::getline(iss, s, ' ');
  // #

  std::getline(iss, s, ' ');
  int LS = std::stoi(s);

  std::getline(iss, s, ' ');
  long int Direccion = std::stoul(s, 0, 16);

  std::getline(iss, s, ' ');
  int IC = std::stoi(s);

  return new SimpleTraceLine(LS, Direccion, IC);
}

SimpleTraceLine::SimpleTraceLine(int LS, long int Direccion, int IC) {
  this->setLS(LS);
  this->setDireccion(Direccion);
  this->setIC(IC);
};

void SimpleTraceLine::update(std::string* line) {
  std::istringstream iss(*line);
  std::string s;

  std::getline(iss, s, ' ');
  // #

  std::getline(iss, s, ' ');
  this->setLS(std::stoi(s));

  std::getline(iss, s, ' ');
  this->setDireccion(std::stoul(s, 0, 16));

  std::getline(iss, s, ' ');
  this->setIC(std::stoi(s));
}

int SimpleTraceLine::getLS() { return this->LS; }

long int SimpleTraceLine::getDireccion() { return this->Direccion; }

int SimpleTraceLine::getIC() { return this->IC; }

void SimpleTraceLine::setLS(int LS) { this->LS = LS; }

void SimpleTraceLine::setDireccion(long int Direccion) {
  this->Direccion = Direccion;
}

void SimpleTraceLine::setIC(int IC) { this->IC = IC; }
