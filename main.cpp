#include "MatrixGraph.h"
#include "Algorithms.h"
#include <iostream>
#include "Heuristics.h"
#include <iterator>
#include "Shell.h"


//TODO fix const reference returns

int main()
{    bool quit = false;
    do
    {
        std::cout << "> ";
        try
        {
            auto graph = make_graph("../input.xml");
            std::string command;
            std::getline(std::cin, command);    
            quit = run(command, graph);
        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << '\n';
        }
    } while (!quit);

}
