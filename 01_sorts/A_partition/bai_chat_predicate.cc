#include <algorithm>
#include <iostream>
#include <vector>

// Пример функции, принимающей предикат в качестве параметра
void processWithPredicate(const std::vector<int>& data,
                          bool (*predicate)(int)) {
  for (int num : data) {
    if (predicate(num)) {
      std::cout << num << " ";
    }
  }
  std::cout << std::endl;
}

// Пример предиката
bool isEven(int num) { return num % 2 == 0; }

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Передаем предикат в качестве параметра
  std::cout << "Четные числа: ";
  processWithPredicate(numbers, &isEven);

  // Можно также воспользоваться лямбда-выражением в качестве предиката
  std::cout << "Нечетные числа: ";
  processWithPredicate(numbers, [](int num) { return num % 2 != 0; });

  return 0;
}
