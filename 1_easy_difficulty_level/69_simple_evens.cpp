/*
Coderbyte coding challenge: Simple Evens

Using the C++ language, have the function SimpleEvens(num) check whether every
single number in the passed in parameter is even. If so, return the string true,
otherwise return the string false. For example: if num is 4602225 your program
should return the string false because 5 is not an even number.

Sample test cases:

Input:  2222220222
Output: "true"

Input:  20864646452
Output: "false"
*/

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

string SimpleEvens_v1(const int64_t num) {
  const string num_str{to_string(num)};

  for (const char ch : num_str) {
    if (ch % 2 == 1)
      return "false";  // or if ((ch - '0') % 2 == 1) return "false";
  }

  return "true";
}

string SimpleEvens_v2(const int64_t num) {
  const string num_str{to_string(num)};

  return (all_of(begin(num_str), end(num_str),
                 [](const char ch) { return ch % 2 == 0; })
              ? "true"
              : "false");
}

int main() {
  // cout << SimpleEvens_v2(gets(stdin));
  cout << SimpleEvens_v2(4602225LL) << '\n';      // expected output: "false"
  cout << SimpleEvens_v2(2222220222LL) << '\n';   // expected output: "true"
  cout << SimpleEvens_v2(20864646452LL) << '\n';  // expected output: "false"

  return 0;
}
