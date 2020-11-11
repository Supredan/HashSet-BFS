cmake_minimum_required(VERSION 3.17)
project(hw3)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Google_tests)
add_executable(hw3 main.cpp proj3.cpp proj3.hpp Wordset.cpp Wordset.hpp)