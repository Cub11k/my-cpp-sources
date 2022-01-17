#include "hash_container.h"

using namespace std;

void error_handler(const char *exception)
{
    cout << exception << endl;
}

void test(char *filename)
{
    cout << endl << "------------------------Test------------------------" << endl << endl;
    HashContainer set;
    try {
        set.ProcessFile(filename);
        set.Show();
    } catch (const char *exception) {
        error_handler(exception);
    }
    cout << endl << "----------------------End Test----------------------" << endl << endl;
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        test(argv[1]);
    }
    return 0;
}