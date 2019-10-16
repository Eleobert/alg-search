#include "MatrixGraph.h"
#include "Algorithms.h"
#include <iostream>

int main()
{
    auto graph = makeGraphFromFile("input");
    //std::cout << graph.width();
    //std::cout << graph.height();
    std::cout << graph << std::endl;

    try{
        auto path = dijkstra(MatrixNode(0, 0), MatrixNode(9, 7), graph);
        for(auto& node: path)
        {
            std::cout << node.i << ' ' << node.j << '\n';
        }
    }catch(const std::string& message)
    {
        std::cout << message << '\n';
    }

}
