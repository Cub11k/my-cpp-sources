#include <iostream>
#include <iomanip>
#include <algorithm>

#define IDX_OUT_OF_RANGE 1

template <typename T>
class DynamicArray
{
private:
    class Block
    {
    public:
        int block_size_ = 0;
        int curr_length_ = 0;
        T *mass_ = nullptr;
        Block *next_ = nullptr;
        Block *prev_ = nullptr;

        Block();
        Block(const Block &obj);
        ~Block();
        void set_value(const int i, T value);
        Block &operator=(const Block &obj);
        T operator[](const int i) const;
        void print() const;
    };

    int block_size_ = 0;
    int block_num_ = 0;
    int length_ = 0;
    Block *head_ = nullptr;
    Block *tail_ = nullptr;

    void push_back(const Block &obj);
    void set_value(const int i, T value);
    void debug_print() const;
    void add_block();

public:
    DynamicArray();
    DynamicArray(const DynamicArray &obj);
    ~DynamicArray();
    DynamicArray &operator=(const DynamicArray &obj);
    DynamicArray &operator+(const DynamicArray &obj) const;
    T &operator[](const int i) const;
    int get_length() const;
    void push_back(const T *arr, const int size);
    void print() const;
    void clear_array();
    void sort();
};

// template class DynamicArray<bool>;
// template class DynamicArray<char>;
// template class DynamicArray<unsigned char>;
// template class DynamicArray<short>;
// template class DynamicArray<unsigned short>;
template class DynamicArray<int>;
// template class DynamicArray<unsigned int>;
// template class DynamicArray<long>;
// template class DynamicArray<unsigned long>;
// template class DynamicArray<long long>;
// template class DynamicArray<unsigned long long>;
// template class DynamicArray<float>;
template class DynamicArray<double>;
// template class DynamicArray<long double>;