# Cache Memory Simulation

This project simulates a cache memory with the given parameters in many replacement policies scenarios.

## Compiling

Install basic developing tools which may not be already in your system

```bash
sudo apt-get update
sudo apt-get install build-essential software-properties-common -y
```

Thits project has been ested with ```g++ 7.2.0```. Check `g++` version:

```bash
which g++
```

In any case, standard `c++17` is required.

Uses zlib and libboost .

```bash
# install zlib
sudo apt-get install zlib1g
sudo apt-get install zlib1g-dev
# install libboost_iostreams
sudo apt-get install libboost-iostreams-dev
```

Compiles via make(installed by default in most systems):

```bash
make
```

_This has to be run from the folder which contains the Makefile._

This generates a symlink to an excecutable, `./cache`.

## Running

### Example of use

```bash
./bin/cache -t 32 -a 4 -l 32 -mp 30 -rp LRU
```

These flags must be declared

- `-t`: cache size in kilobytes(kB). Must be an integer.
- `-a`: cache associativity(1,2,4,...). Must be an integer.
- `-l`: cache block size in bytes. Must be an integer.
- `-mp`: miss penalty in cycles. Must be an integer.
- `-rp`: Replacement policy. Must be any of the implemented replacement policies(case sensitive):
  - `LRU`
  - `NRU`
  - `SRRIP`
  - `random`

If any of the previous flags is not defined or value is invalid, the program will stop.

Optional flags:

```bash
./bin/cache -t 32 -a 4 -l 32 -mp 30 -rp LRU -f data/mcf.trace.gz -c 1.05
```

- `-f`: filepath to gunziped trace. Defaults to `data/art.trace.gz`. Program will stop if problems with file are found(doesn't exist, incorrect format, etc).
- `-c`: cycle multiplier. Defaults to 1. Float type.

Any other tag will be ignored.

## Running Automated Tests

Place all traces to be analyzed in the `./data` folder.
Run the script:

```bash
./scripts/runTests.sh
```
