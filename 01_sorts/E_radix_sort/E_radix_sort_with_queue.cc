/**
 * RadixSort:
 *
 * Алгоритм поразрядной сортировки массива строк одинаковой длины реализован
 * в методе RadixSort() класса RSArray.
 * Используется суперсложный подход с использованием очереди для хранения строк
 * на каждой фазе сортировки. Итераторы в очереди было лень писать, поэтому
 * пришлось вынести структуру узла из класса HalfQueue, а доступ к голове
 * и хвосту предоставить через геттеры.
 * 
 * Ошибка, допущенная с использованием очередей:
 * использовалась только один массив очередей, который перезаписывался во время
 * прохождения по элементам его элементов. В следствие этого решение закольцовывалось и уходило в бесконечный цикл.
 * Исправление:
 * Введен буфферный массив очередей
 * 
 * Проще изначально не усложнять решение и не плодить лишние сущности.
 * То же самое можно сделать двумя массивами данных и вспомогательными
 * массивами подсчёта и позиций вставок (см. скрин)
 **/

#include <iostream>

const int strlen = 21;
const int nill_code = 48;

template <typename T>
struct QNode {
  QNode<T>* next{nullptr};
  T data;
};

template <typename T>
class HalfQueue {
 public:

  HalfQueue() {}
  ~HalfQueue() {
    while (size_ != 0) {
      QNode<T>* tmp = head_;
      head_ = head_->next;
      delete tmp;
      --size_;
    }
  }

  QNode<T>* GetRoot() { return head_; }
  QNode<T>* GetTail() { return tail_; }

  void Push(const T& data_value) {
    if (size_ == 0) {
      head_ = new QNode<T>;
      tail_ = head_;
    } else {
      tail_->next = new QNode<T>;
      tail_ = tail_->next;
    }
    tail_->data = data_value;
    ++size_;
  }

  void MoveFromOtherQueue(HalfQueue& other) {
    if (size_ == 0) {
      head_ = other.head_;
      tail_ = other.head_;
      other.head_ = other.head_->next;
      tail_->next = nullptr;
    } else {
      tail_->next = other.head_;
      other.head_ = (other.head_)->next;
      tail_ = tail_->next;
      tail_->next = nullptr;
    }
    ++size_;
    --other.size_;
  }

  void PrintQueue() {
    if (size_ == 0) {
      std::cout << "empty\n";
    } else {
      QNode<T>* ptr = head_;
      for (; ptr != nullptr; ptr = ptr->next) {
        std::cout << ptr->data;
        if (ptr != tail_) std::cout << ", ";
      }
      std::cout << std::endl;
    }
  }

 private:
  QNode<T>* head_{nullptr};
  QNode<T>* tail_{nullptr};
  size_t size_{0};
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
      HalfQueue<char*>* buckets = new HalfQueue<char*>[10];
      HalfQueue<char*>* buckets_buffer = new HalfQueue<char*>[10];
      
      // first phase of sorting
      for (size_t i = 0; i < size_; ++i) {
        int k = array_[i][number_pos] - nill_code;
        buckets[k].Push(array_[i]);
      }
      --number_pos;

      // other phases of sorting
      int phase = 2;
      for (; number_pos >= 0; --number_pos, ++phase) {
        for (int i = 0; i < 10; ++i) {
          for (QNode<char*>* ptr = buckets[i].GetRoot();
               ptr != nullptr;) {
            int k = ptr->data[number_pos] - nill_code;
            ptr = ptr->next;
            buckets_buffer[k].MoveFromOtherQueue(buckets[i]);
          }
        }
        HalfQueue<char*>* buckets_tmp = buckets;
        buckets = buckets_buffer;
        buckets_buffer = buckets_tmp;
      }  // for 1...m-1 number positions

      // from queue to array
      int j = 0;
      for (int i = 0; i < 10; ++i) {
        for (QNode<char*>* ptr = buckets[i].GetRoot();
               ptr != nullptr;) {
            array_[j] = ptr->data;
            ++j;
            ptr = ptr->next;
        }
      }

      delete[] buckets;
      delete[] buckets_buffer;
    }
  }

  void RadixSortWithReport() {
    std::cout << "Initial array:\n";
    PrintArray();

    if (size_ > 0) {
      int number_pos = string_size_ - 1;
      HalfQueue<char*>* buckets = new HalfQueue<char*>[10];
      HalfQueue<char*>* buckets_buffer = new HalfQueue<char*>[10];
      
      // first phase of sorting
      for (size_t i = 0; i < size_; ++i) {
        int k = array_[i][number_pos] - nill_code;
        buckets[k].Push(array_[i]);
      }
      --number_pos;
      std::cout << "**********\nPhase 1\n";
      for (int i = 0; i < 10; ++i) {
        std::cout << "Bucket " << i << ": "; 
        buckets[i].PrintQueue();
      }

      // other phases of sorting
      int phase = 2;
      for (; number_pos >= 0; --number_pos, ++phase) {
        std::cout << "**********\nPhase " << phase << std::endl;
        for (int i = 0; i < 10; ++i) {
          for (QNode<char*>* ptr = buckets[i].GetRoot();
               ptr != nullptr;) {
            int k = ptr->data[number_pos] - nill_code;
            ptr = ptr->next;
            buckets_buffer[k].MoveFromOtherQueue(buckets[i]);
          }
        }
        HalfQueue<char*>* buckets_tmp = buckets;
        buckets = buckets_buffer;
        buckets_buffer = buckets_tmp;
        for (int i = 0; i < 10; ++i) {
          std::cout << "Bucket " << i << ": "; 
          buckets[i].PrintQueue();
        }
      }  // for 1...m-1 number positions

      // from queue to array
      int j = 0;
      for (int i = 0; i < 10; ++i) {
        for (QNode<char*>* ptr = buckets[i].GetRoot();
               ptr != nullptr;) {
            array_[j] = ptr->data;
            ++j;
            ptr = ptr->next;
        }
      }

      delete[] buckets;
      delete[] buckets_buffer;
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
