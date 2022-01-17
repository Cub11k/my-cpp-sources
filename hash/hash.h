#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define index_type int
#define IDX_OUT_OF_RANGE "Index is out of range"
#define NO_SUCH_ELEMENT "No such element"

using namespace std;

template <class T, class V>
class HashTable
{
private:
    struct field
    {
        bool exist;
        T key;
        V value;
    };
    field *set = nullptr;
    int max_element_count = 100;
    int count;

    int HashFunction(const T key) const;

    int GetFirstFreeIndex(const int index) const;

    void Resize(const int size);
public:
    HashTable();
    HashTable(const HashTable &obj);

    ~HashTable();

    HashTable &operator=(const HashTable &obj);
    HashTable &operator+(const HashTable &obj) const;
    HashTable &operator-(const HashTable &obj) const;

    V &operator[](const T key) const;

    void Insert(const T key, const V value);
    bool Search(const T key) const;
    bool Delete(const T key);

    void Clear();
    void Show() const;
};

template class HashTable<int, int>;
template class HashTable<double, double>;
template class HashTable<string, string>;
template class HashTable<vector<int>, vector<int>>;
template class HashTable<vector<double>, vector<double>>;