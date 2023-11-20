/**
 * Partition:
 * 
 * Алгоритм подсчёта прописан в main() с использованием метода
 * FirstElemNotIf()
 * 
 * В классе QSArray реализован шаблонный метод FirstElemNotIf(), возвращающий
 * итератор (указатель) на первый элемент массива (начиная с указателя на
 * некоторый элемент) не удовлетворяющий условию предиката
 * 
 * Предикат выполнен в виде функционального объекта класса LessThanPivot
**/

#include <iostream>

// Functor: Less Than Pivot
class LessThanPivot {
 public:
  LessThanPivot(const int& pivot_value) : pivot_(pivot_value) {}

  bool operator()(const int& value) {
    return value < pivot_;
  }

 private:
  int pivot_{0};
};

// Functor: Greater Than Or Equal To Pivot
class GreaterThanOrEqualToPivot {
 public:
  GreaterThanOrEqualToPivot(const int& pivot_value) : pivot_(pivot_value) {}

  bool operator()(const int& value) {
    return value >= pivot_;
  }

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
  int* FirstElemIf(int* first, int* last, predicate_functor predicate) {
    while (first != last && predicate(*first) == false) ++first;
    return first;
  }

  template <typename predicate_functor>
  int* LastElemIf(int* first, int* last, predicate_functor predicate) {
    while (last != first && predicate(*last) == false) --last;
    return last;
  }

  void Partition(int* first, int* last, const int& pivot) {
    GreaterThanOrEqualToPivot pred_greater_or_equal(pivot);
    LessThanPivot pred_less(pivot);

    int* ptr_greater_or_equal = first;
    int* ptr_less = last;
    while (ptr_greater_or_equal < ptr_less) {
      ptr_greater_or_equal = FirstElemIf(first, last, pred_greater_or_equal);
      ptr_less = LastElemIf(first, last, pred_less);
      // std::cout << *ptr_greater_or_equal << ' ' << *ptr_less << std::endl;
      if (ptr_greater_or_equal < ptr_less) Swap(ptr_greater_or_equal, ptr_less);
      first = ptr_greater_or_equal;
      last = ptr_less;
    }
    size_t less_than_pivot = last - array_;
    if (last != first) ++less_than_pivot;
    std::cout << less_than_pivot << std::endl << size_ - less_than_pivot << std::endl;
    // int* ptr = array_;
    // for (; ptr <= last; ++ptr) {
    //   std::cout << *ptr << ' ';
    // }
    // std::cout << std::endl;

    // for (; ptr < array_ + size_; ++ptr) {
    //   std::cout << *ptr << ' ';
    // }
    // std::cout << std::endl;
  }

  void RandPartition(int* first, int* last) {
    int pivot = *(first + std::rand() % (last + 1 - first));
    std::cout << pivot << std::endl;
    Partition(first, last, pivot);

    // GreaterThanOrEqualToPivot pred_greater_or_equal(pivot);
    // LessThanPivot pred_less(pivot);

    // int* ptr_greater_or_equal = first;
    // int* ptr_less = last;
    // while (ptr_greater_or_equal < ptr_less) {
    //   PrintArray();
    //   ptr_greater_or_equal = FirstElemIf(first, last, pred_greater_or_equal);
    //   ptr_less = LastElemIf(first, last, pred_less);
    //   std::cout << *ptr_greater_or_equal << ' ' << *ptr_less << std::endl;
    //   if (ptr_greater_or_equal < ptr_less) Swap(ptr_greater_or_equal, ptr_less);
    //   first = ptr_greater_or_equal;
    //   last = ptr_less;
    // }
    // PrintArray();
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
  array.Partition(array.Begin(), array.End() - 1, pivot_value);

  return 0;
}
