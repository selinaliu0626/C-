cmake_minimum_required(VERSION 3.17)
project(Project3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project3 main.cpp Vertex.h Vertex.cpp Graph.h Graph.cpp)
include_directories(/usr/local/include/)