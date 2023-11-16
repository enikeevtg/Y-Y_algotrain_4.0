#include <iostream>

int main() {
  int a, b, c, d;
  std::cin >> a >> b >> c >> d;

  int numerator = a * d + b * c;
  int denominator = b * d;

  int i = 2;
  while (i <= numerator && i <= denominator) {
    while (numerator % i == 0 && denominator % i == 0) {
      numerator /= i;
      denominator /= i;
    }
    ++i;
  }

  std::cout << numerator << ' ' << denominator << std::endl;

  return 0;
}
