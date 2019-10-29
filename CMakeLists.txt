cmake_minimum_required(VERSION 3.0)

project(alg-search)
set(CMAKE_CXX_STANDARD 17)


add_executable(alg-search
    src/main.cpp
    include/MatrixGraph.h
    src/MatrixGraph.cpp
    include/Algorithms.h
    src/Algorithms.cpp
    include/Utils.h
    tinyxml2/tinyxml2.h
    tinyxml2/tinyxml2.cpp
    include/ColoredOut.h
    src/ColoredOut.cpp
    include/Heuristics.h
    src/Heuristics.cpp
    include/NodeData.h
)

target_include_directories(alg-search PRIVATE include .)
target_link_libraries(alg-search)