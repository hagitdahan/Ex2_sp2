cmake_minimum_required(VERSION 3.28)
project(Ex2_sp)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ex2_sp 
        Algorithms.hpp
        Graph.cpp
        Graph.hpp
        GraphType.hpp
        Demo.cpp
        Algorithms.cpp
        Dijkstra.hpp
        Dijkstra.cpp
        BellmanFord.cpp
        BellmanFord.hpp
        TestCounter.cpp
        doctest.h
        Test.cpp)
