#include "MatrixGraph.h"
#include <iostream>
#include <fstream>
#include <algorithm>

enum class Tiles: char {hearth = '\3'};

void print(const MatrixGraph& graph, std::vector<MatrixNode> path)
{
    std::cout << path[0].i << ' ' << path[0].j << '\n';

    std::cout << "  ";
    for(int j = 0 ; j < graph.height(); j++) std::cout << ' ' << j;
    std::cout << "\n  ";
    for(int j = 0 ; j < graph.height(); j++) std::cout << ' ' << '-';
    std::cout << '\n';


    for(int i = 0; i < graph.width(); i++)
    {
        std::cout << i << "| ";
        for(int j = 0 ; j < graph.height(); j++)
        {
            auto it = std::find(path.begin(), path.end(), MatrixNode(i, j));
            if(path[0].i == i && path[0].j == j) std::cout << "\xe2\x99\xa5";
            else if(path[path.size() - 1].i == i && path[path.size() - 1].j == j) std::cout << "\342\230\272";
            else if(it != path.end())
            {
                std::cout << "*";
            }
            else{
                std::cout << graph[i][j];
            }
            std::cout << ' ';
        }
        std::cout << '\n';
    }
}

std::ostream& operator<<(std::ostream& stream, const MatrixNode& node)
{
    stream << '(' << node.i << ", " << node.j << ')';
    return stream;
}

MatrixGraph::MatrixGraph(MatrixGraph&& graph)
{
    this->w = graph.w;
    this->h = graph.h;
    this->data = std::move(graph.data);
}

MatrixGraph makeGraphFromFile(std::string filepath)
{
    MatrixGraph result;

    std::ifstream file;
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    file.open(filepath);
    file >> result.w; file >> result.h;
    result.data.resize(result.h);

    for(int i = 0; i < result.h; i++)
    {
        result.data[i].resize(result.w);
        for(int j = 0; j < result.w; j++)
        {
            file >> result[i][j];
        }
    }
    return result;
}

bool operator==(const MatrixNode& a, const MatrixNode& b)
{
    return a.i == b.i && a.j == b.j;
}

bool operator!=(const MatrixNode& a, const MatrixNode& b)
{
    return !(a == b);
}
