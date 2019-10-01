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

constexpr size_t get_number_length(size_t number) {
  size_t len{};

  while (0U != number) {
    number /= 10;
    ++len;
  }

  return len;
}

size_t ProductDigits_v1(const size_t num) {
  const size_t num_len{to_string(num).length()};
  size_t min_len{num_len + 1};

  for (size_t i{2U}; i < static_cast<size_t>(sqrt(num)) + 1; ++i) {
    if (num % i == 0U) {
      const size_t factor{num / i};
      const string result{to_string(i) + to_string(factor)};
      if (result.length() < min_len) {
        min_len = result.length();
        if (num_len == min_len)
          return min_len;
      } else if (result.length() > min_len)
        break;
    }
  }

  return min_len;
}

size_t ProductDigits_v2(const size_t num) {
  const size_t num_len{get_number_length(num)};
  size_t min_len{num_len + 1};

  for (size_t i{2U}; i < static_cast<size_t>(sqrt(num)) + 1; ++i) {
    if (num % i == 0U) {
      const size_t factor{num / i};
      const size_t current_len{get_number_length(i) +
                               get_number_length(factor)};
      if (current_len < min_len) {
        min_len = current_len;
        if (num_len == min_len)
          return min_len;
      } else if (current_len > min_len)
        break;
    }
  }

  return min_len;
}

int main() {
  // cout << ProductDigits_v2(gets(stdin));
  cout << ProductDigits_v2(24) << '\n';    // expected output: 2
  cout << ProductDigits_v2(90) << '\n';    // expected output: 3
  cout << ProductDigits_v2(6) << '\n';     // expected output: 2
  cout << ProductDigits_v2(23) << '\n';    // expected output: 3
  cout << ProductDigits_v2(1) << '\n';     // expected output: 2
  cout << ProductDigits_v2(79) << '\n';    // expected output: 3
  cout << ProductDigits_v2(1764) << '\n';  // expected output: 4
  cout << ProductDigits_v2(1024) << '\n';  // expected output: 4

  return 0;
}
