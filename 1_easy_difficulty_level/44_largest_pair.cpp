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
#include <queue>
#include <set>
#include <string>

using namespace std;

int64_t LargestPair_v1(int64_t num) {
  num = abs(num);

  string num_str{to_string(num)};

  priority_queue<int> two_digit_numbers{};

  for (size_t i{}; i < num_str.length() - 1; ++i) {
    two_digit_numbers.push((num_str[i] - '0') * 10 + (num_str[i + 1] - '0'));
  }

  return two_digit_numbers.top();
}

int LargestPair_v2(int64_t num) {
  num = abs(num);
  int current_max_num{};

  while (num > 9) {
    int current_num = num % 100;
    num /= 10;
    if (current_num > current_max_num)
      current_max_num = current_num;
  }

  return current_max_num;
}

int LargestPair_v3(int64_t num) {
  num = abs(num);
  string num_str{to_string(num)};
  int current_max_num{};

  for (size_t i{}; i < num_str.length() - 1; ++i) {
    const int current_num{(num_str[i] - '0') * 10 + (num_str[i + 1] - '0')};
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
