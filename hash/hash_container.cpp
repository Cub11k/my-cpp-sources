#include "hash_container.h"

template <>
HashTable<int, int>
*HashContainer::choose_table() const
{
    return tableInt;
}

template <>
HashTable<double, double>
*HashContainer::choose_table() const
{
    return tableDouble;
}

template <>
HashTable<string, string>
*HashContainer::choose_table() const
{
    return tableString;
}

template <>
HashTable<vector<int>, vector<int>>
*HashContainer::choose_table() const
{
    return tableIntArray;
}

template <>
HashTable<vector<double>, vector<double>>
*HashContainer::choose_table() const
{
    return tableDoubleArray;
}

HashContainer::HashContainer()
{
    tableInt = new HashTable<int, int>();
    tableDouble = new HashTable<double, double>();
    tableString = new HashTable<string, string>();
    tableIntArray = new HashTable<vector<int>, vector<int>>();
    tableDoubleArray = new HashTable<vector<double>, vector<double>>();
}

HashContainer::HashContainer(const HashContainer &obj)
{
    *(this->tableInt) = *(obj.tableInt);
    *(this->tableDouble) = *(obj.tableDouble);
    *(this->tableString) = *(obj.tableString);
    *(this->tableIntArray) = *(obj.tableIntArray);
    *(this->tableDoubleArray) = *(obj.tableDoubleArray);
}

HashContainer::~HashContainer()
{
    delete tableInt;
    delete tableDouble;
    delete tableString;
    delete tableIntArray;
    delete tableDoubleArray;
}

HashContainer &HashContainer::operator=(const HashContainer &obj)
{
    *(this->tableInt) = *(obj.tableInt);
    *(this->tableDouble) = *(obj.tableDouble);
    *(this->tableString) = *(obj.tableString);
    *(this->tableIntArray) = *(obj.tableIntArray);
    *(this->tableDoubleArray) = *(obj.tableDoubleArray);
    return *this;
}

HashContainer &HashContainer::operator+(const HashContainer &obj) const
{
    static HashContainer tmp(*this);
    *(tmp.tableInt) = *(tmp.tableInt) + *(obj.tableInt);
    *(tmp.tableDouble) = *(tmp.tableDouble) + *(obj.tableDouble);
    *(tmp.tableString) = *(tmp.tableString) + *(obj.tableString);
    *(tmp.tableIntArray) = *(tmp.tableIntArray) + *(obj.tableIntArray);
    *(tmp.tableDoubleArray) = *(tmp.tableDoubleArray) + *(obj.tableDoubleArray);
    return tmp;
}

HashContainer &HashContainer::operator-(const HashContainer &obj) const
{
    static HashContainer tmp(*this);
    *(tmp.tableInt) = *(tmp.tableInt) - *(obj.tableInt);
    *(tmp.tableDouble) = *(tmp.tableDouble) - *(obj.tableDouble);
    *(tmp.tableString) = *(tmp.tableString) - *(obj.tableString);
    *(tmp.tableIntArray) = *(tmp.tableIntArray) - *(obj.tableIntArray);
    *(tmp.tableDoubleArray) = *(tmp.tableDoubleArray) - *(obj.tableDoubleArray);
    return tmp;
}

template <class T, class V>
V HashContainer::get_value(const T key) const
{
    return choose_table<T, V>()[key];
}

template <class T, class V>
void HashContainer::Insert(const T key, const V value)
{
    choose_table<T, V>()->Insert(key, value);
}

template <class T>
bool HashContainer::Search(const T key) const
{
    return choose_table<T, T>()->Search(key);
}

template <class T>
bool HashContainer::Delete(const T key)
{
    return choose_table<T, T>()->Delete(key);
}

void HashContainer::ProcessFile(char *filename)
{
    fstream fin;
    fin.open(filename, ios::in);
    if (fin.is_open()) {
        while (!fin.eof()) {
            string type;
            fin >> type;
            if (type == "=i") {
                int key = 0;
                int value = 0;
                fin >> key >> value;
                choose_table<int, int>()->Insert(key, value);
            } else if (type == "=d") {
                double key = 0;
                double value = 0;
                fin >> key >> value;
                choose_table<double, double>()->Insert(key, value);
            } else if (type == "=s") {
                string key = "";
                string value = "";
                fin >> key >> value;
                choose_table<string, string>()->Insert(key, value);
            } else if (type == "=ia") {
                int key_len = 0;
                int value_len = 0;
                vector<int> key = {};
                vector<int> value = {};
                fin >> key_len;
                int x = 0;
                for (int i = 0; i < key_len; ++i) {
                    fin >> x;
                    key.push_back(x);
                }
                fin >> value_len;
                for (int i = 0; i < value_len; ++i) {
                    fin >> x;
                    value.push_back(x);
                }
                choose_table<vector<int>, vector<int>>()->Insert(key, value);
            } else if (type == "=da") {
                int key_len = 0;
                int value_len = 0;
                vector<double> key = {};
                vector<double> value = {};
                fin >> key_len;
                double x = 0;
                for (int i = 0; i < key_len; ++i) {
                    fin >> x;
                    key.push_back(x);
                }
                fin >> value_len;
                for (int i = 0; i < value_len; ++i) {
                    fin >> x;
                    value.push_back(x);
                }
                choose_table<vector<double>, vector<double>>()->Insert(key, value);
            }
        }
    }
    fin.close();
}

void HashContainer::Clear()
{
    tableInt->Clear();
    tableDouble->Clear();
    tableString->Clear();
    tableIntArray->Clear();
    tableDoubleArray->Clear();
}

void HashContainer::Show() const
{
    cout << "tableInt" << endl;
    tableInt->Show();
    cout << "tableDouble" << endl;
    tableDouble->Show();
    cout << "tableString" << endl;
    tableString->Show();
    cout << "tableIntArray" << endl;
    tableIntArray->Show();
    cout << "tableDoubleArray" << endl;
    tableDoubleArray->Show();
}