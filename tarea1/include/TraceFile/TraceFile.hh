#ifndef CLASS_TRACE_FILE
#define CLASS_TRACE_FILE

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include "TraceLine/TraceLine.hh"

class TraceFile {
 private:
  std::ifstream file;
  std::string filepath;
  std::string* line;
  boost::iostreams::filtering_istream in;

  TraceLine* curTraceLine;

  void setLine(std::string* line);
  void setFilepath(std::string filepath);

 public:
  TraceFile(std::string filepath);
  ~TraceFile();

  TraceLine* getTraceLine();

  bool nextLine();
  std::string* currLine();

  void reset();

  void countLines();

  std::ifstream* getFile();
  std::string* getFilepath();
  std::string* getLine();
  boost::iostreams::filtering_istream* getIn();
};

#endif
