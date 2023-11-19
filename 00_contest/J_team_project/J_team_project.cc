#include <iostream>

// v1 algorithm with while loop
void PrintPartitionPossibilityV1() {
  bool partition_possibility = false;
  int students_num = 0;
  int min = 0;
  int max = 0;
  std::cin >> students_num >> min >> max;

  int group_capacity = min;
  while (partition_possibility == false && group_capacity <= max) {
    if (students_num % group_capacity == 0) {
      partition_possibility = true;
    } else if (students_num / group_capacity >= students_num % group_capacity &&
               group_capacity + 1 <= max) {
      partition_possibility = true;
    } else {
      ++group_capacity;
    }
  }

  if (partition_possibility == true) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}

// simple algorithm
void PrintPartitionPossibility() {
  int students_num = 0;
  int min = 0;
  int max = 0;
  std::cin >> students_num >> min >> max;

  size_t groups_number = students_num / min;
  if (groups_number * (max - min) >= students_num % min) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}

int main() {
  int tests_number = 0;
  std::cin >> tests_number;

  for (int i = 0; i < tests_number; ++i) {
    PrintPartitionPossibility();
  }

  return 0;
}
