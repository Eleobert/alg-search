#include "MatrixGraph.h"
#include <iostream>
#include <fstream>


std::ostream& operator<<(std::ostream& stream, const MatrixGraph& graph)
{
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
            std::cout << graph[i][j] << ' ';
        }
        std::cout << '\n';
    }
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
