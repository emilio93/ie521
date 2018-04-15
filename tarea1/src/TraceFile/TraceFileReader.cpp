#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <fstream>
#include <iostream>
#include <string>

class TraceFileReader {
  std::ifstream file;

 public:
  TraceFileReader(std::string filepath) {
    this->file =
        std::ifstream(filepath, std::ios_base::in | std::ios_base::binary);
  }

  void countLines() {
    try {
      boost::iostreams::filtering_istream in;
      in.push(boost::iostreams::gzip_decompressor());
      in.push(file);
      std::string a;
      int i = 0;
      for (std::string str; std::getline(in, str);) {
        i++;
      }
      std::cout << i << std::endl;
    } catch (boost::iostreams::zlib_error& e) {
      std::cout << "Error: " << e.what() << std::endl
                << boost::iostreams::zlib::data_error << std::endl
                << e.code() << std::endl
                << e.error() << std::endl;
    }
  }
};

int main() {
  const clock_t begin_time = clock();
  TraceFileReader* tfr = new TraceFileReader("./data/art.trace.gz");
  tfr->countLines();
  std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
}