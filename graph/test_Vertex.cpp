#include "Vertex.h"

void ExceptionHandler(const char *exception)
{
    cout << exception << endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        return 0;
    }
    try {
        Graph g(argv[1]);
        g.PrintComponents();
    } catch (const char *exception) {
        ExceptionHandler(exception);
        return 1;
    }
}