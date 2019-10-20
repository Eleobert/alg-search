#pragma once

#include <map>
#include <string>
#include <any>
#include <sstream>
#include <vector>
#include <iterator>
#include <vector>
#include <iostream> //------
#include "MatrixGraph.h"
#include "Heuristics.h"
#include "Algorithms.h"

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
        stream.str("");
        stream << commands[2]; //TODO add message for missing 3rd argument
        if(commands[1] == "k")
        {
            stream >> params.k;
        }
        else if(commands[1] == "heuristic")
        {
            stream.str("");
            if(commands[2] == "manhattan") //TODO add message for missing 3rd argument
            {
                params.heuristic = heuristics::manhattan;
            }
            else if(commands[2] == "euclidian") //TODO add message for missing 3rd argument
            {
                params.heuristic = heuristics::euclidian;
            }
            else if(commands[2] == "noheuristic") //TODO add message for missing 3rd argument
            {
                params.heuristic = heuristics::noheuristic;
            }
            else throw std::runtime_error("No heuristic '" + commands[2] + " found!");
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
        }
        else if(commands[1] == "start")
        {
            //TODO check for 4th command
            params.start.i = std::stoi(commands[2]);
            params.start.j = std::stoi(commands[3]);
        }
        else if(commands[1] == "end")
        {
            //TODO check for 4th command
            params.end.i = std::stoi(commands[2]);
            params.end.j = std::stoi(commands[3]);
        }

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
    else throw std::runtime_error("No command '" + commands[0] + " found!");
    return false;
}