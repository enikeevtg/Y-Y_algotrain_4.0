/**
 * Подсчёт количества элементов массива, которые меньше опорного:
 *
 * Алгоритм подсчёта реализован простым перебором элементов массива и
 * прописан в функции CountIf() с использованием функционального объекта
 * класса LessThanPivot
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
};

// Return number of elements in range satisfying condition 'pred'
template <typename iterator, typename predicate>
size_t CountIf(iterator begin, iterator end, predicate pred) {
  size_t counter = 0;
  int* ptr = begin;
  while (ptr < end) {
    if (pred(*ptr) == true) ++counter;
    ++ptr;
  }
  return counter;
}

// Functor
class LessThanPivot {
 public:
  LessThanPivot(int pivot) : pivot_(pivot) {}
  ~LessThanPivot() {}

  bool operator()(const int& value) { return value < pivot_; }

 private:
  int pivot_{0};
};

int main() {
  size_t array_length = 0;
  std::cin >> array_length;
  QSArray array(array_length);
  array.FillArray();

  int pivot_value = 0;
  std::cin >> pivot_value;
  LessThanPivot pred(pivot_value);
  int less = CountIf(array.Begin(), array.End(), pred);
  int greater = array_length - less;

  std::cout << less << std::endl << greater << std::endl;

  return 0;
}
