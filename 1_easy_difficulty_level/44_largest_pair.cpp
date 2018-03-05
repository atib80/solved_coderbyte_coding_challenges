/*
Coderbyte coding challenge: Largest Pair

Using the C++ language, have the function LargestPair(num) take the num
parameter being passed and determine the largest double digit number within the
whole number. For example: if num is 4759472 then your program should return 94
because that is the largest double digit number. The input will always contain
at least two positive digits.

Sample test cases:

Input:  453857
Output: 85

Input:  363223311
Output: 63
*/

#include <functional>
#include <iostream>
#include <set>
#include <string>

using namespace std;

int64_t LargestPair_v1(int64_t num) {
  num = abs(num);

  string num_str{to_string(num)};

  set<int64_t, greater<int64_t>> two_digit_numbers{};

  for (size_t i{}; i < num_str.length() - 1; i++) {
    two_digit_numbers.insert(stoi(num_str.substr(i, 2)));
  }

  return (*begin(two_digit_numbers));
}

int64_t LargestPair_v2(int64_t num) {
  num = abs(num);
  int64_t current_max_num{};

  while (num >= 10) {
    int64_t current_num{num % 10};
    num /= 10;
    current_num += (num % 10) * 10;
    if (current_num > current_max_num)
      current_max_num = current_num;
  }

  return current_max_num;
}

int64_t LargestPair_v3(int64_t num) {
  num = abs(num);
  string num_str{to_string(num)};
  int64_t current_max_num{};

  for (size_t i{}; i < num_str.length() - 1; i++) {
    const int64_t current_num{static_cast<int64_t>(num_str[i] - '0') * 10 +
                              static_cast<int64_t>(num_str[i + 1] - '0')};
    if (current_num > current_max_num)
      current_max_num = current_num;
  }

  return current_max_num;
}

int main() {
  // cout << LargestPair_v2(gets(stdin));
  cout << LargestPair_v2(4759472) << '\n';     // expected output: 94
  cout << LargestPair_v2(453857) << '\n';      // expected output: 85
  cout << LargestPair_v2(363223311) << '\n';   // expected output: 63
  cout << LargestPair_v2(5673536634) << '\n';  // expected output: 73

  return 0;
}
