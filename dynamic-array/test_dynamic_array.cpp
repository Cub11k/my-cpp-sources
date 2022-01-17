#include "dynamic_array.h"

void error_handler(int exception)
{
    switch (exception) {
    case IDX_OUT_OF_RANGE:
        std::cout << "Index out of range" << std::endl;
        break;
    }
}

template <typename T>
int test(T *arr, int size, T test_assignment)
{
    try {
        std::cout << std::endl;
        DynamicArray<T> arr;
        DynamicArray<T> mass2;
        mass2.push_back(arr, size / 4);
        arr = mass2;
        arr = arr + mass2;
        arr.push_back(arr + size / 4, size / 4);
        arr.push_back(arr + size / 4 + size / 4, size / 4);
        arr.print();
        arr.sort();
        std::cout << std::endl
            << "Sorted:" << std::endl;
        arr.print();

        int idx = rand() % arr.get_length();
        std::cout << "Test operator[] : arr[" << idx << "] = " << arr[idx] << std::endl;
        arr[idx] = test_assignment;
        std::cout << "Test operator[] after assignment : arr[" << idx << "] = " << arr[idx] << std::endl;
        std::cout << "Test get_length() : length = " << arr.get_length() << std::endl;
        std::cout << "-----------------------------------------------------------------------" << std::endl
            << std::endl;
    } catch (int exception) {
        error_handler(exception);
        return 1;
    }
    return 0;
}

int main()
{
    srand(time(NULL));

    int arr1[20];
    for (int i = 0; i < 20; ++i) {
        arr1[i] = rand() % 10000;
    }

    double arr2[20];
    for (int i = 0; i < 20; ++i) {
        arr2[i] = 10723.2346754 * ((double) rand() / RAND_MAX);
    }
    int flag = test(arr1, 20, 10000);
    flag |= test(arr2, 20, -100.123);
    return flag;
}