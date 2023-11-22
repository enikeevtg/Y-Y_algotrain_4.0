/**
 * Merge:
 *
 * Алгоритм слияния двух массивов отсортированных по неубыванию реализован
 * в методе MergeSortedArrays() класса Array. Метод принимает в качестве
 * параметра другой массив и возвращает объект класса Array.
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

class Array {
  /* PUBLIC SECTION */
 public:
  Array() {}
  Array(size_t size) : size_(size) { array_ = new int[size_]{}; }
  ~Array() { delete[] array_; }

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

  void QuickSort() {
    if (size_ > 1) QuickSort(array_, array_ + size_);
  }

  void QuickSort(int* begin, int* end) {
    int pivot = *(begin + std::rand() % (end - begin));
    int* bound = Partition(begin, end, pivot);
    if (bound - begin > 1) QuickSort(begin, bound);
    while (bound < end && *bound == pivot) ++bound;
    if (end - bound > 1) QuickSort(bound, end);
  }

  Array MergeSortedArrays(const Array& other) {
    Array merged(size_ + other.size_);
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

  /* PRIVATE SECTION */
 private:
  void Swap(int* first, int* second) {
    int tmp = *first;
    *first = *second;
    *second = tmp;
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
    int pivot = *(begin + std::rand() % (end - begin));
    return Partition(begin, end, pivot);
  }

  int* array_{nullptr};
  size_t size_{0};
};

int main() {
  size_t first_array_length = 0;
  std::cin >> first_array_length;
  Array first_array(first_array_length);
  first_array.FillArray();

  size_t second_array_length = 0;
  std::cin >> second_array_length;
  Array second_array(second_array_length);
  second_array.FillArray();

  Array result_array = first_array.MergeSortedArrays(second_array);
  result_array.PrintArray();
  return 0;
}
