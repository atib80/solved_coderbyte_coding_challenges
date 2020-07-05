/*

85. Coderbyte coding challenge: FizzBuzz (difficulty level: easy)

Using the C++ language, have the function FizzBuzz(num) take the num parameter
being passed and return all the numbers from 1 to num inclusive, separated by
spaces, but replace every number that is divisible by 3 with the word "Fizz",
replace every number that is divisible by 5 with the word "Buzz", and every
number that is divisible by both 3 and 5 with the word "FizzBuzz". For example:
if num is 16, then your program should return the string "1 2 Fizz 4 Buzz Fizz 7
8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16". The input will be within the range 1
- 50.

Sample test cases:

Input:  3
Output: "1 2 Fizz"

Input:  8
Output: "1 2 Fizz 4 Buzz Fizz 7 8"
*/

#include <array>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

// ***** beginning of 1st solution *****
string FizzBuzz_v1(const int num) {
  ostringstream oss{};
  oss << "1";
  for (int i{2}; i <= num; ++i) {
    if (i % 3 == 0 && i % 5 == 0)
      oss << " FizzBuzz";
    else if (i % 3 == 0)
      oss << " Fizz";
    else if (i % 5 == 0)
      oss << " Buzz";
    else
      oss << ' ' << i;
  }

  return oss.str();
}
// ***** end of 1st solution *****

// ***** beginning of 2nd solution *****
string FizzBuzz_v2(const int number) {
  ostringstream oss{};
  oss << "1";

  for (int i{2}; i <= number; ++i) {
    const bool divisible_by_3{0 == i % 3};
    const bool divisible_by_5{0 == i % 5};
    if (divisible_by_3) {
      oss << (divisible_by_5 ? " FizzBuzz" : " Fizz");
    } else if (divisible_by_5)
      oss << " Buzz";
    else
      oss << ' ' << i;
  }

  return oss.str();
}
// ***** end of 2nd solution *****

// ***** beginning of 3rd solution *****
string FizzBuzz_v3(const int number) {
  constexpr const array<const char*, 16> fizz_buzz_dict{
      {nullptr, nullptr, nullptr, "Fizz", nullptr, "Buzz", nullptr, nullptr,
       nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       "FizzBuzz"}};

  ostringstream oss{};
  oss << "1";

  for (int i{2}; i <= number; ++i) {
    oss << ' '
        << (i % 15 == 0 ? fizz_buzz_dict.at(15)
                        : (i % 5 == 0 ? fizz_buzz_dict.at(5)
                                      : (i % 3 == 0 ? fizz_buzz_dict.at(3)
                                                    : itoa(i, nullptr, 10))));
  }

  return oss.str();
}
// ***** end of 3rd solution *****

// ***** beginning of 4th solution *****
using process_correct_case_fn = ostream& (*)(ostream&, const int);

inline ostream& get_number(ostream& os, const int number) {
  return os << number;
}

inline ostream& get_fizz(ostream& os, const int) {
  return os << "Fizz";
}

inline ostream& get_buzz(ostream& os, const int) {
  return os << "Buzz";
}

inline ostream& get_fizz_buzz(ostream& os, const int) {
  return os << "FizzBuzz";
}

string FizzBuzz_v4(const int number) {
  constexpr const process_correct_case_fn fizz_buzz_funcs[9]{
      get_number, nullptr, nullptr, get_fizz,     nullptr,
      get_buzz,   nullptr, nullptr, get_fizz_buzz};

  ostringstream oss{};
  oss << "1";

  for (int i{2}; i <= number; ++i) {
    const int index{(i % 3 == 0) * 3 + (i % 5 == 0) * 5};
    oss << ' ';
    fizz_buzz_funcs[index](oss, i);
  }

  return oss.str();
}
// ***** end of 4th solution *****

int main() {
  // cout << FizzBuzz_v4(gets(stdin));
  cout << FizzBuzz_v4(16) << '\n';  // expected output: "1 2 Fizz 4 Buzz Fizz 7
                                    // 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16"
  cout << FizzBuzz_v4(3) << '\n';   // expected output: "1 2 Fizz"
  cout << FizzBuzz_v4(8)
       << '\n';  // expected output: "1 2 Fizz 4 Buzz Fizz 7 8"

  return 0;
}
