#include <iostream>
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
            std::string command;
            std::getline(std::cin, command);
            quit = run(command);
        }
        catch(const std::exception& ex)
        {
            red();
            std::cout << ex.what() << '\n';
            normal();
        }
    } while (!quit);

}
