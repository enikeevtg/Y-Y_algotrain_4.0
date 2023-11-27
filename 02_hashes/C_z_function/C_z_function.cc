#include <iostream>
#include <string>

const int kHashNumber = 1;  // количество пар x-p (степень-модуль)
const int kXArray[kHashNumber] = {257};
const int kModulesArray[kHashNumber] = {1000000007};

class HString {
 public:
  HString() {}
  HString(const size_t size, const char* input) : size_(size), str_(input) {
    hash_tables_array_ = new uint*[kHashNumber] {};
    x_pows_arrays_array_ = new uint*[kHashNumber] {};
    for (int i = 0; i < kHashNumber; ++i) {
      hash_tables_array_[i] = new uint[size_ + 1];
      x_pows_arrays_array_[i] = new uint[size_ + 1];
    }
    PrefixHashes();
  }
  ~HString() {
    for (int i = 0; i < kHashNumber; ++i) {
      delete[] hash_tables_array_[i];
      delete[] x_pows_arrays_array_[i];
    }
    delete[] hash_tables_array_;
    delete[] x_pows_arrays_array_;
  }

  void Print() {
    for (size_t i = 0; i < size_; ++i) {
      std::cout << str_[i];
    }
    std::cout << std::endl;
  }

  void PrintHashes() {
    for (int table_id = 0; table_id < kHashNumber; ++table_id) {
      for (size_t i = 0; i < size_ + 1; ++i) {
        std::string tmp_str(str_, i);
        std::cout << tmp_str << ": " << hash_tables_array_[table_id][i]
                  << std::endl;
      }
    }
  }

  bool PartsEquality(const int& l, const int& f1, const int& f2) {
    for (int i = 0; i < kHashNumber; ++i) {
      uint hash_f1 = hash_tables_array_[i][f1];
      uint hash_f2 = hash_tables_array_[i][f2];
      uint hash_l1 = hash_tables_array_[i][f1 + l];
      uint hash_l2 = hash_tables_array_[i][f2 + l];
      uint x = x_pows_arrays_array_[i][l];
      int p = kModulesArray[i];

      if ((hash_l1 + hash_f2 * x) % p != (hash_l2 + hash_f1 * x) % p) {
        return false;
      }
    }
    return true;
  }

  int LineBase() {
    int base = 1;
    while (base < size_) {
      uint hash_f1 = hash_tables_array_[0][0];
      uint hash_f2 = hash_tables_array_[0][base];
      uint hash_l1 = hash_tables_array_[0][size_ - base];
      uint hash_l2 = hash_tables_array_[0][size_];
      uint x = x_pows_arrays_array_[0][size_ - base];
      int p = kModulesArray[0];

      if ((hash_l1 + hash_f2 * x) % p == (hash_l2 + hash_f1 * x) % p) {
        return base;
      }
      ++base;
    }
    return base;
  }

  int* ZFunction_v1(int*& z_array) {  // TL test 92
    z_array[0] = 0;
    for (size_t i = 1; i < size_; ++i) {
      int lenght = 0;
      uint hash_f1 = hash_tables_array_[0][0];
      uint hash_f2 = hash_tables_array_[0][i];
      uint hash_l1, hash_l2;
      uint x;
      int p = kModulesArray[0];
      do {
        ++lenght;
        hash_l1 = hash_tables_array_[0][lenght];
        hash_l2 = hash_tables_array_[0][i + lenght];
        x = x_pows_arrays_array_[0][lenght];
      } while (((hash_l1 + hash_f2 * x) % p == (hash_l2 + hash_f1 * x) % p));

      z_array[i] = --lenght;
    }
    return z_array;
  }

