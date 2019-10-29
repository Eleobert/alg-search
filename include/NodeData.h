#pragma once

constexpr float infinity = 10000000.0f;

struct NodeData
{
    NodeData() = default;
    NodeData(MatrixNode parent, float gcost, float hcost)
    {
        this->parent = parent;
        this->gcost = gcost;
        this->fcost = fcost;

    }

    MatrixNode parent;
    float gcost = infinity;
    float fcost = infinity;
    bool closed = false;
};