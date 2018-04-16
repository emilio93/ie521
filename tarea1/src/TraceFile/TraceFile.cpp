#include "TraceFile/TraceFile.hh"

TraceFile::TraceFile(std::string filepath) {
  this->filepath = filepath;
  this->reset();
}

void TraceFile::reset() {
  try {
    this->file = std::ifstream(this->filepath,
                               std::ios_base::in | std::ios_base::binary);
    this->in.push(boost::iostreams::gzip_decompressor());
    this->in.push(this->file);
  } catch (boost::iostreams::zlib_error& e) {
    std::cout << "Error: " << e.what() << std::endl
              << boost::iostreams::zlib::data_error << std::endl
              << e.code() << std::endl
              << e.error() << std::endl;
  }
}

bool TraceFile::nextLine() {

  std::string* str = new std::string();
  if (!std::getline(this->in, *str)) {
    return false;
  }
  this->line = str;
  return true;
}

std::string TraceFile::currLine() {
  return *this->line;
}


void TraceFile::countLines() {
  try {
    boost::iostreams::filtering_istream in;
    in.push(boost::iostreams::gzip_decompressor());
    in.push(file);
    std::string a;
    int i = 0;
    for (std::string str; std::getline(in, str);) {
      i++;
    }
    std::cout << std::dec << i << std::endl;
  } catch (boost::iostreams::zlib_error& e) {
    std::cout << "Error: " << e.what() << std::endl
              << boost::iostreams::zlib::data_error << std::endl
              << e.code() << std::endl
              << e.error() << std::endl;
  }
}