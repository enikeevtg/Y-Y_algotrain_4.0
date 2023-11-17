#include <iostream>

int main() {
  int n = 1;
  std::cin >> n;

  int* ratings = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> ratings[i];
  }

  for (int i = 0; i < n; ++i) {
    int pivot = ratings[i];
    int j = 0;
    
    int less = 0;
    while (ratings[j] < pivot) {
      less += ratings[j];
      ++j;
    }
    less = j * pivot - less;

    // while (ratings[j] < pivot) {
    //   less += pivot - ratings[j];
    //   ++j;
    // }

    while (ratings[j] == pivot) ++j;

    int greater = greater = -(n - j) * pivot;
    for (; j < n; ++j) {
      greater += ratings[j];
    }

    // int greater = 0;
    // for (; j < n; ++j) {
    //   greater += ratings[j] - pivot;
    // }

    int result = greater + less;
    std::cout << result << ' ';
  }

  delete[] ratings;
  return 0;
}
