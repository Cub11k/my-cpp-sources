#include "Vertex.h"

Graph::Graph(const char *filename)
{
    fstream fin;
    fin.open(filename, ios::in);
    if (!fin.is_open()) {
        throw CANNOT_OPEN_FILE;
    }
    num_nodes = 0;
    fin >> num_nodes;
    if (num_nodes == 0) {
        return;
    }
    all_nodes = nullptr;
    all_nodes = new Vertex[num_nodes];
    for (int i = 0; i < num_nodes; ++i) {
        all_nodes[i].num_next = 0;
        all_nodes[i].id_next = new int[num_nodes];
        all_nodes[i].exist = false;
    }
    while (!fin.eof()) {
        int start = num_nodes;
        int end = num_nodes;
        fin >> start >> end;
        if (start >= 0 && start < num_nodes && end >= 0 && end < num_nodes) {
            all_nodes[start].id_next[all_nodes[start].num_next] = end;
            all_nodes[start].num_next++;
            all_nodes[start].exist = true;
            all_nodes[end].id_next[all_nodes[end].num_next] = start;
            all_nodes[end].num_next++;
            all_nodes[end].exist = true;
        }
    }
}

Graph::~Graph()
{
    if (all_nodes) {
        for (int i = 0; i < num_nodes; ++i) {
            if (all_nodes[i].id_next) {
                delete[] all_nodes[i].id_next;
            }
            all_nodes[i].num_next = 0;
            all_nodes[i].exist = false;
        }
        delete[] all_nodes;
    }
    num_nodes = 0;
}

void Graph::WalkThroughComponent(vector<bool> *visited, int id) const
{
    stack<int> stack;
    stack.push(id);
    while (!stack.empty()) {
        int vertex = stack.top();
        stack.pop();

        if (!(*visited)[vertex]) {
            cout << vertex << " ";
            (*visited)[vertex] = true;
        }

        for (int i = 0; i < all_nodes[vertex].num_next; ++i) {
            if (!(*visited)[all_nodes[vertex].id_next[i]]) {
                stack.push(all_nodes[vertex].id_next[i]);
            }
        }
    }
    cout << endl;
}

void Graph::PrintComponents() const
{
    int num_components = 0;
    vector<bool> visited(num_nodes, false);
    for (int i = 0; i < num_nodes; ++i) {
        if (all_nodes[i].exist && !visited[i]) {
            cout << endl << "--------Component " << num_components + 1 << "--------" << endl;
            WalkThroughComponent(&visited, i);
            cout << "------End component " << num_components + 1 << "------" << endl;
            num_components++;
        }
    }
    cout << endl << "Number of components: " << num_components << endl << endl;
}