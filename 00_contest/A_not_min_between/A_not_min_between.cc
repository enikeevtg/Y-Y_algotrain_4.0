#include <iostream>

class Array {
 public:
  Array(int size) : size_(size) { array_ = new int[size_]; }
  ~Array() { delete[] array_; }

  int& operator[](const int& pos) { return array_[pos]; }
  int operator[](const int& pos) const { return array_[pos]; }

  void Fill() {
    for (int i = 0; i < size_; ++i) {
      std::cin >> array_[i];
    }
  }

  int MinBetween(int l_bound, int r_bound) {
    int min = array_[l_bound];
    for (int i = l_bound + 1; i <= r_bound; ++i) {
      if (array_[i] < min) min = array_[i];
    }
    return min;
  }

  void PrintAnyNotMinBetween(int l_bound, int r_bound) {
    int min = MinBetween(l_bound, r_bound);
    int i = l_bound;
    while (array_[i] == min && i <= r_bound) ++i;
    if (i <= r_bound && array_[i] != min) {
      std::cout << array_[i] << std::endl;
    } else {
      std::cout << "NOT FOUND" << std::endl;
    }
  }

  void PrintArray() {
    for (int i = 0; i < size_; ++i) {
      std::cout << array_[i] << ' ';
    }
  }

 private:
  int* array_{nullptr};
  size_t size_{0};
};

int main(int argc, char** argv) {
  int N, M;
  std::cin >> N >> M;

  Array array(N);
  array.Fill();
  for (int i = 0; i < M; ++i) {
    int L, R;
    std::cin >> L >> R;
    array.PrintAnyNotMinBetween(L, R);
  }

  return 0;
}
