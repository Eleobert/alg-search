#include "MatrixGraph.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "tinyxml2/tinyxml2.h"
#include <sstream>

namespace symbols
{
    auto hearth = "\xe2\x99\xa5";
    auto face   = "\342\230\272";
    auto brick  = "☐";
}

void print(const MatrixGraph& graph, std::vector<MatrixNode> path)
{
    //std::cout << "  ";
    for(int j = 0 ; j < graph.width() + 2; j++) std::cout << symbols::brick << ' ';
    std::cout << "\n";
    //for(int j = 0 ; j < graph.height(); j++) std::cout << ' ' << '-';
    //std::cout << '\n';


    for(int i = 0; i < graph.width(); i++)
    {
        std::cout << symbols::brick << ' ';
        for(int j = 0 ; j < graph.height(); j++)
        {
            auto it = std::find(path.begin(), path.end(), MatrixNode(i, j));
            if(path[0].i == i && path[0].j == j) std::cout << symbols::hearth;
            else if(path[path.size() - 1].i == i && path[path.size() - 1].j == j) std::cout << symbols::face;
            else if(it != path.end())
            {
                std::cout << "⚬";
            }
            else{
                if (graph[i][j] == 1)
                {
                    std::cout << symbols::brick;
                }
                if (graph[i][j] == 0)
                {
                    std::cout << ' ';
                }
                
            }
            std::cout << ' ';
        }
        std::cout << symbols::brick << '\n';
    }

    for(int j = 0 ; j < graph.width() + 2; j++) std::cout << symbols::brick << ' ';
    std::cout << '\n';
    
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

MatrixGraph make_graph(std::string filepath)
{
    MatrixGraph result;

    using namespace tinyxml2;
    XMLDocument doc;
    doc.LoadFile(filepath.c_str());

    auto map = doc.RootElement()->FirstChildElement("map");
    result.h = map->FindAttribute("width")->IntValue();
    result.w = map->FindAttribute("width")->IntValue();
    std::stringstream stream(map->GetText());
    result.data.resize(result.h);

    for(int i = 0; i < result.h; i++)
    {
        result.data[i].resize(result.w);
        for(int j = 0; j < result.w; j++)
        {
            stream >> result[i][j];
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
