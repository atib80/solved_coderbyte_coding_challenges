/*
Coderbyte coding challenge: ThreeFive Multiples

Using the C++ language, have the function ThreeFiveMultiples(num) return the sum
of all the multiples of 3 and 5 that are below num. For example: if num is 10,
the multiples of 3 and 5 that are below 10 are 3, 5, 6, and 9, and adding them
up you get 23, so your program should return 23. The integer being passed will
be between 1 and 100.

Sample test cases:

Input:  6
Output: 8

Input:  1
Output: 0
*/

#include <iostream>

using namespace std;

int ThreeFiveMultiples(const int num) {

  int sum{};

  for (int i{3}; i < num; i++) {
    if (i % 3 == 0 || i % 5 == 0)
      sum += i;
  }

  return sum;
}

int main() {
  // cout << ThreeFiveMultiples(gets(stdin));
  cout << ThreeFiveMultiples(10) << '\n';  // expected output: 23
  cout << ThreeFiveMultiples(6) << '\n';   // expected output: 8
  cout << ThreeFiveMultiples(1) << '\n';   // expected output: 0
  cout << ThreeFiveMultiples(3) << '\n';   // expected output: 0
  cout << ThreeFiveMultiples(31) << '\n';  // expected output: 225
  cout << ThreeFiveMultiples(17) << '\n';  // expected output: 60
  cout << ThreeFiveMultiples(4) << '\n';   // expected output: 3
  return 0;
}
