/*
Coderbyte coding challenge: Prime Mover

Using the C++ language, have the function PrimeMover(num) return the nth prime
number. The range will be from 1 to 10^4. For example: if num is 16 the output
should be 53 as 53 is the 16th prime number.

Sample test cases:

Input:  9
Output: 23

Input:  100
Output: 541
*/

#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

bool is_prime_number(const int64_t n) {
  if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0)
    return false;

  const int64_t upper_limit = static_cast<int>(sqrt(n)) + 1;

  for (int64_t i{7}; i < upper_limit; i += 2) {
    if (n % i == 0)
      return false;
  }

  return true;
}

int PrimeMover(int num) {
  num = abs(num);

  if (num == 1)
    return 2;
  if (num == 2)
    return 3;
  if (num == 3)
    return 5;
  if (num == 4)
    return 7;
  if (num == 5)
    return 11;

  int n{6};

  int current_prime_number{11};

  const int increment_factor[4] = {2, 4, 2, 2};

  size_t i{};

  while (n <= num) {
    do {
      current_prime_number += increment_factor[i];

      i++;

      if (4 == i)
        i = 0;

    } while (!is_prime_number(current_prime_number));

    n++;
  }

  return current_prime_number;
}

int main() {
  // cout << PrimeMover(gets(stdin));
  cout << PrimeMover(16) << '\n';   // expected output: 53
  cout << PrimeMover(9) << '\n';    // expected output: 23
  cout << PrimeMover(100) << '\n';  // expected output: 541
  return 0;
}
