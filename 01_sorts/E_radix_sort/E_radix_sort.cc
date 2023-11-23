/**
 * RadixSort:
 *
 * Алгоритм поразрядной сортировки массива строк одинаковой длины реализован
 * в методе RadixSort() класса RSArray.
 * Для вывода поэтапного отчёта по сортировке сделан расширенный метод
 * RedixSortWithReport()
 **/

#include <iostream>

const int strlen = 21;
const int nill_code = 48;

class RSArray {
 public:
  RSArray() {}
  RSArray(size_t size) : size_(size) {
    array_ = new char* [size_] {};
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
    getchar();
    for (int i = 0; i < size_; ++i) {
      char ch = '\0';
      int j = 0;
      while ((ch = getchar()) != '\n') {
        array_[i][j] = ch;
        ++j;
      }
    }
    char* ptr = array_[0];
    while (*ptr != '\0') ++ptr;
    string_size_ = ptr - array_[0];
  }

  void PrintArray() {
    for (int i = 0; i < size_ - 1; ++i) {
      std::cout << array_[i] << ", ";
    }
    std::cout << array_[size_ - 1] << std::endl;
  }

  void RadixSort() {
    if (size_ > 0) {
      int number_pos = string_size_ - 1;
      char** buffer = new char*[size_];

      while (number_pos >= 0) {
        unsigned int buckets_capacities[10]{};
        unsigned int insertion_positions[10]{};
        for (size_t i = 0; i < size_; ++i) {
          int k = array_[i][number_pos] - nill_code;
          ++buckets_capacities[k];
        }
        for (size_t i = 1; i < 10; ++i) {
          insertion_positions[i] =
              insertion_positions[i - 1] + buckets_capacities[i - 1];
        }
        for (int i = 0; i < size_; ++i) {
          int k = array_[i][number_pos] - nill_code;
          int pos = insertion_positions[k];
          ++insertion_positions[k];
          buffer[pos] = array_[i];
        }
        char** tmp = array_;
        array_ = buffer;
        buffer = tmp;
        --number_pos;
      }
      delete[] buffer;
    }
  }

  void RadixSortWithReport() {
    std::cout << "Initial array:\n";
    PrintArray();

    if (size_ > 0) {
      int number_pos = string_size_ - 1;
      int phase = 1;
      char** buffer = new char*[size_];

      while (number_pos >= 0) {
        int buckets_capacities[10]{};
        int insertion_positions[10]{};
        int insertion_positions_output[10]{};
        for (size_t i = 0; i < size_; ++i) {
          int k = array_[i][number_pos] - nill_code;
          ++buckets_capacities[k];
        }

        for (size_t i = 1; i < 10; ++i) {
          insertion_positions[i] =
              insertion_positions[i - 1] + buckets_capacities[i - 1];
          insertion_positions_output[i] = insertion_positions[i];
        }

        for (int i = 0; i < size_; ++i) {
          int k = array_[i][number_pos] - nill_code;
          int pos = insertion_positions[k];
          ++insertion_positions[k];
          buffer[pos] = array_[i];
        }

        std::cout << "**********\nPhase " << phase << std::endl;
        for (int i = 0; i < 10; ++i) {
          std::cout << "Bucket " << i << ": ";
          int j = insertion_positions_output[i];
          if (j < insertion_positions[i]) {
            for (; j < insertion_positions[i] - 1; ++j) {
              std::cout << buffer[j] << ", ";
            }
            std::cout << buffer[j] << std::endl;
          } else {
            std::cout << "empty" << std::endl;
          }
        }

        char** tmp = array_;
        array_ = buffer;
        buffer = tmp;
        --number_pos;
        ++phase;
      }
      delete[] buffer;
    }
    std::cout << "**********\nSorted array:\n";
    PrintArray();
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
  array.RadixSortWithReport();

  return 0;
}
