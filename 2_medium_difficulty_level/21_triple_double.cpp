/*
Coderbyte coding challenge: Triple Double

Using the C++ language, have the function TripleDouble(num1,num2) take both
parameters being passed, and return 1 if there is a straight triple of a number
at any place in num1 and also a straight double of the same number in num2. For
example: if num1 equals 451999277 and num2 equals 41177722899, then return 1
because in the first parameter you have the straight triple 999 and you have a
straight double, 99, of the same number in the second parameter. If this isn't
the case, return 0.

Sample test cases:
Input:  465555 & num2 = 5579
Output: 1

Input:  67844 & num2 = 66237
Output: 0
*/

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

int TripleDouble_v1(int64_t num1, int64_t num2) {
  const string num1_str{to_string(num1)};
  const string num2_str{to_string(num2)};

  for (char digit{'0'}; digit <= '9'; digit++) {
    if ((end(num1_str) != search_n(begin(num1_str), end(num1_str), 3, digit)) &&
        (end(num2_str) != search_n(begin(num2_str), end(num2_str), 2, digit)))
      return 1;
  }

  return 0;
}

int TripleDouble_v2(int64_t num1, int64_t num2) {
  const string num1_str{to_string(num1)};
  const string num2_str{to_string(num2)};

  map<char, size_t> digit_count{};

  for (const char digit : num1_str)
    digit_count[digit]++;

  for (const pair<char, size_t>& digit_freq : digit_count) {
    if (digit_freq.second < 3)
      continue;

    if (end(num2_str) !=
        search_n(begin(num2_str), end(num2_str), 2, digit_freq.first))
      return 1;
  }

  return 0;
}

int main() {
  // cout << TripleDouble_v2(gets(stdin));
  cout << TripleDouble_v2(451999277LL, 41177722899LL)
       << '\n';                                       // expected output: 1
  cout << TripleDouble_v2(465555LL, 5579LL) << '\n';  // expected output: 1
  cout << TripleDouble_v2(67844LL, 66237LL) << '\n';  // expected output: 0
  return 0;
}
