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
    *this = std::move(graph);
}

MatrixGraph& MatrixGraph::operator=(MatrixGraph&& graph)
{
    this->w = graph.w;
    this->h = graph.h;
    this->data = std::move(graph.data);
    return *this;
}


std::pair<MatrixGraph,std::string> make_graph(std::string filepath)
{
    std::pair<MatrixGraph,std::string> result;

    using namespace tinyxml2;
    XMLDocument doc;
    if(doc.LoadFile(filepath.c_str()) != XML_SUCCESS)
    {
        throw std::runtime_error("File could not be loaded!");
    }
    
    auto map = doc.RootElement()->FirstChildElement("map");
    if(!map)
    {
        throw std::runtime_error("No node named 'map' inside root node.");
    }
    auto width = map->FindAttribute("width");
    auto height = map->FindAttribute("width");
    if(!width || !height)
    {
        throw std::runtime_error("Invalid attributes width and height");

    }
    result.first.h = width->IntValue();
    result.first.w = height->IntValue();
    std::stringstream stream(map->GetText());

    result.first.data.resize(result.first.h);

    for(int i = 0; i < result.first.h; i++)
    {
        result.first.data[i].resize(result.first.w);
        for(int j = 0; j < result.first.w; j++)
        {
            stream >> result.first[i][j];
        }
    }
    auto ptr = doc.RootElement()->FirstChildElement("comment");
    if(ptr != nullptr)
    {
        result.second = ptr->GetText();
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
