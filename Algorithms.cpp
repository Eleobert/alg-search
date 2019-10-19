#include "Algorithms.h"
#include "Utils.h"
#include <queue>
#include <cmath>
#include <iostream> //TODO temporary,only for debugging
#include <stdexcept>

constexpr float infinity = 10000000.0f;

struct NodeData
{
    NodeData() = default;
    NodeData(MatrixNode parent, float cost)
    {
        this->parent = parent;
        this->cost = cost;
    }

    MatrixNode parent;
    float cost = infinity;
    //bool closed = false;
};
/*
bool operator<(const NodeData& a, const NodeData& b)
{
    return a.cost < b.cost;
}*/
auto getNeighbors(const MatrixNode& node, const MatrixGraph& graph)
{
    std::vector<MatrixNode> result;
    auto conditionalPush = [&](int i, int j)
    {
        if(inbox(i, j, graph.height(), graph.width()) && graph[i][j] != 1)
            result.emplace_back(i, j);
    };

    conditionalPush(node.i - 1, node.j);
    conditionalPush(node.i + 1, node.j);
    conditionalPush(node.i, node.j - 1);
    conditionalPush(node.i, node.j + 1);
    return result;
}

namespace heuristic
{
    float manhattan(const MatrixNode& start, const MatrixNode& end)
    {
        return std::abs(start.i - end.i) + std::abs(start.j - end.j);
    }

}

auto recunstructPath(MatrixNode start, MatrixNode end, const std::vector<std::vector<NodeData>>& data)
{
    std::vector<MatrixNode> result;
    do
    {
        result.emplace_back(end);
        end = data[end.i][end.j].parent;
    }while (end != start);
    return result;
}

auto createDataMatrix(int w, int h)
{
    std::vector<std::vector<NodeData>> result;
    result.resize(h);
    for(int i = 0; i < h; i++)
    {
        result[i].resize(w);
    }
    return result;
}

std::vector<MatrixNode> dijkstra(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph)
{

    if(!inbox(start.i, start.j, graph.height(), graph.width()) || graph[start.i][start.j] == 1)
        throw std::runtime_error("Invalid start point");
    if(!inbox(end.i, end.j, graph.height(), graph.width()) || graph[end.i][end.j] == 1)
        throw std::runtime_error("Invalid end point");

    auto data = createDataMatrix(graph.width(), graph.height());
    auto comparator = [&data](const MatrixNode& a, const MatrixNode& b){
        return data[a.i][a.j].cost < data[a.i][a.j].cost;
    };

    std::priority_queue<MatrixNode, std::vector<MatrixNode>, decltype(comparator)> open(comparator);

    open.emplace(start);
    data[start.i][start.j].cost = 0;

    while(!open.empty())
    {
        auto current = open.top();
        open.pop();

        for(auto& neighbor: getNeighbors(current, graph))
        {
            int cost = data[current.i][current.j].cost + heuristic::manhattan(current, neighbor);
            if(cost < data[neighbor.i][neighbor.j].cost)
            {
                data[neighbor.i][neighbor.j].cost = cost;
                data[neighbor.i][neighbor.j].parent = current;
                open.emplace(neighbor);
            }
        }
    }
    if(data[end.i][end.j].cost == infinity) throw std::runtime_error("No path found!");
    return recunstructPath(start, end, data);

}
