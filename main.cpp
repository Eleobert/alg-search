#include "MatrixGraph.h"
#include "Algorithms.h"
#include <iostream>
#include "Heuristics.h"
#include <iterator>
#include "Shell.h"
#include "ColoredOut.h"



int main()
{    bool quit = false;
    do
    {
        blue();
        std::cout << "> ";
        normal();
        try
        {
            auto graph = make_graph("../input.xml");
            std::string command;
            std::getline(std::cin, command);
            quit = run(command, graph);
        }
        catch(const std::exception& ex)
        {
            red();
            std::cout << ex.what() << '\n';
            normal();
        }
    } while (!quit);

}
