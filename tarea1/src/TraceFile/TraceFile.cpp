#include "TraceFile/TraceFile.hh"

TraceFile::TraceFile(std::string filepath) {
  this->curTraceLine = NULL;
  this->line = NULL;
  this->filepath = filepath;
  try {
    this->reset();
  } catch (boost::iostreams::zlib_error& e) {
    throw e;
  }
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
    throw e;
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

std::ifstream* TraceFile::getFile() { return &this->file; }

std::string* TraceFile::getFilepath() { return &this->filepath; }

std::string* TraceFile::getLine() { return this->line; }

boost::iostreams::filtering_istream* TraceFile::getIn() { return &this->in; }

void TraceFile::setLine(std::string* line) { this->line = line; }

void TraceFile::setFilepath(std::string filepath) { this->filepath = filepath; }
