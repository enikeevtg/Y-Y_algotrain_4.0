#include <iostream>

const int letters_number = 26;

int main() {
  char str_1[100001];
  char str_2[100001];
  std::cin >> str_1;
  std::cin >> str_2;

  int letters_count_1[letters_number]{};
  int letters_count_2[letters_number]{};
  
  int i = 0;
  while (str_1[i] != '\0' && str_2[i] != '\0') {
    letters_count_1[(int)str_1[i] - 97] += 1;
    letters_count_2[(int)str_2[i] - 97] += 1;
    ++i;
  }

  bool is_anagram = true;
  if (str_1[i] != '\0' || str_2[i] != '\0') {
    is_anagram = false;
  }
  for (int k = 0; is_anagram != false && k < letters_number; ++k) {
    if (letters_count_1[k] != letters_count_2[k]) is_anagram = false;
  }

  if (is_anagram == true) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}
