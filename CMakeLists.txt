cmake_minimum_required(VERSION 3.0)

project(alg-search)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER "clang++")

add_executable(alg-search
    main.cpp
    MatrixGraph.h
    MatrixGraph.cpp
    Algorithms.h
    Algorithms.cpp
    Utils.h
    tinyxml2/tinyxml2.h
    tinyxml2/tinyxml2.cpp
)

target_link_libraries(alg-search)