#pragma once

#include "NodeData.h"
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

auto& fcost(const MatrixNode& node, std::vector<std::vector<NodeData>>& data)
{
    return data[node.i][node.j].fcost;
}

const auto& fcost(const MatrixNode& node, const std::vector<std::vector<NodeData>>& data)
{
    return data[node.i][node.j].fcost;
}

auto& gcost(const MatrixNode& node, std::vector<std::vector<NodeData>>& data)
{
    return data[node.i][node.j].gcost;
}

const auto& gcost(const MatrixNode& node, const std::vector<std::vector<NodeData>>& data)
{
    return data[node.i][node.j].gcost;
}

auto& parent(const MatrixNode& node, std::vector<std::vector<NodeData>>& data)
{
    return data[node.i][node.j].parent;
}

const auto& parent(const MatrixNode& node, const std::vector<std::vector<NodeData>>& data)
{
    return data[node.i][node.j].parent;
}

void close(const MatrixNode& node, std::vector<std::vector<NodeData>>& data)
{
    data[node.i][node.j].closed  = true;
}

[[nodiscard]] auto closed(const MatrixNode& node, std::vector<std::vector<NodeData>>& data)
{
    return data[node.i][node.j].closed;
}



