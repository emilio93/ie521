#include "TraceFile/TraceFile.hh"

TraceFile::TraceFile(std::string filepath) {
  this->curTraceLine = NULL;
  this->line = NULL;
  this->filepath = filepath;
  this->reset();
}

TraceFile::~TraceFile() {
  delete this->line;
  this->line = NULL;
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
  if (this->line != NULL) delete this->line;

  std::string* str = new std::string();
  if (!std::getline(this->in, *str)) {
    return false;
  }
  this->line = str;

  return true;
}

TraceLine* TraceFile::getTraceLine() {
  // std::cout << this->file;
  if (this->curTraceLine == NULL) {
    // this->curTraceLine = TraceLine::makeTraceLine();
  }
  return NULL;
}

std::string* TraceFile::currLine() { return this->getLine(); }

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

std::ifstream* TraceFile::getFile() { return &this->file; }

std::string* TraceFile::getFilepath() { return &this->filepath; }

std::string* TraceFile::getLine() { return this->line; }

boost::iostreams::filtering_istream* TraceFile::getIn() { return &this->in; }

void TraceFile::setLine(std::string* line) { this->line = line; }

void TraceFile::setFilepath(std::string filepath) { this->filepath = filepath; }
