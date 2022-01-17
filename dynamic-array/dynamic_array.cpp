#include "dynamic_array.h"

template <typename T>
DynamicArray<T>::Block::Block()
{
    block_size_ = 0;
    curr_length_ = 0;
    mass_ = nullptr;
    next_ = nullptr;
    prev_ = nullptr;
}

template <typename T>
DynamicArray<T>::Block::Block(const Block &obj)
{
    block_size_ = obj.block_size_;
    curr_length_ = obj.curr_length_;
    next_ = obj.next_;
    prev_ = obj.prev_;
    if (mass_) {
        delete[] mass_;
    }
    mass_ = new T[block_size_];
    for (int i = 0; i < block_size_; ++i) {
        mass_[i] = obj.mass_[i];
    }
}

template <typename T>
DynamicArray<T>::Block::~Block()
{
    block_size_ = 0;
    curr_length_ = 0;
    if (mass_) {
        delete[] mass_;
    }
    next_ = nullptr;
    prev_ = nullptr;
}

template <typename T>
typename DynamicArray<T>::Block &DynamicArray<T>::Block::operator=(const Block &obj)
{
    if (this == &obj) {
        return *this;
    }

    this->block_size_ = obj.block_size_;
    this->curr_length_ = obj.curr_length_;
    this->next_ = obj.next_;
    this->prev_ = obj.prev_;
    if (this->mass_) {
        delete[] this->mass_;
    }
    this->mass_ = new T[this->block_size_];
    for (int i = 0; i < this->block_size_; i++) {
        this->mass_[i] = obj.mass_[i];
    }
    return *this;
}

template <typename T>
T DynamicArray<T>::Block::operator[](const int i) const
{
    if (i >= curr_length_) {
        throw IDX_OUT_OF_RANGE;
    }
    return mass_[i];
}

template <typename T>
void DynamicArray<T>::Block::set_value(const int i, T value)
{
    if (i >= block_size_) {
        throw IDX_OUT_OF_RANGE;
    }
    if (i >= curr_length_) {
        mass_[curr_length_] = value;
        curr_length_++;
    } else {
        mass_[i] = value;
    }
}

template <typename T>
void DynamicArray<T>::Block::print() const
{
    std::cout << "  {\n    \"length\": " << curr_length_ << ",\n    \"array\": [";
    if (curr_length_ > 0) {
        std::cout << std::setw(4) << mass_[0];
    }
    for (int i = 1; i < curr_length_; ++i) {
        std::cout << "," << std::setw(4) << mass_[i];
    }
    std::cout << "]\n  }";
}

// _____________________________________________________

