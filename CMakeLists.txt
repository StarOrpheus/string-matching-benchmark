cmake_minimum_required(VERSION 3.25)
project(parse_command_benchmark)

set(CMAKE_CXX_STANDARD 23)

find_package(benchmark CONFIG REQUIRED)

add_executable(parse_command_benchmark main.cpp)
target_link_libraries(parse_command_benchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)