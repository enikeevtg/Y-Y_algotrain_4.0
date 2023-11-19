#include <iostream>

const int string_max_size = 100001;
const int empty_stack = -1;

int main() {
  char string[string_max_size]{};
  std::cin >> string;

  char stack[string_max_size / 2];
  int top = empty_stack;
  char brackets_check = true;

  char* ptr = string;
  while (brackets_check == true && *ptr != '\0' && top < string_max_size / 2) {
    if (*ptr == '(' || *ptr == '[' || *ptr == '{') {
      ++top;
      stack[top] = *ptr;
    } else if (*ptr == ')') {
      if (stack[top] == '(') {
        --top;
      } else {
        brackets_check = false;
      }
    } else if (*ptr == ']') {
      if (stack[top] == '[') {
        --top;
      } else {
        brackets_check = false;
      }
    } else if (*ptr == '}') {
      if (stack[top] == '{') {
        --top;
      } else {
        brackets_check = false;
      }
    }
    ++ptr;
  }

  if (top != empty_stack) brackets_check = false;

  if (brackets_check == true) {
    std::cout << "yes";
  } else {
    std::cout << "no";
  }

  return 0;
}
