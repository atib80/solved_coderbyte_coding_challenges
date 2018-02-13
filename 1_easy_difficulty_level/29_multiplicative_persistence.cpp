/*
Coderbyte coding challenge: Multiplicative Persistence

Using the C++ language, have the function MultiplicativePersistence(num) take
the num parameter being passed which will always be a positive integer and
return its multiplicative persistence which is the number of times you must
multiply the digits in num until you reach a single digit. For example: if num
is 39 then your program should return 3 because 3 * 9 = 27 then 2 * 7 = 14 and
finally 1 * 4 = 4 and you stop at 4.

Sample test cases:

Input:  4
Output: 0

Input:  25
Output: 2
*/

#include <iostream>
#include <string>

using namespace std;

int MultiplicativePersistence(int num) {
  size_t iter{};

  while (num > 9) {
    iter++;

    const string num_str{to_string(num)};

    num = 1;

    for (const char digit : num_str)
      num *= static_cast<int>(digit - '0');
  }

  return iter;
}

int main() {
  // cout << MultiplicativePersistence(gets(stdin));
  cout << MultiplicativePersistence(39) << '\n';  // expected output: 3
  cout << MultiplicativePersistence(4) << '\n';   // expected output: 0
  cout << MultiplicativePersistence(25) << '\n';  // expected output: 2

  return 0;
}
