#pragma once
#include "MatrixGraph.h"

inline bool between(int a, int value, int b){return (a < value) && (value < b);}

bool inbox(int i, int j, int boxH, int boxW)
{
    if(between(-1, i, boxH) && between(-1, j, boxW))
    {
        return true;
    }
    return false;
}

/*
void throwIfInvalidNode(const MatrixNode& node, const MatrixGraph& graph, const std::string& message)
{
    if(!between(-1, node.i, graph.height) || !between(-1, node.j, graph.width))
    {
        throw message;
    }
}
*/
