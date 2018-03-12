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
#include <string>

using namespace std;

int ThreeFiveMultiples_v1(const int num) {
  if (num < 3)
    return 0;

  int sum{3};

  for (int i{5}; i < num; i++) {
    if (i % 3 == 0 || i % 5 == 0)
      sum += i;
  }

  return sum;
}

int ThreeFiveMultiples_v2(const int num) {
  if (num < 3)
    return 0;

  int sum{3};
  int current_num1{5};
  int current_num2{6};

  bool is_first_cond_true{current_num1 < num};
  bool is_second_cond_true{current_num2 < num};

  while (is_first_cond_true || is_second_cond_true) {
    if (is_first_cond_true)
      sum += current_num1;
    current_num1 += 5;

    if (is_second_cond_true)
      sum += current_num2;
    current_num2 += 3;

    is_first_cond_true = current_num1 < num;
    is_second_cond_true = current_num2 < num;
  }

  return sum;
}

int main() {
  // cout << ThreeFiveMultiples_v2(gets(stdin));
  cout << ThreeFiveMultiples_v2(10) << '\n';  // expected output: 23
  cout << ThreeFiveMultiples_v2(6) << '\n';   // expected output: 8
  cout << ThreeFiveMultiples_v2(1) << '\n';   // expected output: 0
  return 0;
}
