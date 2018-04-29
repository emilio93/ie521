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

/**
 * @brief a TraceFile enables reading a .trace.gz file for cache simulation
 *
 */
class TraceFile {
 private:
  /**
   * @brief file input stream
   *
   */
  std::ifstream file;

  /**
   * @brief trace file path
   *
   */
  std::string filepath;

  /**
   * @brief a reference to a single line of the trace file
   *
   */
  std::string* line;

  /**
   * @brief stream filtering to read the compressed data
   *
   */
  boost::iostreams::filtering_istream in;

  /**
   * @brief the TraceLine being read
   *
   */
  TraceLine* curTraceLine;

  /**
   * @brief set the Line object
   *
   * @param line
   */
  void setLine(std::string* line);

  /**
   * @brief set the filepath
   *
   * @param filepath
   */
  void setFilepath(std::string filepath);

  /**
   * @brief resets the file reader to the start of the set filepath
   *
   */
  void reset();

  /**
   * @brief get the file stream
   *
   * @return std::ifstream* file stream
   */
  std::ifstream* getFile();

  /**
   * @brief Get the stream filtering
   *
   * @return boost::iostreams::filtering_istream* stream filtering
   */
  boost::iostreams::filtering_istream* getIn();

 public:

  /**
   * @brief Construct a new Trace File object
   *
   * @param filepath
   */
  TraceFile(std::string filepath);

  /**
   * @brief Destroy the Trace File object
   *
   */
  ~TraceFile();

  /**
   * @brief Retrieves next line and indicates if indeed there was a next line
   *
   * @return true if there is a next line
   * @return false if there is not a next line
   */
  bool nextLine();

  /**
   * @brief get the filepath
   *
   * @return std::string* filepath
   */
  std::string* getFilepath();

  /**
   * @brief get the current line
   *
   * @return std::string* the last read line
   */
  std::string* getLine();
};

#endif
