#pragma once
#include <vector>
#include <string>

struct MatrixGraph;
struct MatrixNode;

std::pair<MatrixGraph,std::string> make_graph(std::string filepath);

void print(const MatrixGraph& graph, std::vector<MatrixNode> path = {});

struct MatrixNode
{
    MatrixNode() = default;
    MatrixNode(int i, int j)
    {
        this->i = i;
        this->j = j;
    }
    int i = -1;
    int j = -1;
};

bool operator==(const MatrixNode& a, const MatrixNode& b);
bool operator!=(const MatrixNode& a, const MatrixNode& b);

struct MatrixGraph
{
    MatrixGraph(MatrixGraph&& graph);
    MatrixGraph() = default;

    MatrixGraph& operator=(MatrixGraph&& graph);
    std::vector<int>& operator[](int index){return data[index];}
    const std::vector<int>& operator[](int index) const {return data[index];}


    int width()  const {return w;}
    int height() const {return h;}

private:
    std::vector<std::vector<int>> data;
    int w = 0, h = 0;
    friend std::pair<MatrixGraph,std::string> make_graph(std::string filepath);
};

std::ostream& operator<<(std::ostream& stream, const MatrixNode& node);
