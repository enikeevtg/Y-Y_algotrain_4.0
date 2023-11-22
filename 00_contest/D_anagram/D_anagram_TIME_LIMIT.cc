#include <iostream>

const int letters_number = 26;

class String {
 public:
  String(){};
  String(const char* string) {
    while (string[size_] != '\0') ++size_;
    AllocAndFillString(string);
  }
  String(const String& other) : size_(other.size_) {
    AllocAndFillString(other.string_);
  }
  ~String() { delete[] string_; }

  bool IsAnagram(const char* string) {
    String tmp(*this);
    int i = 0;
    while (string[i] != '\0') {
      if (string[i] != ' ') {
        int j = 0;
        while (tmp.string_[j] != '\0' && tmp.string_[j] != string[i]) ++j;
        if (tmp.string_[j] == '\0') {
          return false;
        } else {
          tmp.string_[j] = '-';
        }
      }
      ++i;
    }

    for (int k = 0; k < tmp.size_; ++k) {
      if (tmp.string_[k] != '-') return false;
    }
    return true;
  }

 private:
  void AllocAndFillString(const char* string) {
    string_ = new char[size_]{};
    for (int i = 0; i <= size_; ++i) {
      string_[i] = string[i];
    }
  }

  size_t size_{0};
  char* string_{nullptr};
};

int main() {
  char input_str_1[100001];
  char input_str_2[100001];
  std::cin >> input_str_1;
  std::cin >> input_str_2;

  String str(input_str_1);
  bool is_anagram = str.IsAnagram(input_str_2);
  if (is_anagram == true) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}
