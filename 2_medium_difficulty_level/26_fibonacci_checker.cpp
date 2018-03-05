/*
Coderbyte coding challenge: Fibonacci Checker

Using the C++ language, have the function FibonacciChecker(num) return the
string yes if the number given is part of the Fibonacci sequence. This sequence
is defined by: Fn = Fn-1 + Fn-2, which means to find Fn you add the previous two
numbers up. The first two numbers are 0 and 1, then comes 1, 2, 3, 5 etc. If num
is not in the Fibonacci sequence, return the string no.

Sample test cases:

Input:  34
Output: "yes"

Input:  54
Output: "no"
*/

#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

uint64_t fibonacci(const uint64_t num) {
  if (num < 2ULL)
    return num;

  return (fibonacci(num - 1ULL) + fibonacci(num - 2ULL));
}

string FibonacciChecker(const uint64_t num) {
  if (num == 0ULL || num == 1ULL)
    return "yes";

  uint64_t a{}, b{1};

  while (true) {
    const uint64_t temp{a};
    a = b;
    b = temp + b;
    if (num == b)
      return "yes";
    if (num < b)
      break;
  }

  return "no";
}

int main() {
  // cout << FibonacciChecker(gets(stdin));
  cout << FibonacciChecker(34) << '\n';  // expected output: "yes"
  cout << FibonacciChecker(54) << '\n';  // expected output: "no"
  cout << FibonacciChecker(8) << '\n';   // expected output: "yes"
  cout << FibonacciChecker(17) << '\n';  // expected output: "no"
  cout << FibonacciChecker(21) << '\n';  // expected output: "yes"

  return 0;
}
