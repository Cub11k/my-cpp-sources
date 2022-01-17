#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#define CANNOT_OPEN_FILE "Cannot open file"

using namespace std;

struct Vertex
{
    int num_next;  // number of neighbours
    int *id_next;  // array of indices of neighbour vertices in graph array all_nodes

    bool exist;
};


class Graph
{
private:
    int num_nodes;    // number of vertices
    Vertex *all_nodes;  // array of all vertices

    void WalkThroughComponent(vector<bool> *visited, int id) const;
public:
    Graph(const char *filename);
    ~Graph();

    void PrintComponents() const;
};
