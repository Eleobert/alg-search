#pragma once

#include "Algorithms.h"
#include "MatrixGraph.h"
#include "Heuristics.h"

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <vector>
#include <iostream>
#include <iomanip>

bool run(std::string cmd, const MatrixGraph& graph)
{
    struct Parameters
    {
        int k = 2;
        heuristics::heuristic_t heuristic = heuristics::noheuristic;
        bool use_theta;
        MatrixNode start, end;
    };
    static Parameters params;

    std::vector<std::string> commands;

    std::stringstream stream(cmd);

    std::copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(),
        std::back_inserter(commands));

    if(commands[0] == "set")
    {
        if(commands.size() < 2) throw std::runtime_error("Missing argument 'variable'");
        if(commands.size() < 3) throw std::runtime_error("Missing argument 'value'");

        if(commands[1] == "k")
        {
            params.k = std::stoi(commands[2]);
        }
        else if(commands[1] == "heuristic")
        {
            stream.str("");
            if(commands[2] == "manhattan")
            {
                params.heuristic = heuristics::manhattan;
            }
            else if(commands[2] == "euclidian")
            {
                params.heuristic = heuristics::euclidian;
            }
            else if(commands[2] == "noheuristic")
            {
                params.heuristic = heuristics::noheuristic;
            }
            else throw std::runtime_error("No heuristic '" + commands[2] + "' found!");
        }
        else if(commands[1] == "use-theta")
        {
            if(commands[2] == "true")
            {
                params.use_theta = true;
            }
            else if(commands[2] == "false")
            {
                params.use_theta = false;
            }
            else throw std::runtime_error("Argument must to be 'true' or 'fasle'!");
        }
        else if(commands[1] == "start")
        {
            if(commands.size() < 4) throw std::runtime_error("Missing argument 'value'");
            params.start.i = std::stoi(commands[2]);
            params.start.j = std::stoi(commands[3]);
        }
        else if(commands[1] == "end")
        {
            if(commands.size() < 4) throw std::runtime_error("Missing argument 'value'");
            params.end.i = std::stoi(commands[2]);
            params.end.j = std::stoi(commands[3]);
        }
        else throw std::runtime_error("No variable '" + commands[2] + "' found!");

    }
    else if(commands[0] == "status")
    {
        using namespace heuristics;
        std::cout << "Heuristic: ";
        if (params.heuristic == noheuristic) std::cout << "noheuristic";
        else if (params.heuristic == manhattan) std::cout << "manhattan";
        else std::cout << "euclidian";
        std::cout << '\n';
        std::cout << "use_theta: " << std::boolalpha << params.use_theta << '\n';
        std::cout << "k        : " << params.k << '\n';
    }
    else if(commands[0] == "go")
    {
       auto path = basic_algorithm(params.start, params.end, graph, params.heuristic, params.k, params.use_theta);
       print(graph, path);
    }
    else if(commands[0] == "quit")
    {
        return true;
    }
    else throw std::runtime_error("No command '" + commands[0] + "' found!");
    return false;
}