  int* ZFunction_v2(int*& z_array) {  // TL test 84
    z_array[0] = 0;
    for (size_t i = 1; i < size_; ++i) {
      int lenght = size_ - i;
      uint hash_f1 = hash_tables_array_[0][0];
      uint hash_f2 = hash_tables_array_[0][i];
      uint hash_l1 = hash_tables_array_[0][lenght];
      uint hash_l2 = hash_tables_array_[0][i + lenght];
      uint x = x_pows_arrays_array_[0][lenght];
      int p = kModulesArray[0];
      while (lenght > 0 &&
             ((hash_l1 + hash_f2 * x) % p != (hash_l2 + hash_f1 * x) % p)) {
        --lenght;
        hash_l1 = hash_tables_array_[0][lenght];
        hash_l2 = hash_tables_array_[0][i + lenght];
        x = x_pows_arrays_array_[0][lenght];
      }

      z_array[i] = lenght;
    }
    return z_array;
  }

  int* ZFunction(int*& z_array) {  // with binary searching
    z_array[0] = 0;
    uint hash_f1 = hash_tables_array_[0][0];
    int p = kModulesArray[0];
    for (size_t i = 1; i < size_; ++i) {
      bool equal = true;
      int lenght = size_ - i;
      uint hash_f2 = hash_tables_array_[0][i];
      uint hash_l1 = hash_tables_array_[0][lenght];
      uint hash_l2 = hash_tables_array_[0][i + lenght];
      uint x = x_pows_arrays_array_[0][lenght];
      if ((hash_l1 + hash_f2 * x) % p != (hash_l2 + hash_f1 * x) % p) {
        int left = 0;
        int right = size_ - i;
        while (left < right) {
          lenght = (left + right) / 2;
          hash_l1 = hash_tables_array_[0][lenght];
          hash_l2 = hash_tables_array_[0][i + lenght];
          x = x_pows_arrays_array_[0][lenght];
          if ((hash_l1 + hash_f2 * x) % p != (hash_l2 + hash_f1 * x) % p) {
            right = lenght;
            equal = false;
          } else {
            left = lenght + 1;
            equal = true;
          }
        }
      }
      if (equal == false) --lenght;
      z_array[i] = lenght;
    }

    return z_array;
  }

 private:
  using uint = unsigned long int;

  void PrefixHashes() {
    for (int table_id = 0; table_id < kHashNumber; ++table_id) {
      uint* hash = hash_tables_array_[table_id];
      uint* x_pows = x_pows_arrays_array_[table_id];
      int x_ = kXArray[table_id];
      int p_ = kModulesArray[table_id];

      hash[0] = 0;
      x_pows[0] = 1;
      for (int i = 1; i <= size_; ++i) {
        hash[i] = (hash[i - 1] * x_ + str_[i - 1]) % p_;
        x_pows[i] = (x_pows[i - 1] * x_) % p_;
      }
    }
  }

  void PrefixHashesDebug() {
    int ascii_numbers_offset = 48;
    for (int table_id = 0; table_id < kHashNumber; ++table_id) {
      uint* hash = hash_tables_array_[0];
      uint* x_pows = x_pows_arrays_array_[0];
      int x_ = 10;
      int p_ = 1e9 + 7;

      hash[0] = 0;
      x_pows[0] = 1;
      for (int i = 1; i <= size_; ++i) {
        hash[i] = (hash[i - 1] * x_ + str_[i - 1] - ascii_numbers_offset) % p_;
        x_pows[i] = (x_pows[i - 1] * x_) % p_;
      }
    }
  }

  const char* str_{nullptr};
  int size_{0};
  uint** hash_tables_array_{nullptr};
  uint** x_pows_arrays_array_{nullptr};
};

int main() {
  std::string input;
  std::cin >> input;
  size_t str_len = input.length();
  HString string(str_len, input.data());
  int* z_array = new int[str_len]{};
  z_array = string.ZFunction(z_array);
  for (int i = 0; i < str_len; ++i) {
    std::cout << z_array[i] << ' ';
  }
  std::cout << '\n';
  delete[] z_array;
  return 0;
}
