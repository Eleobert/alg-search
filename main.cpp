#include "MatrixGraph.h"
#include "Algorithms.h"
#include <iostream>
#include "Heuristics.h"

int main()
{
    auto graph = makeGraphFromFile("../input");

    try
    {
        auto path = astar<heuristics::euclidian, 3>({2, 0}, {9, 9}, graph);
        print(graph, path);
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }

}
