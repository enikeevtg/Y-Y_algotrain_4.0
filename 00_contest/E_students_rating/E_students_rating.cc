#include <iostream>

int main() {
  int n = 1;
  std::cin >> n;

  int* ratings = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> ratings[i];
  }

  int* ratings_sum = new int[n]{};
  ratings_sum[0] = ratings[0];
  for (int i = 1; i < n; ++i) {
    ratings_sum[i] = ratings_sum[i - 1] + ratings[i];
  }

  for (int i = 0; i < n; ++i) {
    int pivot = ratings[i];
    int result = (pivot * (i + 1) - ratings_sum[i]) +
                 (ratings_sum[n - 1] - ratings_sum[i] - pivot * (n - i - 1));
    std::cout << result << ' ';
  }

  delete[] ratings;
  delete[] ratings_sum;

  return 0;
}
