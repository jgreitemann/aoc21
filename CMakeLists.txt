cmake_minimum_required(VERSION 3.20)
project(aoc21)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(cpr)

add_executable(aoc21 main.cpp)
target_link_libraries(aoc21 PRIVATE cpr::cpr)
