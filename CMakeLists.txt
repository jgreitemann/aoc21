cmake_minimum_required(VERSION 3.20)
project(aoc21)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(fmt)
find_package(httplib)
find_package(OpenSSL)

include(FetchContent)

FetchContent_Declare(rangesnext
    GIT_REPOSITORY https://github.com/cor3ntin/rangesnext.git
    GIT_TAG        056d3d22f007f8eef1692954660be8e77a50e315
)
FetchContent_Populate(rangesnext)
add_library(rangesnext INTERFACE)
target_include_directories(rangesnext INTERFACE ${rangesnext_SOURCE_DIR}/include)

FetchContent_Declare(mdspan
    GIT_REPOSITORY https://github.com/kokkos/mdspan.git
    GIT_TAG        a0aa4d9a3c401f23b18db91cac68fbb6b5bd0528
)
FetchContent_Populate(mdspan)
add_library(mdspan INTERFACE)
target_include_directories(mdspan INTERFACE ${mdspan_SOURCE_DIR}/include)

add_library(solutions STATIC utils.cpp)
target_link_libraries(solutions
    PRIVATE
        fmt::fmt
    PUBLIC
        rangesnext
        mdspan
)

add_executable(aoc21 main.cpp input.cpp)
target_link_libraries(aoc21
    PRIVATE
        solutions
        fmt::fmt
        httplib::httplib
        OpenSSL::OpenSSL
)
target_compile_definitions(aoc21
    PRIVATE
        CPPHTTPLIB_OPENSSL_SUPPORT
)

enable_testing()
find_package(GTest)
include(GoogleTest)

add_executable(aoc21-test)
gtest_discover_tests(aoc21-test)
target_link_libraries(aoc21-test
    PRIVATE
        solutions
        fmt::fmt
        GTest::GTest
        rangesnext
)

add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)
add_subdirectory(day07)
add_subdirectory(day08)
add_subdirectory(day09)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
add_subdirectory(day13)
add_subdirectory(day14)
