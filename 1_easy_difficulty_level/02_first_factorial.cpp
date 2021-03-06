/*
Coderbyte coding challenge: First Factorial

Using the C++ language, have the function FirstFactorial(num) take the num
parameter being passed and return the factorial of it (e.g. if num = 4, return
(4 * 3 * 2 * 1)). For the test cases, the range will be between 1 and 18 and the
input will always be an integer.

Sample test cases:

Input:  4
Output: 24

Input:  8
Output: 40320
*/

#include <cctype>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "../include/stl_helper_functions.hpp"

using namespace std;

template <size_t N = 20>
struct precalculated_factorials {
  uint64_t factorials[N + 1];

  constexpr precalculated_factorials() : factorials{} {
    factorials[0] = factorials[1] = 1;

    for (size_t i{2}; i <= N; ++i)
      factorials[i] = calculate_factorial(i);
  }

  constexpr uint64_t calculate_factorial(uint64_t n) const {
    if (n <= 2U)
      return 0U == n ? 1U : n;

    uint64_t result{n};

    while (--n > 1)
      result *= n;

    return result;
  }

  constexpr uint64_t get_factorial_of_specified_number(const uint64_t n) const {
    if (n <= N)
      return factorials[n];
    return calculate_factorial(n);
  }
};

static constexpr precalculated_factorials<> factorials;

uint64_t FirstFactorial_v1(uint64_t num) {
  if (num <= 2ULL)
    return 0ULL == num ? 1ULL : num;

  uint64_t result{num};

  while (num > 2ULL)
    result *= --num;

  return result;
}

uint64_t FirstFactorial_v2(const uint64_t num) {
  if (num < 2ULL)
    return 1ULL;

  return num * FirstFactorial_v2(num - 1);
}

uint64_t FirstFactorial_v3(const uint64_t num) {
  if (num <= 20ULL)
    return factorials.get_factorial_of_specified_number(num);
  return FirstFactorial_v1(num);
}

int main() {
  // cout << FirstFactorial_v1(gets(stdin));
  cout << FirstFactorial_v1(0) << '\n';   // expected output: 1
  cout << FirstFactorial_v1(1) << '\n';   // expected output: 1
  cout << FirstFactorial_v1(2) << '\n';   // expected output: 2
  cout << FirstFactorial_v1(3) << '\n';   // expected output: 6
  cout << FirstFactorial_v1(4) << '\n';   // expected output: 24
  cout << FirstFactorial_v1(5) << '\n';   // expected output: 120
  cout << FirstFactorial_v1(6) << '\n';   // expected output: 720
  cout << FirstFactorial_v1(7) << '\n';   // expected output: 5040
  cout << FirstFactorial_v1(8) << '\n';   // expected output: 40320
  cout << FirstFactorial_v1(9) << '\n';   // expected output: 362880
  cout << FirstFactorial_v1(10) << '\n';  // expected output: 3628800
  cout << FirstFactorial_v1(11) << '\n';  // expected output: 39916800
  cout << FirstFactorial_v1(12) << '\n';  // expected output: 479001600
  cout << FirstFactorial_v1(13) << '\n';  // expected output: 6227020800
  cout << FirstFactorial_v1(14) << '\n';  // expected output: 87178291200
  cout << FirstFactorial_v1(15) << '\n';  // expected output: 1307674368000
  cout << FirstFactorial_v1(16) << '\n';  // expected output: 20922789888000
  cout << FirstFactorial_v1(17) << '\n';  // expected output: 355687428096000
  cout << FirstFactorial_v1(18) << '\n';  // expected output: 6402373705728000
  cout << FirstFactorial_v1(19) << '\n';  // expected output: 121645100408832000
  cout << FirstFactorial_v1(20)
       << '\n';  // expected output: 2432902008176640000

  return 0;
}
