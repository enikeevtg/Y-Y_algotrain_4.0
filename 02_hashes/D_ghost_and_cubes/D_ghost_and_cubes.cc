#include <iostream>
#include <string>
#include <algorithm>

const int kHashNumber = 1;  // количество пар x-p (степень-модуль)
const int kXArray[kHashNumber] = {257};
const int kModulesArray[kHashNumber] = {1000000007};

class HString {
 public:
  HString() {}
  HString(const size_t size, const char* input) : size_(size), str_(input) {
    hash_tables_array_ = new uint* [kHashNumber] {};
    x_pows_arrays_array_ = new uint* [kHashNumber] {};
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

  void Print() const {
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

  bool PartsEquality(const int &l, const int &f1, const int &f2) {
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

  int* ZFunction(int*& z_array) {
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

  // not good solution, because 1 != 10 but 1 % 9 == 10 % 9
  void PrintCubesCount_v1() {
    std::string polyndrom(str_);
    std::reverse(polyndrom.begin(), polyndrom.end()); 
    HString polyndrom_str(size_, polyndrom.data());

    uint hash_f_real = hash_tables_array_[0][0];
    for (int i = size_ / 2; i >= 0; --i) {
      uint hash_l_real = hash_tables_array_[0][i];
      uint hash_f_unreal = polyndrom_str.hash_tables_array_[0][size_ - 2 * i];
      uint hash_l_unreal = polyndrom_str.hash_tables_array_[0][size_ - i];
      uint x_ = x_pows_arrays_array_[0][i];
      int p_ = kModulesArray[0];
      if ((hash_l_real + hash_f_unreal * x_) % p_ == (hash_l_unreal +
          hash_f_real * x_) % p_) {
        std::cout << size_ - i << ' ';
      }
    }
  }

  void PrintCubesCount(const HString& polyndrom, int cubes_count,
                       int*& positions) {
    uint hash_f_real = hash_tables_array_[0][0];
    for (int i = cubes_count / 2; i >= 0; --i) {
      int pos = positions[i];
      // std::cout << i << ' ' << pos << ' ' << str_ + pos << " - " << 
      // polyndrom.str_ + size_ - pos << "\n";
      uint hash_l_real = hash_tables_array_[0][pos];
      uint hash_f_unreal = polyndrom.hash_tables_array_[0][size_ - 2 * pos];
      uint hash_l_unreal = polyndrom.hash_tables_array_[0][size_ - pos];
      uint x_ = x_pows_arrays_array_[0][pos];
      int p_ = kModulesArray[0];
      if ((hash_l_real + hash_f_unreal * x_) % p_ == (hash_l_unreal +
          hash_f_real * x_) % p_) {
        std::cout << cubes_count - i << ' ';
      }
    }
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
  int cubes_count = 0;
  int colors_count = 0;
  std::cin >> cubes_count >> colors_count;
  std::string input_part;
  std::string input;
  std::string reverse_input;
  int* positions = new int[cubes_count + 1]{};
  positions[0] = 0;
  for (int i = 0; i < cubes_count; ++i) {
    std::cin >> input_part;
    positions[i + 1] = positions[i] + input_part.length();
    input.append(input_part);
    std::reverse(input_part.begin(), input_part.end());
    reverse_input.append(input_part);
  }
  size_t str_len = input.length();
  HString string(str_len, input.data());
  std::reverse(reverse_input.begin(), reverse_input.end());
  HString polyndrom(str_len, reverse_input.data());
  string.PrintCubesCount(polyndrom, cubes_count, positions);
  return 0;
}

// not good solution
// int main() {
//   int cubes_count = 0;
//   int colors_count = 0;
//   std::cin >> cubes_count >> colors_count;
//   std::string input;
//   int input_part;
//   for (int i = 0; i < cubes_count; ++i) {
//     std::cin >> input_part;
//     //not good solution, because 1 != 10 but 1 % 9 == 10 % 9
//     char symb = (input_part % 9 + 48);  // [char49 == 1 ... char57 == 9]
//     input.append(&symb, 1);
//   }
//   size_t str_len = input.length();
//   HString string(str_len, input.data());
//   string.PrintCubesCount();
//   return 0;
// }
