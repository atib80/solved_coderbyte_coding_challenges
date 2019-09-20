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

using namespace std;

constexpr int MultiplicativePersistence(int64_t num) {
  if (num < 0)
    num = -num;

  int iter_count{};

  while (num > 9) {
    iter_count++;
    int64_t product{1};

    while (0 != num) {
      product *= num % 10;
      num /= 10;
    }

    num = product;
  }

  return iter_count;
}

int main() {
  // cout << MultiplicativePersistence(gets(stdin));
  cout << MultiplicativePersistence(39) << '\n';  // expected output: 3
  cout << MultiplicativePersistence(4) << '\n';   // expected output: 0
  cout << MultiplicativePersistence(25) << '\n';  // expected output: 2

  return 0;
}
