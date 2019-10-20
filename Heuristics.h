#pragma once
#include "MatrixGraph.h"
#include <cmath>

namespace heuristics
{
    using heuristic_t = float(*)(const MatrixNode& start, const MatrixNode& end);
    inline float manhattan(const MatrixNode& start, const MatrixNode& end)
    {
        return std::abs(start.i - end.i) + std::abs(start.j - end.j);
    }

    inline float noheuristic(const MatrixNode&, const MatrixNode&)
    {
        return 0;
    }

    inline float euclidian(const MatrixNode& start, const MatrixNode& end)
    {
        return std::sqrt(std::pow(start.j - end.j, 2) + std::pow(start.i + end.i, 2));
    }

}