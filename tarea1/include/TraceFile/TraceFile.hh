#ifndef CLASS_TRACE_FILE
#define CLASS_TRACE_FILE

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

class TraceFile {
 private:
  std::ifstream file;
  std::string filepath;
  std::string line;
  boost::iostreams::filtering_istream in;

 public:
  TraceFile(std::string filepath);

  bool nextLine();
  std::string currLine();

  void reset();

  void countLines();
};

#endif
