#pragma once
#include "MatrixGraph.h"
#include "Heuristics.h"

// Because of template nature, I cant implement astar function in Aplication.cpp
// I could just pass the  heuristic function as a function parammeter but
// it would break my disign goals. So what I did is to mix the 2 approachs
// created the _astar function implemented in Application.cpp (taking the heuristic
// function as a function parameter, and created the astar function, implemented
// here, taking he function as a template.

//  _astar function implemented in Application.cpp, takes the heuristic function as
// funcion parameter. The user should not use this function (it's just a helper function) 
std::vector<MatrixNode> basic_algorithm(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph, 
heuristics::heuristic_t heuristic, int k,  bool use_theta);

//A* function, implemented here. Takes the heuristic funtion as template 
template <heuristics::heuristic_t heuristic, int k>
std::vector<MatrixNode> astar(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph)
{
    static_assert(k >= 0 && k <= 5, "No function astar for this value of k.");
    // call the helper (and real) function  
    return basic_algorithm(start, end, graph, heuristic, k, false);
}

// dijskra function (just astar taking no heuristic)
// k as template parameter avoid invalid valueof k 
template<int k>
inline std::vector<MatrixNode> dijkstra(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph)
{
    static_assert(k >= 0 && k <= 5, "No function dijkstra for this value of k.");
    return astar<heuristics::noheuristic, k>(start, end, graph);
}


// Theta* function
// k as template parameter avoid invalid value of k 
template<int k>
inline std::vector<MatrixNode> thetastar(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph)
{
    return basic_algorithm(start, end, graph, heuristics::euclidian, k, true);
}

