/**
 * RadixSort:
 *
 * Алгоритм поразрядной сортировки массива строк одинаковой длины реализован
 * в методе RadixSort() класса RSArray.
 **/

#include <iostream>

const int strlen = 21;

template <typename T>
class SimpleQueue {
 public:
  SimpleQueue() {
    root_ = new QNode;
    tail_ = root_;
  }
  ~SimpleQueue() {
    while (Empty() == false) Pop();
  }

  bool Empty() {
    return root_.next == nullptr;
  }

  void Push(const T& data_value) {
    tail_->next = new QNode;
    tail_ = tail_->next;
    tail_->data = data_value;
  }

  void Pop() {
    QNode* tmp = root_->next;
    delete root_;
    root_ = tmp;
  }

 private:
  struct QNode {
    QNode* next{nullptr};
    T data;
  };

  QNode* root_;
  QNode* tail_;
};


class RSArray {
 public:
  RSArray() {}
  RSArray(size_t size) : size_(size) {
    array_ = new char*[size_]{};
    for (int i = 0; i < size_; ++i) {
      array_[i] = new char[strlen]{};
    }
  }
  ~RSArray() {
    for (int i = 0; i < size_; ++i) {
      delete[] array_[i];
    }
    delete[] array_;
  }

  void FillArray() {
    for (int i = 0; i < size_; ++i) {
      std::cin >> array_[i];
    }
    char* ptr = array_[0];
    while (*ptr != '\0') ++ptr;
    string_size_ = ptr - array_[0];
  }

  void PrintArray() {
    for (int i = 0; i < size_; ++i) {
      std::cout << array_[i] << ' ';
    }
    std::cout << std::endl;
  }

  void PrintRadixSortReport() {
    std::cout << "Initial array:\n";
    PrintArray();
    std::cout << "**********\n";
    // RadixSortWithReport();
    // PrintArray();
  }

  char** Begin() { return array_; }

  char** End() { return array_ + size_; }

  void RadixSortWithReport() {
    if (size_ > 0) {
      RadixSort();
      std::cout << "**********\n";
    }
  }

  void RadixSort() {
    if (size_ > 0) {
      int number_place = string_size_ - 1;

      while (number_place >= 0) {

      }
    }
  }

 private:
  void Swap(char** first, char** second) {
    char* tmp = *first;
    *first = *second;
    *second = tmp;
  }

  char** array_{nullptr};
  size_t size_{0};
  int string_size_{0};
};

int main() {
  size_t array_length = 0;
  std::cin >> array_length;
  RSArray array(array_length);
  array.FillArray();
  array.PrintRadixSortReport();

  return 0;
}
