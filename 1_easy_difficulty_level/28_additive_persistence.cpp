/*
Coderbyte coding challenge: Additive Persistence

Using the C++ language, have the function AdditivePersistence(num) take the num
parameter being passed which will always be a positive integer and return its
additive persistence which is the number of times you must add the digits in num
until you reach a single digit. For example: if num is 2718 then your program
should return 2 because 2 + 7 + 1 + 8 = 18 and 1 + 8 = 9 and you stop at 9.

Sample test cases:

Input:  4
Output: 0

Input:  19
Output: 2
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int AdditivePersistence(int num) {
  num = abs(num);

  size_t iter{};

  while (num > 9) {
    iter++;

    const string num_str{to_string(num)};

    num = 0;

    for (const char digit : num_str)
      num += static_cast<int>(digit - '0');
  }

  return iter;
}

int main() {
  // cout << AdditivePersistence(gets(stdin));
  cout << AdditivePersistence(2718) << '\n';  // expected output: 2
  cout << AdditivePersistence(4) << '\n';     // expected output: 0
  cout << AdditivePersistence(19) << '\n';    // expected output: 2

  return 0;
}
