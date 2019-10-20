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
std::vector<MatrixNode> _astar(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph, 
float h(const MatrixNode&, const MatrixNode&), bool use_theta);

//A* function, implemented here. Takes the heuristic funtion as template 
template <float h(const MatrixNode&, const MatrixNode&)>
std::vector<MatrixNode> astar(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph)
{
    // call the helper (and real) function
    return _astar(start, end, graph, h, false);
}

//dijskra function (just astar taking no heuristic)
inline std::vector<MatrixNode> dijkstra(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph)
{
    return astar<heuristics::noheuristic>(start, end, graph);
}


//Theta* function
inline std::vector<MatrixNode> thetastar(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph)
{
    return _astar(start, end, graph, heuristics::euclidian, true);
}