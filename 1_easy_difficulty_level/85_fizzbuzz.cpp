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

#include <iostream>
#include <sstream>

using namespace std;

string FizzBuzz(const int num) {
  if (num < 1)
    return {};

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

int main() {
  // cout << FizzBuzz(gets(stdin));
  cout << FizzBuzz(16) << '\n';  // expected output: "1 2 Fizz 4 Buzz Fizz 7 8
                                 // Fizz Buzz 11 Fizz 13 14 FizzBuzz 16"
  cout << FizzBuzz(3) << '\n';   // expected output: "1 2 Fizz"
  cout << FizzBuzz(8) << '\n';   // expected output: "1 2 Fizz 4 Buzz Fizz 7 8"

  return 0;
}
