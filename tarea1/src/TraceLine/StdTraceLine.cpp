#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "StdTraceLine.hh"
#include "Util.hh"

// clang-format off
const std::string StdTraceLine::re("\\s*([0-9]+)\\s+([a-f0-9]+)\\s+([0-9-]+)\\s+([0-9-]+)\\s+([0-9-]+)\\s+([RW-]{1})\\s+([NT-]{1})\\s+([LS-]{1})\\s+([0-9-]+)\\s+([a-f0-9]+)\\s+([a-f0-9]+)\\s+([a-f0-9]+)\\s+([a-zA-Z0-9_]+)\\s+([a-zA-Z0-9_]+)\\s*");
// 0 1      2  3  4  5 6 7         8            9       10           11     12       13
// 2 400658 18 44 18 - - -         0            0       40065f            0 MULSD    FP_MUL_DOUBLE
// 1 40065f 17 18 17 - - -         0            0       400663            0 ADDSD    FP_ADD_DOUBLE
// 1 400663 14 -1 14 W - -         8            0       400667            0 ADD      ADD_IMM
// 1 400667 15 -1 15 W - -         8            0       40066b            0 ADD      ADD_IMM
// 1 40066b 12 -1 12 - - -         1            0       40066e            0 DEC      SUB_IMM
// 1 40066e -1 -1 -1 R T -       -32            0       400670       400650 J        JMP_IMM
// 1 400650 -1 15 13 - - L         0       7d7210       400653            0 MOV      LOAD
// clang-format on

const std::string StdTraceLine::getRe() { return StdTraceLine::re; }

StdTraceLine::StdTraceLine(long int Uop,                // 32 bit decimal
                           long long pc,                // 64 bit hex
                           signed long int Src1,        // 32 bit signed decimal
                           signed long int Src2,        // 32 bit signed decimal
                           signed long int Dest,        // 32 bit signed decimal
                           char Flags,                  // Single char(R, W, -)
                           char Branch,                 // single char(T, N, -)
                           int LdSt,                    // single char(L, S, -)
                           signed long long Immediate,  // 64 bit signed
                           long long MemAddress,        // 64 bit hex
                           long long FallthroughPC,     // 64 bit hex
                           long long TargetPC,          // 64 bit hex
                           std::string MacroOpcode,     // String
                           std::string MicroOpcode      // String
                           ) {
  this->setUop(Uop);
  this->setPc(pc);
  this->setSrc1(Src1);
  this->setSrc2(Src2);
  this->setDest(Dest);
  this->setFlags(Flags);
  this->setBranch(Branch);
  this->setLdSt(LdSt);
  this->setImmediate(Immediate);
  this->setMemAddress(MemAddress);
  this->setFallthroughPC(FallthroughPC);
  this->setTargetPC(TargetPC);
  this->setMacroOpcode(MacroOpcode);
  this->setMicroOpcode(MicroOpcode);
}

