/**
 * Подсчёт количества элементов массива, которые меньше опорного:
 * 
 * Алгоритм подсчёта прописан в main() с использованием метода
 * FirstElemsCountIf()
 * 
 * В классе QSArray реализован шаблонный метод FirstElemsCountIf(), возвращающий
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

  template <typename predicate_functor>
  size_t FirstElemsCountIf(int* begin, predicate_functor pred_) {
    size_t count = 0;
    int* ptr = begin;
    int* end = array_ + size_;
    while (ptr != end && pred_(*ptr) == true) {
      ++count;
      ++ptr;
    }
    return count;
  }

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

int main() {
  size_t array_length = 0;
  std::cin >> array_length;
  QSArray array(array_length);
  array.FillArray();

  int pivot_value = 0;
  std::cin >> pivot_value;
  LessThanPivot comparison(pivot_value);

  size_t less_count = 0;
  int* ptr = array.Begin();
  int* end = array.End();
  while (ptr != end) {
    size_t part_length = array.FirstElemsCountIf(ptr, comparison);
    less_count += part_length;
    ptr += part_length;
    if (part_length == 0) ++ptr;
  }
  size_t other_count = array_length - less_count;

  std::cout << less_count << std::endl << other_count << std::endl;

  return 0;
}
