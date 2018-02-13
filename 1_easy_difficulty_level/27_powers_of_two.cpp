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

#include <iostream>
#include <string>

using namespace std;

string PowersofTwo(int num) {
  if (num < 1)
    return "false";

  while (num) {
    if (1 == num)
      return "true";

    if (num % 2 == 1)
      return "false";

    num /= 2;
  }

  return "true";
}

string PowersofTwo_v2(const int target_num) {
  if (target_num < 1)
    return "false";

  int search_num{1};

  while (true) {
    if (target_num == search_num)
      return "true";

    search_num <<= 1;

    if (search_num > target_num)
      return "false";
  }
}

int main() {
  // cout << PowersofTwo(gets(stdin));
  cout << PowersofTwo_v2(16) << '\n';   // expected output: "true"
  cout << PowersofTwo_v2(22) << '\n';   // expected output: "false"
  cout << PowersofTwo_v2(4) << '\n';    // expected output: "true"
  cout << PowersofTwo_v2(124) << '\n';  // expected output: "false"

  return 0;
}
