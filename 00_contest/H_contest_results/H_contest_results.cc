#include <iostream>

int main() {
  int solved_group_1 = 0;
  int solved_group_2 = 0;
  int tasks_number = 0;
  std::cin >> solved_group_1 >> solved_group_2 >> tasks_number;

  int group_1_max = solved_group_1;

  // деление с округлением вверх 1:
  // int group_2_min = (solved_group_2 + tasks_number - 1) /
  // tasks_number; if (solved_group_2 % tasks_number > 0)
  // ++group_2_min;
  // деление с округлением вверх 2:
  int group_2_min = (solved_group_2 + tasks_number - 1) / tasks_number;

  if (group_1_max > group_2_min) {
    std::cout << "Yes";
  } else {
    std::cout << "No";
  }

  return 0;
}
