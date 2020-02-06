cmake_minimum_required(VERSION 3.0.0)
project(tutorial1 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tutorial1 main.cpp)
target_include_directories(tutorial1 PUBLIC "/usr/local/Cellar/boost/1.70.0/include")