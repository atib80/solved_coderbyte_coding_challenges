/*
Coderbyte coding challenge: Ternary Converter

Using the C++ language, have the function TernaryConverter(num) take the num
parameter being passed, which will always be a positive integer, and convert it
into a ternary representation. For example: if num is 12 then your program
should return 110.

Sample test cases:

Input:  21
Output: 210

Input:  67
Output: 2111
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string TernaryConverter_v1(int num) {
  string result{};

  while (num) {
    result.insert(begin(result), static_cast<char>(num % 3 + '0'));

    num /= 3;
  }

  return result;
}

string TernaryConverter_v2(int num) {
  ostringstream oss{};

  while (num) {
    oss << static_cast<char>(num % 3 + '0');

    num /= 3;
  }

  string result{oss.str()};

  reverse(begin(result), end(result));

  return result;
}

int main() {
  // cout << TernaryConverter_v1(gets(stdin));
  cout << TernaryConverter_v1(12) << '\n';  // expected output: 110
  cout << TernaryConverter_v1(21) << '\n';  // expected output: 210
  cout << TernaryConverter_v1(67) << '\n';  // expected output: 2111

  return 0;
}
