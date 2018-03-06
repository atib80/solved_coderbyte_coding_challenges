/*
Coderbyte coding challenge: Product Digits

Using the C++ language, have the function ProductDigits(num) take the num
parameter being passed which will be a positive integer, and determine the least
amount of digits you need to multiply to produce it. For example: if num is 24
then you can multiply 8 by 3 which produces 24, so your program should return 2
because there is a total of only 2 digits that are needed. Another example: if
num is 90, you can multiply 10 * 9, so in this case your program should output 3
because you cannot reach 90 without using a total of 3 digits in your
multiplication.

Sample test cases:

Input:  6
Output: 2

Input:  23
Output: 3
*/

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

size_t get_number_length(size_t number) {
  size_t len{};

  while (number) {
    number /= 10;
    len++;
  }

  return len;
}

size_t ProductDigits_v1(const size_t num) {
  string result{"1" + to_string(num)};
  size_t min_len{result.length()};

  for (size_t i{2}; i < static_cast<size_t>(sqrt(num)) + 1; i++) {
    const size_t factor{num / i};

    if (num == i * factor) {
      result = to_string(i) + to_string(factor);
      if (result.length() < min_len)
        min_len = result.length();
    }
  }

  return min_len;
}

size_t ProductDigits_v2(const size_t num) {
  size_t min_len{1 + get_number_length(num)};

  for (size_t i{2}; i < static_cast<size_t>(sqrt(num)) + 1; i++) {
    const size_t factor{num / i};

    if (num == i * factor) {
      const size_t current_len{get_number_length(i) +
                               get_number_length(factor)};
      if (current_len < min_len)
        min_len = current_len;
    }
  }

  return min_len;
}

int main() {
  // cout << ProductDigits_v2(gets(stdin));
  cout << ProductDigits_v2(24) << '\n';  // expected output: 2
  cout << ProductDigits_v2(90) << '\n';  // expected output: 3
  cout << ProductDigits_v2(6) << '\n';   // expected output: 2
  cout << ProductDigits_v2(23) << '\n';  // expected output: 3
  cout << ProductDigits_v2(1) << '\n';   // expected output: 2
  cout << ProductDigits_v2(79) << '\n';  // expected output: 3

  return 0;
}
