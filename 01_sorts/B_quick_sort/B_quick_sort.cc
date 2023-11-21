/**
 * QuickSort:
 *
 * Алгоритм быстрой сортировки реализован в методе QuickSort()
 * класса QSArray. Метод QuickSort() основан на методе Partition() из задания A
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
    int cols = 0;
    for (int i = 0; i < size_; ++i) {
      std::cout << array_[i] << ' ';
      ++cols;
      if (cols == 5) {
        std::cout << '\n';
        cols = 0;
      }
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

  // int* Partition(int* begin, int* end, const int& pivot) {
  //   GreaterThanOrEqualToPivot pred_greater_or_equal(pivot);
  //   LessThanPivot pred_less(pivot);

  //   int* ptr_greater_or_equal = begin;
  //   int* ptr_less = end;
  //   while (ptr_greater_or_equal && ptr_less &&
  //          ptr_greater_or_equal < ptr_less) {
  //     ptr_greater_or_equal = FindFirstElem(begin, end,
  //     pred_greater_or_equal); ptr_less = FindLastElem(begin, end, pred_less);

  //     if (ptr_greater_or_equal && ptr_less) {
  //       if (ptr_greater_or_equal < ptr_less) {
  //         Swap(ptr_greater_or_equal, ptr_less);
  //       }
  //       begin = ptr_greater_or_equal;
  //       end = ptr_less;
  //     } else if (!ptr_greater_or_equal && ptr_less) {
  //       begin = ptr_less + 1;
  //     }
  //   }

  //   return begin;
  // }

  // int* RandPartition(int* begin, int* end) {
  //   int pivot = *(begin + std::rand() % (end - begin));
  //   return Partition(begin, end, pivot);
  // }

  void QuickSort() {
    if (size_ > 1) QuickSort(array_, array_ + size_);
  }

  void QuickSort(int* begin, int* end) {
    int pivot = *(begin + std::rand() % (end - begin));

    int* ptr_greater_or_equal = begin;
    int* ptr_less = end - 1;
    int* bound = nullptr;  // right part begin (left part afterlast element)
    while (ptr_greater_or_equal < ptr_less) {
      while (ptr_greater_or_equal < ptr_less && *ptr_greater_or_equal < pivot) {
        ++ptr_greater_or_equal;
      }
      while (ptr_less > ptr_greater_or_equal && *ptr_less >= pivot) {
        --ptr_less;
      }

      if (ptr_greater_or_equal < ptr_less) {
        Swap(ptr_greater_or_equal, ptr_less);
      } else {
        bound = ptr_less;
      }
    }

    if (bound == begin && *(bound + 1) == *bound) bound = begin + 1;
    if (bound - begin > 1) QuickSort(begin, bound);
    if (end - bound > 1) QuickSort(bound, end);
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
  array.QuickSort();
  array.PrintArray();
  return 0;
}
