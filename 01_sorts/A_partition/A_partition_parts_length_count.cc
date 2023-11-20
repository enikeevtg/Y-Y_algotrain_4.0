/**
 * Подсчёт количества элементов массива, которые меньше опорного:
 * 
 * Алгоритм подсчёта прописан в функции PivotLessValuesCount() с использованием
 * шаблонной функции PartLengthCountIf()
 * 
 * Реализована шаблонная функция PartLengthCountIf(), возвращающая
 * количество первых элементов, начиная с указателя на некоторый элемент
 * массива, удовлетворяющих условию предиката
 * 
 * Предикат выполнен в виде функционального объекта класса LessThanPivot
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

  int* Begin() { return array_; }

  int* End() { return array_ + size_; }

 private:
  int* array_{nullptr};
  size_t size_{0};
};

// Functor
class LessThanPivot {
 public:
  LessThanPivot(const int& pivot_value) : pivot_(pivot_value) {}
  bool operator()(const int& value) {
    return value < pivot_;
  }

 private:
  int pivot_{0};
};

template <typename iterator, typename predicate>
size_t PartLengthCountIf(iterator begin, iterator end, predicate pred_) {
  size_t count = 0;
  iterator ptr = begin;
  while (ptr != end && pred_(*ptr) == true) {
    ++count;
    ++ptr;
  }
  return count;
}

size_t PivotLessValuesCount(QSArray* array, const int& pivot_value) {
  size_t count = 0;
  LessThanPivot comparison(pivot_value);
  int* ptr = array->Begin();
  int* end = array->End();
  while (ptr != end) {
    size_t part_length = PartLengthCountIf(ptr, array->End(), comparison);
    count += part_length;
    ptr += part_length;
    if (part_length == 0) ++ptr;
  }
  return count;
}

int main() {
  size_t array_length = 0;
  std::cin >> array_length;
  QSArray array(array_length);
  array.FillArray();

  int pivot_value = 0;
  std::cin >> pivot_value;
  size_t less = PivotLessValuesCount(&array, pivot_value);
  size_t greater = array_length - less;

  std::cout << less << std::endl << greater << std::endl;

  return 0;
}
