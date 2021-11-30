cmake_minimum_required(VERSION 3.20)
project(aoc21)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(cpr)
find_package(fmt)

add_library(solutions STATIC)
target_link_libraries(solutions
    PRIVATE
        fmt::fmt
)

add_executable(aoc21 main.cpp input.cpp)
target_link_libraries(aoc21
    PRIVATE
        solutions
        cpr::cpr
        fmt::fmt
)

enable_testing()
find_package(GTest)
include(GoogleTest)

add_executable(aoc21-test)
gtest_discover_tests(aoc21-test)
target_link_libraries(aoc21-test
        PRIVATE
        solutions
        GTest::GTest
)

add_subdirectory(day00)
