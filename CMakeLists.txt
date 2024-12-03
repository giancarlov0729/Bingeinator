cmake_minimum_required(VERSION 3.29)
project(Bingeinator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

add_executable(Bingeinator
    src/main.cpp
        src/MaxHeap.h
        src/SplayTree.h)
