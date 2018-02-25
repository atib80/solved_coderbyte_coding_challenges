/*
Coderbyte coding challenge: One Decremented

Using the C++ language, have the function OneDecremented(num) count how many
times a digit appears that is exactly one less than the previous digit. For
example: if num is 5655984 then your program should return 2 because 5 appears
directly after 6 and 8 appears directly after 9. The input will always contain
at least 1 digit.

Sample test cases:

Input:  56
Output: 0

Input:  9876541110
Output: 6
*/

#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

size_t OneDecremented(const int64_t num) {
  const string num_str{to_string(num)};

  if (num_str.length() < 2)
    return 0;

  size_t freq{};

  for (size_t i{}; i < num_str.length() - 1; i++) {
    if (1 == static_cast<int>(num_str[i] - num_str[i + 1]))
      freq++;
  }

  return freq;
}

int main() {
  // cout << OneDecremented(gets(stdin));
  cout << OneDecremented(5655984LL) << '\n';     // expected output: 2
  cout << OneDecremented(56LL) << '\n';          // expected output: 0
  cout << OneDecremented(9876541110LL) << '\n';  // expected output: 6

  return 0;
}
