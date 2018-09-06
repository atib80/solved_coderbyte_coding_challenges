/*
Coderbyte coding challenge: Primes

Using the C++ language, have the function Primes(num) take the num parameter
being passed and return the string true if the parameter is a prime number,
otherwise return the string false. The range will be between 1 and 2^16.

Sample test cases:

Input:  4
Output: "false"

Input:  1709
Output: "true"
*/

#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

string Primes(int64_t num) {
  num = abs(num);

  if (2 == num || 3 == num || 5 == num)
    return "true";

  if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0)
    return "false";

  const int64_t highest_factor{static_cast<int64_t>(sqrt(num)) + 1};

  for (int64_t i{7}; i < highest_factor; i += 2) {
    if (num % i == 0)
      return "false";
  }

  return "true";
}

int main() {
  // cout << Primes(gets(stdin));
  cout << Primes(3) << '\n';    // expected output: "true"
  cout << Primes(4) << '\n';    // expected output: "false"
  cout << Primes(5) << '\n';    // expected output: "true"
  cout << Primes(7) << '\n';    // expected output: "true"
  cout << Primes(19) << '\n';   // expected output: "true"
  cout << Primes(110) << '\n';  // expected output: "false"
  cout << Primes(71) << '\n';   // expected output: "true"
  cout << Primes(1709) << '\n'; // expected output: "true"

  return 0;
}
