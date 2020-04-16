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

using namespace std;

constexpr int AdditivePersistence(int64_t num) {
  if (num < 0)
    num = -num;

  int iter_count{};

  while (num > 9) {
    iter_count++;
    int64_t sum{};

    while (0 != num) {
      sum += num % 10;
      num /= 10;
    }

    num = sum;
  }

  return iter_count;
}

int main() {
  // cout << AdditivePersistence(gets(stdin));
  cout << AdditivePersistence(2718) << '\n';  // expected output: 2
  cout << AdditivePersistence(4) << '\n';     // expected output: 0
  cout << AdditivePersistence(19) << '\n';    // expected output: 2

  return 0;
}
