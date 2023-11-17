#include <iostream>

int main() {
  size_t lift_capacity = 0;
  size_t floors_number = 0;
  std::cin >> lift_capacity;
  std::cin >> floors_number;

  size_t* humans_on_floor = new size_t[floors_number + 1]{};
  for (int i = 1; i <= floors_number; ++i) {
    std::cin >> humans_on_floor[i];
  }

  size_t time = 0;
  for (size_t i = floors_number; i > 0; --i) {
    size_t full_rise_up = humans_on_floor[i] / lift_capacity;
    if (humans_on_floor[i] % lift_capacity > 0) ++full_rise_up;
    time +=
        /*количество полных подъёмов на этаж*/
        full_rise_up * i +
        /*количество полных спусков с этажа*/
        humans_on_floor[i] / lift_capacity * i;

    if (humans_on_floor[i] % lift_capacity > 0) {
      // снизились на один этаж и убираем один полный подъём на него
      humans_on_floor[i - 1] += humans_on_floor[i] % lift_capacity;
      time += 1 - (i - 1);
    }
  }

  std::cout << time;

  delete[] humans_on_floor;

  return 0;
}
