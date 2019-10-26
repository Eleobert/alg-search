#include "Algorithms.h"
#include "Utils.h"
#include <queue>
#include <cmath>
#include <iostream> //TODO temporary,only for debugging
#include <stdexcept>
#include "Heuristics.h"
#include <set>
#include <algorithm>

//TODO fix case

constexpr float infinity = 10000000.0f;

struct NodeData
{
    NodeData() = default;
    NodeData(MatrixNode parent, float gcost, float hcost)
    {
        this->parent = parent;
        this->gcost = gcost;
        this->fcost = fcost;

    }

    MatrixNode parent;
    float gcost = infinity;
    float fcost = infinity;

};

/* cost() and parent() should be on Utils.h, but so, I couldn't hide NodeData struct from the user */
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

// I didn't found a pattern, so just brute force it!
auto get_neighbors(int k, const MatrixNode& node, const MatrixGraph& graph)
{
    std::vector<MatrixNode> result;
    auto conditionalPush = [&](int i, int j)
    {
        if(inbox(i, j, graph.height(), graph.width()) && !blocked(i, j, graph))
            result.emplace_back(i, j);
    };

    conditionalPush(node.i - 1, node.j);
    conditionalPush(node.i + 1, node.j);
    conditionalPush(node.i, node.j - 1);
    conditionalPush(node.i, node.j + 1);
    
    if(k >= 3)
    {
        conditionalPush(node.i - 1, node.j - 1);
        conditionalPush(node.i - 1, node.j + 1);
        conditionalPush(node.i + 1, node.j - 1);
        conditionalPush(node.i + 1, node.j + 1);
        
        if(k >= 4)
        {
            conditionalPush(node.i - 1, node.j - 2);
            conditionalPush(node.i - 1, node.j + 2);
            conditionalPush(node.i - 2, node.j - 1);
            conditionalPush(node.i - 2, node.j + 1);
            conditionalPush(node.i + 1, node.j - 2);
            conditionalPush(node.i + 1, node.j + 2);
            conditionalPush(node.i + 2, node.j - 1);
            conditionalPush(node.i + 2, node.j + 1);
            
            if(k == 5)
            {
                conditionalPush(node.i - 1, node.j - 3);
                conditionalPush(node.i - 1, node.j + 3);
                conditionalPush(node.i - 2, node.j - 3);
                conditionalPush(node.i - 2, node.j + 3);
                conditionalPush(node.i - 3, node.j - 2);
                conditionalPush(node.i - 3, node.j + 2);
                conditionalPush(node.i - 3, node.j - 1);
                conditionalPush(node.i - 3, node.j + 1);
                conditionalPush(node.i + 1, node.j - 3);
                conditionalPush(node.i + 1, node.j + 3);
                conditionalPush(node.i + 2, node.j - 3);
                conditionalPush(node.i + 2, node.j + 3);
                conditionalPush(node.i + 3, node.j - 2);
                conditionalPush(node.i + 3, node.j + 2);
                conditionalPush(node.i + 3, node.j - 1);
                conditionalPush(node.i + 3, node.j + 1);
            }
        }
    }
    

    return result;
}

auto recunstruct_path(const MatrixNode& start, MatrixNode end, const std::vector<std::vector<NodeData>>& data)
{
    std::vector<MatrixNode> result;
    while (end != start)
    {
        result.emplace_back(end);
        end = parent(end, data);
    }
    result.emplace_back(end); //push the start point
    return result;
}


auto create_data_matrix(int w, int h)
{
    std::vector<std::vector<NodeData>> result;
    result.resize(h);
    for(int i = 0; i < h; i++)
    {
        result[i].resize(w);
    }
    return result;
}

//TODO fix that small bug
//this is my own implementation of line_of_sight
bool line_of_sight(const MatrixNode& a, const MatrixNode& b, const MatrixGraph& graph)
{
    //create a linear function that maps j -> i
    auto linearx = [&](int x)
    {
        return static_cast<float>(b.i - a.i)/(b.j - a.j) * x + static_cast<float>(b.j * a.i - a.j * b.i)/(b.j - a.j);
    };

    for(int j = a.j; j != b.j; (a.j < b.j)? j++: j--)
    {
        if(blocked(linearx(j), j, graph)) return false;
    }

    //do the same thing for i
    //create a linear function that maps i -> j
    //But actually we don't need to. If we swap the values of i and j, of the nodes, we can use the same function above.
    auto lineary = [&](int y)
    {
        return static_cast<float>(b.j - a.j)/(b.i - a.i) * y + static_cast<float>(b.i * a.j - a.i * b.j)/(b.i - a.i);
    };

    for(int i = a.i; i != b.i; (a.i < b.i)? i++: i--)
    {
        if(blocked(i, lineary(i), graph)) return false;
    }

    return true;
}


void theta_update_vertex(MatrixNode& current, MatrixNode& neighbor, const MatrixGraph& graph, std::vector<std::vector<NodeData>>& data,
    heuristics::heuristic_t heuristic)
{
    if(line_of_sight(parent(current, data), neighbor, graph))
    {
        gcost(neighbor, data) = gcost(parent(current, data), data) + heuristic(parent(current, data), neighbor);
        parent(neighbor, data) = parent(current, data);
    }
    else
    {
        gcost(neighbor, data) = gcost(current, data) + heuristic(current, neighbor);
        parent(neighbor, data) = current;
    }
    
}


/*
 * This function seems to have a huge amount of arguments but it doesn't.
 * start - is the start point
 * end   - is the end point
 * graph - the graph we working with
 * heuristic - is the heuristic function
 * use_theta - true if we want to use theta* algotithm
 * Это все очень просто!
*/
std::vector<MatrixNode> basic_algorithm(const MatrixNode& start, const MatrixNode& end, const MatrixGraph& graph, heuristics::heuristic_t heuristic,
    int k, bool use_theta) 
{

    if(!inbox(start.i, start.j, graph.height(), graph.width()) || blocked(start, graph))
        throw std::runtime_error("Invalid start point");
    if(!inbox(end.i, end.j, graph.height(), graph.width()) || blocked(end, graph))
        throw std::runtime_error("Invalid end point");

    auto data = create_data_matrix(graph.width(), graph.height());
    auto comparator = [&data](const MatrixNode& a, const MatrixNode& b){
        return fcost(a, data) < fcost(b, data);
    };

    std::multiset<MatrixNode, decltype(comparator)> open(comparator);

    open.emplace(start);
    parent(start, data) = start; //to avoid bugs when looking for parent of start (bug found on theta_update_vertex)
    gcost(start, data) = 0;
    fcost(start, data) = heuristic(start, end);

    while(!open.empty())
    {
        auto current = *open.begin();
        open.erase(open.begin());

        for(auto& neighbor: get_neighbors(k, current, graph))
        {
            auto newcost = gcost(current, data) + heuristic(current, neighbor);
            if(newcost < gcost(neighbor, data) && line_of_sight(current, neighbor, graph))
            {
                if(use_theta)
                {
                    theta_update_vertex(current, neighbor, graph, data, heuristic);
                }
                else
                {
                    gcost(neighbor, data) = newcost;
                    fcost(neighbor, data) = newcost + heuristic(neighbor, end);
                    parent(neighbor, data) = current;
                }
                if(auto e = std::find(open.begin(), open.end(), neighbor); e != open.end())
                {
                    open.erase(e); //remove to update it's position (below)
                }
                open.emplace(neighbor);
            }
        }
    }
    if(gcost(end, data) == infinity) throw std::runtime_error("No path found!");
    return recunstruct_path(start, end, data);
}