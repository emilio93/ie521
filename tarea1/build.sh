
mkdir -p bin
g++ -Isrc/Cli -Isrc src/**/*.cpp src/*.cpp -o ./bin/cache -lboost_iostreams -lz 
