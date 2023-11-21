#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v;
  int size = 0;
  std::cin >> size;
  for (int i = 0; i < size; ++i) {
    int tmp = 0;
    std::cin >> tmp;
    v.push_back(tmp);
  }
  std::sort(v.begin(), v.end());

  int cols = 0;
  for (int i = 0; i < size; ++i) {
    std::cout << v[i] << ' ';
    ++cols;
    if (cols == 5) {
      std::cout << '\n';
      cols = 0;
    }
  }

  return 0;
}
