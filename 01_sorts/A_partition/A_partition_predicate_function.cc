/**
 * Подсчёт количества элементов массива, которые меньше опорного:
 * 
 * Алгоритм подсчёта реализован простым перебором элементов массива и
 * прописан в функции CountIf() с использованием функции-предиката
 * LessThan()
**/

#include <iostream>

class QSArray {
 public:
  QSArray() {}
  QSArray(size_t size) : size_(size) { array_ = new int[size_ + 1]{}; }
  ~QSArray() { delete[] array_; }

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

 private:
  size_t size_{0};
  int* array_{nullptr};
  int pivot_{0};
};

size_t CountIf(int* begin, int* end, bool (*pred)(int, int), int pivot) {
  size_t counter = 0;
  int* ptr = begin;
  while (ptr < end) {
    if (pred(*ptr, pivot) == true) ++counter;
    ++ptr;
  }
  return counter;
}

// Predicate function
bool LessThan(int value, int pivot) { return value < pivot; }

int main() {
  size_t array_length = 0;
  std::cin >> array_length;
  QSArray array(array_length);
  array.FillArray();

  int pivot_value = 0;
  std::cin >> pivot_value;
  int less = CountIf(array.Begin(), array.End(), LessThan, pivot_value);
  int greater = array_length - less;

  std::cout << less << std::endl << greater << std::endl;

  return 0;
}
