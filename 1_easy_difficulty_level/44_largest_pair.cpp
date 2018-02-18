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

int LargestPair_v1(int num) {
  num = abs(num);

  string num_str{to_string(num)};

  set<int, greater<int>> two_digit_numbers{};

  for (size_t i{}; i < num_str.length() - 1; i++) {
    two_digit_numbers.insert(stoi(num_str.substr(i, 2)));
  }

  return (*begin(two_digit_numbers));
}

int LargestPair_v2(int num) {
  num = abs(num);
  int current_max_num{};

  while (num >= 10) {
    int current_num{num % 10};
    num /= 10;
    current_num += (num % 10) * 10;
    if (current_num > current_max_num)
      current_max_num = current_num;
  }

  return current_max_num;
}

int LargestPair_v3(int num) {
  num = abs(num);
  string num_str{to_string(num)};
  int current_max_num{};

  for (size_t i{}; i < num_str.length() - 1; i++) {
    const int current_num{static_cast<int>(num_str[i] - '0') * 10 +
                          static_cast<int>(num_str[i + 1] - '0')};
    if (current_num > current_max_num)
      current_max_num = current_num;
  }

  return current_max_num;
}

int main() {
  // cout << LargestPair_v1(gets(stdin));
  cout << LargestPair_v3(4759472) << '\n';    // expected output: 94
  cout << LargestPair_v3(453857) << '\n';     // expected output: 85
  cout << LargestPair_v3(363223311) << '\n';  // expected output: 63

  return 0;
}
