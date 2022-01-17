#include "hash.h"

class HashContainer
{
private:
    HashTable<int, int> *tableInt;
    HashTable<double, double> *tableDouble;
    HashTable<string, string> *tableString;
    HashTable<vector<int>, vector<int>> *tableIntArray;
    HashTable<vector<double>, vector<double>> *tableDoubleArray;

    template <class T, class V>
    HashTable<T, V> *choose_table() const;
public:

    HashContainer();
    HashContainer(const HashContainer &obj);
    ~HashContainer();

    HashContainer &operator=(const HashContainer &obj);
    HashContainer &operator+(const HashContainer &obj) const;
    HashContainer &operator-(const HashContainer &obj) const;

    template<class T, class V>
    V get_value(const T key) const;

    template <class T, class V>
    void Insert(const T key, const V value);
    template <class T>
    bool Search(const T key) const;
    template <class T>
    bool Delete(const T key);

    void ProcessFile(char *filename);

    void Clear();
    void Show() const;
};