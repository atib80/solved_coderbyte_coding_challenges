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

size_t ProductDigits(const size_t num) {
  string result{"1" + to_string(num)};
  size_t current_min_len{result.length()};

  for (size_t i{2}; i < static_cast<size_t>(sqrt(num)) + 1; i++) {
    const size_t factor{num / i};

    if (num == i * factor) {
      result = to_string(i) + to_string(factor);
      if (result.length() < current_min_len)
        current_min_len = result.length();
    }
  }

  return current_min_len;
}

int main() {
  // cout << ProductDigits(gets(stdin));
  cout << ProductDigits(24) << '\n';  // expected output: 2
  cout << ProductDigits(90) << '\n';  // expected output: 3
  cout << ProductDigits(6) << '\n';   // expected output: 2
  cout << ProductDigits(23) << '\n';  // expected output: 3
  cout << ProductDigits(1) << '\n';   // expected output: 2
  cout << ProductDigits(79) << '\n';  // expected output: 3

  return 0;
}
