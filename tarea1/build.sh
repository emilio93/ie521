
# sudo add-apt-repository ppa:ubuntu-toolchain-r/test
# sudo apt-get update
# sudo apt-get install g++-7


mkdir -p bin
mkdir -p build
mkdir -p build/Cli
mkdir -p build/Cache
mkdir -p build/TraceLine
mkdir -p build/TraceFile
make
# g++ -Isrc/Cli -Isrc src/**/*.cpp src/*.cpp -o ./bin/cache -lboost_iostreams -lz -std=c++11
