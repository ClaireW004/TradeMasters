cmake_minimum_required(VERSION 3.26)
project(TradeMasters)

set(CMAKE_CXX_STANDARD 17)

add_executable(TradeMasters main.cpp
        AdjacencyList.h
        AdjacencyList.cpp
        fileRead.h
        AdjacencyMatrix.cpp
        AdjacencyMatrix.h)