TraceLine* StdTraceLine::parse(std::string line) {
  long int Uop;
  long long pc;
  signed long int Src1;
  signed long int Src2;
  signed long int Dest;
  char Flags;
  char Branch;
  char LdSt;
  signed long long Immediate;
  long long MemAddress;
  long long FallthroughPC;
  long long TargetPC;
  std::string MacroOpcode;
  std::string MicroOpcode;

  std::vector<std::string> items;
  if (Util::isRegexMatch(line, StdTraceLine::getRe())) {
    items = Util::regexMatches(line, StdTraceLine::getRe());
  }

  try {
    Uop = std::stol(items.at(0));

    // item is in base-16
    pc = std::stoull(items.at(1), 0, 16);

    Src1 = std::stol(items.at(2));

    Src2 = std::stol(items.at(3));

    Dest = std::stol(items.at(4));

    // using ASCII
    // Possible values   representation(val & 0b11)>>6
    // 2D 00101101 -     01 -> 1
    // 52 01010010 R     10 -> 2
    // 57 01010111 W     11 -> 3
    // short int Flags = (items.at(5).at(0) & 0b11);
    Flags = items.at(5).at(0);

    // using ASCII
    // Possible values   representation(val & 0b11)>>6
    // 2D 00101101 -     01 -> 1
    // 4E 01001110 N     10 -> 2
    // 54 01010100 T     00 -> 0
    // short int Branch = (items.at(6).at(0) & 0b11);
    Branch = items.at(6).at(0);

    // using ASCII
    // Possible values   representation(val & 0b11)
    // 2D 00101101 -     01 -> 1
    // 4C 01001100 L     10 -> 0
    // 53 01010011 S     00 -> 3
    // int LdSt = (items.at(7).at(0) & 0b11);
    LdSt = items.at(7).at(0);

    Immediate = std::stoll(items.at(8));

    MemAddress = std::stoull(items.at(9));

    FallthroughPC = std::stoull(items.at(10));

    TargetPC = std::stoull(items.at(11));

    MacroOpcode = items.at(12);

    MicroOpcode = items.at(13);

  } catch (std::invalid_argument& e) {
    std::cout << "std::invalid_argument what : " << e.what() << std::endl;
    return NULL;
  }

  // Items come in the same order as the Trace constructor parameters
  //

  // To be sure that its ok to delete this; in destructur:
  //   Trace Instances must be created via new
  //   Dont refer to this anymore
  // https://isocpp.org/wiki/faq/freestore-mgmt#delete-this
  TraceLine* traceLine = new StdTraceLine(
      Uop, pc, Src1, Src2, Dest, Flags, Branch, LdSt, Immediate, MemAddress,
      FallthroughPC, TargetPC, MacroOpcode, MicroOpcode);
  return traceLine;
};

int StdTraceLine::getLS() { return this->getLdSt() == 'S' ? 1 : 0; }
long int StdTraceLine::getDireccion() { return this->getMemAddress(); }
int StdTraceLine::getIC() { return this->getPc(); }

long int StdTraceLine::getUop() { return this->Uop; }

long long StdTraceLine::getPc() { return this->pc; }

signed long int StdTraceLine::getSrc1() { return this->Src1; }

signed long int StdTraceLine::getSrc2() { return this->Src2; }

signed long int StdTraceLine::getDest() { return this->Dest; }

char StdTraceLine::getFlags() { return this->Flags; }

char StdTraceLine::getBranch() { return this->Branch; }

int StdTraceLine::getLdSt() { return this->LdSt; }

signed long long StdTraceLine::getImmediate() { return this->Immediate; }

long long StdTraceLine::getMemAddress() { return this->MemAddress; }

long long StdTraceLine::getFallthroughPC() { return this->FallthroughPC; }

long long StdTraceLine::getTargetPC() { return this->TargetPC; }

std::string StdTraceLine::getMacroOpcode() { return this->MacroOpcode; }

std::string StdTraceLine::getMicroOpcode() { return this->MicroOpcode; }

void StdTraceLine::setUop(long int Uop) { this->Uop = Uop; }

void StdTraceLine::setPc(long long pc) { this->pc = pc; }

void StdTraceLine::setSrc1(signed long int Src1) { this->Src1 = Src1; }

void StdTraceLine::setSrc2(signed long int Src2) { this->Src2 = Src2; }

void StdTraceLine::setDest(signed long int Dest) { this->Dest = Dest; }

void StdTraceLine::setFlags(char Flags) { this->Flags = Flags; }

void StdTraceLine::setBranch(char Branch) { this->Branch = Branch; }

void StdTraceLine::setLdSt(int LdSt) { this->LdSt = LdSt; }

void StdTraceLine::setImmediate(signed long long Immediate) {
  this->Immediate = Immediate;
}

void StdTraceLine::setMemAddress(long long MemAddress) {
  this->MemAddress = MemAddress;
}

void StdTraceLine::setFallthroughPC(long long FallthroughPC) {
  this->FallthroughPC = FallthroughPC;
}

void StdTraceLine::setTargetPC(long long TargetPC) {
  this->TargetPC = TargetPC;
}

void StdTraceLine::setMacroOpcode(std::string MacroOpcode) {
  this->MacroOpcode = MacroOpcode;
}

void StdTraceLine::setMicroOpcode(std::string MicroOpcode) {
  this->MicroOpcode = MicroOpcode;
}
