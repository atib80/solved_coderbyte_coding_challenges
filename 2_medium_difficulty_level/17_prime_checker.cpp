/*
Coderbyte coding challenge: Prime Checker

Using the C++ language, have the function PrimeChecker(num) take num and return
1 if any arrangement of num comes out to be a prime number, otherwise return 0.
For example: if num is 910, the output should be 1 because 910 can be arranged
into 109 or 019, both of which are primes.

Sample test cases:

Input:  98
Output: 1

Input:  598
Output: 1
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_prime_number(long n) {
  if (2 == n || 3 == n || 5 == n)
    return true;

  if (n < 2 || n % 2 == 0 || n % 5 == 0)
    return false;

  const long upper_limit = static_cast<long>(sqrt(static_cast<double>(n)) + 1);

  vector<long> divisor_factors{3, 7, 9, 11};
  long k{3};
  size_t index{1};

  while (k <= upper_limit) {
    if (n % k == 0)
      return false;

    k = divisor_factors[index++];

    if (index > 3) {
      index = 0;

      for (auto& factor : divisor_factors)
        factor += 10;
    }
  }

  return true;
}

long PrimeChecker(long number) {
  string number_str{to_string(number)};

  if (1 == number_str.length()) {
    if (!is_prime_number(number))
      return 0;
    return 1;
  }

  const char first_digit{number_str.front()};

  if (all_of(begin(number_str), end(number_str),
             [&first_digit](const char d) { return d == first_digit; })) {
    return is_prime_number(number) ? 1 : 0;
  }

  sort(begin(number_str), end(number_str));

  do {
    long next_num{stol(number_str)};
    if (is_prime_number(next_num))
      return 1;
  } while (next_permutation(begin(number_str), end(number_str)));

  return 0;
}

int main() {
  // cout << PrimeChecker(gets(stdin));
  cout << PrimeChecker(910) << '\n';  // expected output: 1
  cout << PrimeChecker(9) << '\n';    // expected output: 0
  cout << PrimeChecker(44) << '\n';   // expected output: 0
  cout << PrimeChecker(100) << '\n';  // expected output: 0
  cout << PrimeChecker(104) << '\n';  // expected output: 1
  cout << PrimeChecker(908) << '\n';  // expected output: 1

  return 0;
}
