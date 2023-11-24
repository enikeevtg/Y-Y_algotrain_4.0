/**
 * Merge:
 *
 * Алгоритм слияния двух массивов отсортированных по неубыванию реализован
 * в методе MergeSortedArrays() класса MSArray. Метод принимает в качестве
 * параметра другой массив и возвращает объект класса MSArray.
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

  int* array_{nullptr};
  size_t size_{0};
};

int main() {
  size_t first_array_length = 0;
  std::cin >> first_array_length;
  MSArray first_array(first_array_length);
  first_array.FillArray();

  size_t second_array_length = 0;
  std::cin >> second_array_length;
  MSArray second_array(second_array_length);
  second_array.FillArray();

  MSArray result_array = first_array.MergeSortedArrays(second_array);
  result_array.PrintArray();
  return 0;
}
