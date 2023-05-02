# C++ String-to-Enum Benchmarking Experiment

This benchmarking experiment compares the performance of three different C++ data structures for translating string commands into their corresponding enum values:

- `std::map`
- `std::unordered_map`
- `std::array`

### Test Data
The test data is generated using the `genTestData()` function, which produces a `std::vector` of `std::string` instances. 
The data consists of 50% valid commands and 50% invalid commands, with a total of `TEST_DATA_SIZE` elements (default 1,024 x 1,024 elements).

### Benchmark Functions

The benchmarking experiment consists of three functions:

- `BM_std_map`: Uses a `std::map<std::string_view, COMMAND>` to perform the translation.
- `BM_std_unordered_map`: Uses a `std::unordered_map<std::string_view, COMMAND>` to perform the translation.
- `BM_std_array`: Uses a `std::array<std::pair<std::string_view, COMMAND>, 10>` to perform the translation.
Each benchmark function measures the time it takes to translate the test data using the respective data structure.

### Results

| Benchmark            | Time        | CPU         | Comment          |
|----------------------|-------------|-------------|------------------|
| BM_std_map           | 20174349 ns | 20118676 ns | 7.8 times slower |
| BM_std_unordered_map | 14961303 ns | 14928499 ns | 5 times slower   |
| BM_std_array         | 2584919 ns  | 2579549 ns  |                  |


### Usage
To run the benchmarking experiment, simply compile and execute the provided C++ code. Make sure that the benchmark 
library is installed and linked properly.

