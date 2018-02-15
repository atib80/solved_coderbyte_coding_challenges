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

string PowersofTwo(int num) {
  if (!num)
    return "false";

  const bool is_number_negative{num < 0};

  const int factor{is_number_negative ? -2 : 2};

  while (num) {
    if (1 == num)
      return "true";

    if (abs(num) % 2 == 1)
      return "false";

    num /= factor;
  }

  return "true";
}

string PowersofTwo_v2(const int target_num) {
  if (!target_num)
    return "false";

  const bool is_number_negative{target_num < 0};
  const int mult_factor{is_number_negative ? -1 : 1};

  int search_num{1};

  while (true) {
    if (target_num == search_num)
      return "true";

    search_num <<= 1;

    search_num *= mult_factor;

    if (is_number_negative) {
      if (search_num < target_num)
        return "false";
    } else if (search_num > target_num)
      return "false";
  }
}

int main() {
  // cout << PowersofTwo_v2(gets(stdin));
  cout << PowersofTwo_v2(16) << '\n';   // expected output: "true"
  cout << PowersofTwo_v2(22) << '\n';   // expected output: "false"
  cout << PowersofTwo_v2(4) << '\n';    // expected output: "true"
  cout << PowersofTwo_v2(124) << '\n';  // expected output: "false"
  cout << PowersofTwo_v2(-8) << '\n';   // expected output: "true"
  cout << PowersofTwo_v2(16) << '\n';   // expected output: "true"
  cout << PowersofTwo_v2(-32) << '\n';  // expected output: "true"

  return 0;
}
