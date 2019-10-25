#pragma once
#include "MatrixGraph.h"
#include <cmath>

namespace heuristics
{
    using heuristic_t = float(*)(const MatrixNode& start, const MatrixNode& end);

    extern float weight;

    inline float manhattan(const MatrixNode& start, const MatrixNode& end)
    {
        return weight * (std::abs(start.i - end.i) + std::abs(start.j - end.j));
    }

    inline float noheuristic(const MatrixNode&, const MatrixNode&)
    {
        return 0;
    }

    inline float euclidian(const MatrixNode& start, const MatrixNode& end)
    {
        return weight * (std::sqrt(std::pow(start.j - end.j, 2) + std::pow(start.i - end.i, 2)));
    }

    inline float diagonal(const MatrixNode& start, const MatrixNode& end)
    {
        int di = std::abs(end.i - start.i);
        int dj = std::abs(end.j - start.j);
        return weight * (std::min(di, dj) * std::sqrt(2.0f) + std::abs(di - dj));
    } 

}
