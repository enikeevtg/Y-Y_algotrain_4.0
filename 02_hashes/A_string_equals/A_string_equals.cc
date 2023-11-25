#include <iostream>
#include <string>

const int kHashNumber = 3;  // количество пар x-p (степень-модуль)
const int kXArray[kHashNumber] = {10, 10, 10};
const int kModulesArray[kHashNumber] = {/*1e9 + 7*/ 1000000007, 1000000013, 1000000007};

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
    // int false_count = 0;
    for (int i = 0; i < kHashNumber; ++i) {
      uint hash_f1 = hash_tables_array_[i][f1];
      uint hash_f2 = hash_tables_array_[i][f2];
      uint hash_l1 = hash_tables_array_[i][f1 + l];
      uint hash_l2 = hash_tables_array_[i][f2 + l];
      uint x = x_pows_arrays_array_[i][l];
      int p = kModulesArray[i];

      if ((hash_l1 + hash_f2 * x) % p != (hash_l2 + hash_f1 * x) % p) {
        // ++false_count;
        return false;
      }
    }
    return true;
  }

 private:
  using uint = unsigned long long int;

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
        x_pows[i] = x_pows[i - 1] * x_;
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
        x_pows[i] = x_pows[i - 1] * x_;
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
  HString string(input.length(), input.data());
  int queries_number = 0;
  std::cin >> queries_number;

  for (int i = 0; i < queries_number; ++i) {
    int len = 0;
    int from_1 = 0;
    int from_2 = 0;
    std::cin >> len >> from_1 >> from_2;
    std::string str1(input, from_1, len);
    std::string str2(input, from_2, len);
    std::cout << len << ' ' << from_1 << ' ' << from_2 << '\n' << str2 << "\n" << str2 << "\n: ";
    if (string.PartsEquality(len, from_1, from_2) == true) {
      std::cout << "yes\n\n";
    } else {
      std::cout << "no\n\n";
    }
  }

  return 0;
}
