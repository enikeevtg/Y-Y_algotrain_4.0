/**
 * Подсчёт количества элементов массива, которые меньше опорного:
 * 
 * Алгоритм подсчёта реализован простым перебором элементов массива и
 * прописан внутри класса QSArray в методе PivotLessValuesCount()
**/

#include <iostream>

class QSArray {
 public:
  QSArray() {}
  QSArray(size_t size) : size_(size) { array_ = new int[size_]{}; }
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

  int PivotLessValuesCount(const int& pivot) {
    int less_counter = 0;
    for (int i = 0; i < size_; ++i) {
      if (array_[i] < pivot) ++less_counter;
    }
    return less_counter;
  }

 private:
  size_t size_{0};
  int* array_{nullptr};
};

int main() {
  size_t array_length = 0;
  std::cin >> array_length;
  QSArray array(array_length);
  array.FillArray();

  int pivot_value = 0;
  std::cin >> pivot_value;
  int less = array.PivotLessValuesCount(pivot_value);
  int greater = array_length - less;

  std::cout << less << std::endl << greater << std::endl;

  return 0;
}
