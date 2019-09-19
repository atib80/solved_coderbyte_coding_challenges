/*
Coderbyte coding challenge: Powers Of Two

Using the C++ language, have the function PowersofTwo(num) take the num
parameter being passed which will be an integer and return the string true if
it's a power of two. If it's not return the string false. For example if the
input is 16 then your program should return the string true but if the input is
22 then the output should be the string false.

Sample test cases:

Input:  4
Output: "true"

Input:  124
Output: "false"
*/

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

string PowersofTwo_v1(int64_t target_num) {
  if (target_num < 1)
    return "false";

  while (target_num > 1) {
    if (1 == target_num % 2)
      return "false";

    target_num /= 2;
  }

  return "true";
}

string PowersofTwo_v2(const int64_t target_num) {
  if (target_num < 1)
    return "false";

  int64_t num{1};

  while (num <= target_num) {
    if (target_num == num)
      return "true";

    num <<= 1;
  }

  return "false";
}

int main() {
  // cout << PowersofTwo_v2(gets(stdin));
  cout << PowersofTwo_v2(16) << '\n';   // expected output: "true"
  cout << PowersofTwo_v2(22) << '\n';   // expected output: "false"
  cout << PowersofTwo_v2(4) << '\n';    // expected output: "true"
  cout << PowersofTwo_v2(124) << '\n';  // expected output: "false"
  cout << PowersofTwo_v2(16) << '\n';   // expected output: "true"

  return 0;
}
