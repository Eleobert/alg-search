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


const auto blocked(int i, int j, const MatrixGraph& graph)
{
    return graph[i][j] == 1;
}

const auto blocked(const MatrixNode& node , const MatrixGraph& graph)
{
    return blocked(node.i, node.j, graph);
}
