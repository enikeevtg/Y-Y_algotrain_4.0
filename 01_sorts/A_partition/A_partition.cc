/**
 * Partition:
 *
 * Алгоритм разибения для быстрой сортировки реализован в методе Partition()
 * класса QSArray
 *
 * В классе QSArray реализован шаблонные методы FindFirstElem() и
 * FindLastElem(), возвращающие итератор (указатель) на первый
 * и последний элемент массива соответственно (начиная с указателя на
 * некоторый элемент) удовлетворяющий условию предиката
 *
 * Предикаты выполнен в виде функциональных объектов классов LessThanPivot и
 * GreaterThanOrEqualToPivot
 **/

#include <iostream>

// Functor: Less Than Pivot
class LessThanPivot {
 public:
  LessThanPivot(const int& pivot_value) : pivot_(pivot_value) {}

  bool operator()(const int& value) { return value < pivot_; }

 private:
  int pivot_{0};
};

// Functor: Greater Than Or Equal To Pivot
class GreaterThanOrEqualToPivot {
 public:
  GreaterThanOrEqualToPivot(const int& pivot_value) : pivot_(pivot_value) {}

  bool operator()(const int& value) { return value >= pivot_; }

 private:
  int pivot_{0};
};

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

  void Swap(int* first, int* second) {
    int tmp = *first;
    *first = *second;
    *second = tmp;
  }

  template <typename predicate_functor>
  int* FindFirstElem(int* begin, int* end, predicate_functor predicate) {
    while (begin != end && predicate(*begin) == false) ++begin;
    if (begin == end) begin = nullptr;
    return begin;
  }

  template <typename predicate_functor>
  int* FindLastElem(int* begin, int* end, predicate_functor predicate) {
    --end;
    while (end != begin && predicate(*end) == false) --end;
    if (end == begin && predicate(*end) == false) end = nullptr;
    return end;
  }

  int* Partition(int* begin, int* end, const int& pivot) {
    GreaterThanOrEqualToPivot pred_greater_or_equal(pivot);
    LessThanPivot pred_less(pivot);

    int* ptr_greater_or_equal = begin;
    int* ptr_less = end;
    while (ptr_greater_or_equal && ptr_less &&
           ptr_greater_or_equal < ptr_less) {
      ptr_greater_or_equal = FindFirstElem(begin, end, pred_greater_or_equal);
      ptr_less = FindLastElem(begin, end, pred_less);

      if (ptr_greater_or_equal && ptr_less) {
        if (ptr_greater_or_equal < ptr_less) {
          Swap(ptr_greater_or_equal, ptr_less);
        }
        begin = ptr_greater_or_equal;
        end = ptr_less;
      } else if (!ptr_greater_or_equal && ptr_less) {
        begin = ptr_less + 1;
      }
    }

    return begin;
  }

  int* RandPartition(int* begin, int* end) {
    int pivot = *(begin + std::rand() % (end + 1 - begin));
    std::cout << pivot << std::endl;
    return Partition(begin, end, pivot);
  }

 private:
  int* array_{nullptr};
  size_t size_{0};
};

int main() {
  size_t array_length = 0;
  std::cin >> array_length;
  QSArray array(array_length);
  array.FillArray();

  int pivot_value = 0;
  std::cin >> pivot_value;
  int* bound = array.Partition(array.Begin(), array.End(), pivot_value);

  size_t less_than_pivot = bound - array.Begin();
  std::cout << less_than_pivot << std::endl
            << array_length - less_than_pivot << std::endl;

  // Вывод частей массива
  for (int* ptr = array.Begin(); ptr < bound; ++ptr) {
    std::cout << *ptr << ' ';
  }
  std::cout << std::endl;

  for (int* ptr = bound; ptr < array.Begin() + array_length; ++ptr) {
    std::cout << *ptr << ' ';
  }
  std::cout << std::endl;

  return 0;
}
