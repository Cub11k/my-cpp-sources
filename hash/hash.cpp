#include "hash.h"

template<class T, class V>
int HashTable<T, V>::HashFunction(const T key) const
{
    int x = hash<T>{}(key);
    return abs(x) % max_element_count;
}

template <>
int HashTable<vector<int>, vector<int>>::HashFunction(const vector<int> key) const
{
    int x = 0;
    for (auto i : key) {
        x += i;
    }
    return abs(x) % max_element_count;
}

template <>
int HashTable<vector<double>, vector<double>>::HashFunction(
    const vector<double> key) const
{
    int x = 0;
    for (auto i : key) {
        x += ((int) i) ^ 0x4B3F0735;
    }
    return abs(x) % max_element_count;
}

template<class T, class V>
int HashTable<T, V>::GetFirstFreeIndex(const int index) const
{
    for (int i = index; i < max_element_count; ++i) {
        if (!set[i].exist) {
            return i;
        }
    }
    return max_element_count;
}

template<class T, class V>
void HashTable<T, V>::Resize(const int size)
{
    if (size == max_element_count) {
        return;
    }
    field *tmp = new field[size];
    for (int i = 0; i < max_element_count; ++i) {
        tmp[i].exist = set[i].exist;
        tmp[i].key = set[i].key;
        tmp[i].value = set[i].value;
    }
    for (int i = max_element_count; i < size; ++i) {
        tmp[i].exist = false;
    }
    max_element_count = size;
    delete[] set;
    set = tmp;
}

template <class T, class V>
HashTable<T, V>::HashTable()
{
    count = 0;
    set = new field[max_element_count];
    for (int i = 0; i < max_element_count; ++i) {
        set[i].exist = false;
    }
}

template <class T, class V>
HashTable<T, V>::HashTable(const HashTable<T, V> &obj)
{
    this->count = obj.count;
    this->max_element_count = obj.max_element_count;
    if (!this->set || this->max_element_count != obj.max_element_count) {
        delete[] this->set;
        this->set = new field[obj.max_element_count];
    }
    for (int i = 0; i < obj.max_element_count; ++i) {
        this->set[i].exist = obj.set[i].exist;
        this->set[i].key = obj.set[i].key;
        this->set[i].value = obj.set[i].value;
    }
    for (int i = obj.max_element_count; i < this->max_element_count; ++i) {
        this->set[i].exist = false;
    }
}

template <class T, class V>
HashTable<T, V>::~HashTable()
{
    max_element_count = 0;
    count = 0;
    delete[] set;
}

template <class T, class V>
HashTable<T, V> &HashTable<T, V>::operator=(const HashTable<T, V> &obj)
{
    if (!this->set || this->max_element_count != obj.max_element_count) {
        delete[] this->set;
        this->set = new field[obj.max_element_count];
    }
    for (int i = 0; i < obj.max_element_count; ++i) {
        this->set[i].exist = obj.set[i].exist;
        this->set[i].key = obj.set[i].key;
        this->set[i].value = obj.set[i].value;
    }
    for (int i = obj.max_element_count; i < this->max_element_count; ++i) {
        this->set[i].exist = false;
    }
    this->count = obj.count;
    this->max_element_count = obj.max_element_count;
    return *this;
}

template <class T, class V>
HashTable<T, V> &HashTable<T, V>::operator+(const HashTable<T, V> &obj) const
{
    static HashTable<T, V> tmp(*this);
    for (int i = 0; i < obj.max_element_count; ++i) {
        if (obj.set[i].exist) {
            tmp.Insert(obj.set[i].key, obj.set[i].value);
            tmp.count++;
        }
    }
    return tmp;
}

template <class T, class V>
HashTable<T, V> &HashTable<T, V>::operator-(const HashTable<T, V> &obj) const
{
    static HashTable<T, V> tmp(*this);
    for (int i = 0; i < obj.max_element_count; ++i) {
        if (obj.set[i].exist) {
            tmp.Delete(obj.set[i].key);
            tmp.count--;
        }
    }
    return tmp;
}

template <class T, class V>
V &HashTable<T, V>::operator[](const T key) const
{
    int idx = HashFunction(key);
    if (idx < max_element_count) {
        if (set[idx].exist) {
            return set[idx].value;
        }
        throw NO_SUCH_ELEMENT;
    }
    throw IDX_OUT_OF_RANGE;
}

template<class T, class V>
void HashTable<T, V>::Insert(const T key, const V value)
{
    int idx = HashFunction(key);
    if (!set[idx].exist) {
        set[idx].exist = true;
        set[idx].key = key;
        set[idx].value = value;
    } else if (key == set[idx].key) {
        set[idx].value = value;
    } else {
        int free_idx = GetFirstFreeIndex(idx);
        if (free_idx >= max_element_count) {
            Resize(2 * max_element_count);
        }
        set[free_idx].exist = true;
        set[free_idx].key = key;
        set[free_idx].value = value;
    }
    count++;
}

template<class T, class V>
bool HashTable<T, V>::Search(const T key) const
{
    int idx = HashFunction(key);
    if (set[idx].key != key) {
        for (int i = idx + 1; i < max_element_count; ++i) {
            if (set[i].exist && set[i].key == key) {
                return true;
            }
        }
        return false;
    }
    return set[idx].exist;
}

template<class T, class V>
bool HashTable<T, V>::Delete(const T key)
{
    int idx = HashFunction(key);
    if (set[idx].exist) {
        set[idx].exist = false;
        count--;
        return true;
    }
    return false;
}

template<class T, class V>
void HashTable<T, V>::Clear()
{
    for (int i = 0; i < max_element_count; ++i) {
        Delete(set[i].key);
    }
}

template<class T, class V>
void HashTable<T, V>::Show() const
{
    cout << endl << "    -----------------Hash table-----------------" << endl << endl;
    for (int i = 0; i < max_element_count; ++i) {
        if (set[i].exist) {
            cout << "        Key = " << set[i].key << " Value = " << set[i].value
                << " Hash(Key) = " << i << endl;
        }
    }
    cout << endl << "    --------------------------------------------" << endl << endl;
}

template<>
void HashTable<vector<int>, vector<int>>::Show() const
{
    cout << endl << "    -----------------Hash table-----------------" << endl << endl;
    for (int i = 0; i < max_element_count; ++i) {
        if (set[i].exist) {
            cout << "        Key = ";
            for (auto j : set[i].key) {
                cout << j << " ";
            }
            cout << "Value = ";
            for (auto j : set[i].value) {
                cout << j << " ";
            }
            cout << "Hash(Key) = " << i << endl;
        }
    }
    cout << endl << "    --------------------------------------------" << endl << endl;
}

template<>
void HashTable<vector<double>, vector<double>>::Show() const
{
    cout << endl << "    -----------------Hash table-----------------" << endl << endl;
    for (int i = 0; i < max_element_count; ++i) {
        if (set[i].exist) {
            cout << "        Key = ";
            for (auto j : set[i].key) {
                cout << j << " ";
            }
            cout << "Value = ";
            for (auto j : set[i].value) {
                cout << j << " ";
            }
            cout << "Hash(Key) = " << i << endl;
        }
    }
    cout << endl << "    --------------------------------------------" << endl << endl;
}