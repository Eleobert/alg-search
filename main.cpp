#include "MatrixGraph.h"
#include "Algorithms.h"
#include <iostream>

int main()
{
    auto graph = makeGraphFromFile("../input");

    try
    {
        auto path = dijkstra(MatrixNode(4, 0), MatrixNode(6, 0), graph);
        print(graph, path);
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }

}
