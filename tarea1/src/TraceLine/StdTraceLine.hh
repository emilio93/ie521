#ifndef CLASS_STD_TRACE_LINE
#define CLASS_STD_TRACE_LINE

#include <string>

#include "TraceLine/TraceLine.hh"

class StdTraceLine : public TraceLine {
 private:
  const static std::string re;
  long int Uop;
  long long pc;
  signed long int Src1;
  signed long int Src2;
  signed long int Dest;
  char Flags;
  char Branch;
  int LdSt;
  signed long long Immediate;
  long long MemAddress;
  long long FallthroughPC;
  long long TargetPC;
  std::string MacroOpcode;
  std::string MicroOpcode;

  explicit StdTraceLine(long int Uop,                // 32 bit decimal
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
                        long long TargetPC,          // 64bit hex
                        std::string MacroOpcode,     // String
                        std::string MicroOpcode      // String
                        );

 public:
  static TraceLine* parse(std::string line);

  const static std::string getRe();

  const static bool isLine();

  int getLS();
  long int getDireccion();
  int getIC();

  long int getUop();
  long long getPc();
  signed long int getSrc1();
  signed long int getSrc2();
  signed long int getDest();
  char getFlags();
  char getBranch();
  int getLdSt();
  signed long long getImmediate();
  long long getMemAddress();
  long long getFallthroughPC();
  long long getTargetPC();
  std::string getMacroOpcode();
  std::string getMicroOpcode();

  void setUop(long int Uop);
  void setPc(long long Pc);
  void setSrc1(signed long int Src1);
  void setSrc2(signed long int Src2);
  void setDest(signed long int Dest);
  void setFlags(char Flags);
  void setBranch(char Branch);
  void setLdSt(int LdSt);
  void setImmediate(signed long long Immediate);
  void setMemAddress(long long MemAddress);
  void setFallthroughPC(long long FallthroughPC);
  void setTargetPC(long long TargetPC);
  void setMacroOpcode(std::string MacroOpcode);
  void setMicroOpcode(std::string MicroOpcode);
};

#endif