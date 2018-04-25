# Cache Memory Simulation
This project simulates a cache memory with the given parameters in many replacement policies scenarios.

## Compiling
Uses zlib and libboost .
```
# install zlib
sudo apt-get install zlib1g 
sudo apt-get install zlib1g-dev
# install libboost_iostreams
sudo apt-get install libboost-iostreams-dev 
```

Compile via build script.
```
./build.sh
``` 
This generates an excecutable file `./bin/cache`.

Or modify the current compiling command.
```
g++ -Isrc/Cli -Isrc src/**/*.cpp src/*.cpp -o ./bin/cache -lboost_iostreams -lz 
```

This has to be run from the folder which contains the src folder.

## Running

All the flags must be declared
```
./bin/cache -t 32 -a 4 -l 32 -mp 30 -rp LRU
```
 - `-t`: cache size in kilobytes(kB).
 - `-a`: cache associativity(1,2,4,...).
 - `-l`: cache block size in bytes.
 - `-mp`: miss penalty in cycles.
 - `-rp`: Replacement policy(LRU, NRU, SRRIP, random).

Any other tag will be ignored.

Requires a trace file `./data/art.trace.gz`.

> 
> **TODO** Optional flag `-f` allows any tracefile to be used as > inputs fot the simulation.
> ```
> ./bin/cache -t 32 -a 4 -l 32 -mp 30 -rp LRU -f ./data/art.trace.gz
> ```
> **TODO** Enable uncommpressed traces.
