#include <iostream>

void blue()
{
    std::cout << "\033[1;34m";
}

void red()
{
    std::cout << "\033[1;31m";
}

void bolded_black()
{
    std::cout << "\033[1;30m";
}
void normal()
{
    std::cout << "\033[0m";
}
