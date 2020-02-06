cmake_minimum_required(VERSION 3.0.0)
project(string_alg VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(string_alg main.cpp)
target_include_directories(string_alg PUBLIC "/usr/local/Cellar/boost/1.70.0/include")