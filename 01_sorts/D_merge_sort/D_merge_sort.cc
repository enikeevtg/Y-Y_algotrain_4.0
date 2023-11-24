/**
 * MergeSort:
 *
 * Алгоритм слияния двух массивов отсортированных по неубыванию реализован
 * в методе MergeSortedArrays() класса Array. Метод принимает в качестве
 * параметра другой массив и возвращает объект класса Array.
 * 
 *
 * Алгоритм сортировки слиянием реализован в методе MergeSort()
 * класса MArray. Метод MergeSort() вызывает MergeSort(begin, end, buffer),
 * внутри которой происходит разделенение куска массива на две части и
 * рекурсивный вызов MergeSort(begin, end, buffer). Когда кусок массива
 * достигает минимального рамера вызывается метод
 * MergeSortedArrays(begin_1, end_1, begin_2, end_2, buffer), а далее рекурсия
 * начинает разматываться.
 * 
 * Исползование дополнительной памяти O(2N)
 **/

#include <iostream>

class MSArray {
 public:
  MSArray() {}
  MSArray(size_t size) : size_(size) { array_ = new int[size_]{}; }
  ~MSArray() { delete[] array_; }

  void FillArray() {
    for (int i = 0; i < size_; ++i) {
      std::cin >> array_[i];
    }
  }

  void PrintArray() {
    for (int i = 0; i < size_; ++i) {
      std::cout << array_[i] << ' ';
    }
    std::cout << std::endl;
  }

  int* Begin() { return array_; }

  int* End() { return array_ + size_; }

  void MergeSort() {
    if (size_ > 1) {
      int* before_mergesort = array_;
      array_ = new int[size_]{};
      MergeSort(before_mergesort, before_mergesort + size_, array_);
      delete[] before_mergesort;
    }
  }

  void MergeSort(int* begin, int* end, int* buffer) {
    int* begin_1 = begin;
    int* begin_2 = begin + (end - begin) / 2;
    int* end_1 = begin_2;
    int* end_2 = end;
    if (end_1 - begin_1 > 1) {
      size_t buffer_size = end_1 - begin_1;
      int* buffer = new int[buffer_size]{};
      MergeSort(begin_1, end_1, buffer);
      begin_1 = buffer;
      end_1 = begin_1 + buffer_size;
    }
    if (end_2 - begin_2 > 1) {
      size_t buffer_size = end_2 - begin_2;
      int* buffer = new int[buffer_size]{};
      MergeSort(begin_2, end_2, buffer);
      begin_2 = buffer;
      end_2 = begin_2 + buffer_size;
    }

    MergeSortedArrays(begin_1, end_1, begin_2, end_2, buffer);

    if (end_1 - begin_1 > 1) delete[] begin_1;
    if (end_2 - begin_2 > 1) delete[] begin_2;
  }

  MSArray MergeSortedArrays(const MSArray& other) {
    MSArray merged(size_ + other.size_);
    int* first = array_;
    int* first_end = array_ + size_;
    int* second = other.array_;
    int* second_end = other.array_ + other.size_;
    int* ptr = merged.array_;
    while (first != first_end && second != second_end) {
      if (*first <= *second) {
        *ptr = *first;
        ++first;
      } else {
        *ptr = *second;
        ++second;
      }
      ++ptr;
    }
    while (first != first_end) {
      *ptr = *first;
      ++first;
      ++ptr;
    }
    while (second != second_end) {
      *ptr = *second;
      ++second;
      ++ptr;
    }

    return merged;
  }

 private:
  void Swap(int* first, int* second) {
    int tmp = *first;
    *first = *second;
    *second = tmp;
  }

  void MergeSortedArrays(int* begin_1, int* end_1, int* begin_2, int* end_2,
                         int* buffer) {
    while (begin_1 != end_1 && begin_2 != end_2) {
      if (*begin_1 <= *begin_2) {
        *buffer = *begin_1;
        ++begin_1;
      } else {
        *buffer = *begin_2;
        ++begin_2;
      }
      ++buffer;
    }
    while (begin_1 != end_1) {
      *buffer = *begin_1;
      ++begin_1;
      ++buffer;
    }
    while (begin_2 != end_2) {
      *buffer = *begin_2;
      ++begin_2;
      ++buffer;
    }
  }

  int* array_{nullptr};
  size_t size_{0};
};

int main() {
  size_t array_length = 0;
  std::cin >> array_length;
  MSArray array(array_length);
  array.FillArray();
  array.MergeSort();
  array.PrintArray();

  return 0;
}