template <typename T>
DynamicArray<T>::DynamicArray()
{
    head_ = nullptr;
    tail_ = nullptr;
    block_size_ = 0;
    block_num_ = 0;
    length_ = 0;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &obj)
{
    if (this == &obj) {
        return;
    }
    this->clear_array();
    Block *curr = obj.head_;
    while (curr) {
        this->push_back(*curr);
        curr = curr->next_;
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    this->clear_array();
    tail_ = nullptr;
    block_num_ = 0;
    block_size_ = 0;
    length_ = 0;
}

template <typename T>
void DynamicArray<T>::clear_array()
{
    Block *curr = head_;
    Block *next = nullptr;
    while (curr) {
        next = curr->next_;
        delete curr;
        curr = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
    block_num_ = 0;
    block_size_ = 0;
}

template <typename T>
void DynamicArray<T>::set_value(const int i, T value)
{
    Block *curr = head_;
    int idx = i;
    while (curr && idx >= curr->block_size_) {
        idx -= curr->block_size_;
        curr = curr->next_;
    }
    if (!curr) {
        throw IDX_OUT_OF_RANGE;
    }
    if (idx >= curr->curr_length_) {
        curr->mass_[curr->curr_length_] = value;
        curr->curr_length_++;
        length_++;
    }
    curr->mass_[idx] = value;
}

template <typename T>
void DynamicArray<T>::add_block()
{
    tail_->next_ = new Block;
    tail_->next_->block_size_ = block_size_;
    tail_->next_->prev_ = tail_;
    tail_->next_->mass_ = new T[tail_->next_->block_size_];
    for (int i = 0; i < tail_->next_->block_size_; ++i) {
        tail_->next_->mass_[i] = 0;
    }
    tail_ = tail_->next_;
    block_num_++;
}

// [10] [7] <- [5] ==>X [10] [7] [5] ; ==> [10] [10] [2]

template <typename T>
void DynamicArray<T>::push_back(const Block &obj)
{
    if (obj.curr_length_ == 0) {
        return;
    }
    if (head_ == nullptr) {
        head_ = new Block;
        *head_ = obj;
        tail_ = head_;
        block_num_++;
        block_size_ = obj.block_size_;
    } else {
        Block tmp = obj;
        if (tail_->curr_length_ + tmp.curr_length_ > tail_->block_size_) {
            while (tmp.curr_length_) {
                int cnt = 0;
                for (int i = 0; i < tmp.curr_length_; ++i) {
                    if (i + tail_->curr_length_ < tail_->block_size_) {
                        tail_->mass_[tail_->curr_length_ + i] = tmp.mass_[i];
                        cnt++;
                    }
                }
                tail_->curr_length_ += cnt;
                if (cnt) {
                    for (int i = cnt; i < tmp.curr_length_; ++i) {
                        tmp.mass_[i - cnt] = tmp.mass_[i];
                        tmp.mass_[i] = 0;
                    }
                }
                tmp.curr_length_ -= cnt;
                if (tmp.curr_length_) {
                    add_block();
                }
            }
        } else {
            for (int i = 0; i < obj.curr_length_; ++i) {
                tail_->mass_[tail_->curr_length_ + i] = obj.mass_[i];
            }
        }
    }
    length_ += obj.curr_length_;
}

// [3] <- [8] ==> [10] [1]

template <typename T>
void DynamicArray<T>::push_back(const T *arr, const int arr_size)
{
    if (arr_size == 0) {
        return;
    }
    Block tmp;
    tmp.mass_ = new T[arr_size];
    tmp.block_size_ = arr_size;
    tmp.curr_length_ = arr_size;
    for (int i = 0; i < arr_size; ++i) {
        tmp.mass_[i] = arr[i];
    }
    push_back(tmp);
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray &obj)
{
    if (this == &obj) {
        return *this;
    }
    this->clear_array();
    this->block_size_ = obj.block_size_;
    Block *obj_curr = obj.head_;
    while (obj_curr) {
        this->push_back(*obj_curr);
        obj_curr = obj_curr->next_;
    }
    return *this;
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator+(const DynamicArray &obj) const
{
    static DynamicArray tmp(*this);
    Block *obj_curr = obj.head_;
    while (obj_curr) {
        tmp.push_back(*obj_curr);
        obj_curr = obj_curr->next_;
    }
    return tmp;
}

template <typename T>
T &DynamicArray<T>::operator[](const int i) const
{
    Block *curr = head_;
    int idx = i;
    while (curr && idx >= curr->block_size_) {
        idx -= curr->block_size_;
        curr = curr->next_;
    }
    if (!curr || idx >= curr->curr_length_) {
        throw IDX_OUT_OF_RANGE;
    }
    return curr->mass_[idx];
}

template <typename T>
int DynamicArray<T>::get_length() const
{
    return length_;
}

template <typename T>
void DynamicArray<T>::print() const
{
    std::cout << "--------------------Dynamic array as list of blocks--------------------" << std::endl;
    if (length_ > 0) {
        std::cout << "[" << this->operator[](0);
    }
    for (int i = 1; i < length_; ++i) {
        std::cout << ", " << this->operator[](i);
    }
    std::cout << "]" << std::endl
        << "-----------------------------------------------------------------------" << std::endl;
}

template <typename T>
void DynamicArray<T>::debug_print() const
{
    std::cout << "--------------------Dynamic array as list of blocks--------------------" << std::endl
        << "{" << std::endl;
    Block *curr = head_;
    if (curr) {
        curr->print();
        curr = curr->next_;
    }
    while (curr) {
        std::cout << "," << std::endl;
        curr->print();
        curr = curr->next_;
    }
    std::cout << std::endl
        << "}" << std::endl
        << "-----------------------------------------------------------------------" << std::endl;
}

template <typename T>
void DynamicArray<T>::sort()
{
    for (int i = 0; i < length_; ++i) {
        for (int j = i + 1; j < length_; ++j) {
            if (this->operator[](i) > this->operator[](j)) {
                T tmp = this->operator[](i);
                set_value(i, this->operator[](j));
                set_value(j, tmp);
            }
        }
    }
}