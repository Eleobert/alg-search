#include "MatrixGraph.h"
#include "Algorithms.h"
#include <iostream>

int main()
{
    auto graph = makeGraphFromFile("../input");
    //std::cout << graph.width();
    //std::cout << graph.height();

    try{
        auto path = dijkstra(MatrixNode(4, 0), MatrixNode(6, 8), graph);
        print(graph, path);

        for(auto& node: path)
        {
            std::cout << node.i << ' ' << node.j << '\n';
        }
    }catch(const std::string& message)
    {
        std::cout << message << '\n';
    }

}
