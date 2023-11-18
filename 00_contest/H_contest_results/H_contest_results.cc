#include <iostream>

int main() {
  int solved_first_group = 0;
  int solved_second_group = 0;
  int tasks_number = 0;
  std::cin >> solved_first_group >> solved_second_group >> tasks_number;

  int max_first_group = solved_first_group;
  int min_second_group = solved_second_group / tasks_number;
  if (solved_second_group % tasks_number > 0) ++min_second_group;
  if (max_first_group > min_second_group) {
    std::cout << "Yes";
  } else {
    std::cout << "No";
  }

  return 0;
}
