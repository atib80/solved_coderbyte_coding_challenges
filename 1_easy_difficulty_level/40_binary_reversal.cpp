/*
Coderbyte coding challenge: Binary Reversal

Using the C++ language, have the function BinaryReversal(str) take the str
parameter being passed, which will be a positive integer, take its binary
representation, reverse that string of bits, and then finally return the new
reversed string in decimal form. For example: if str is "47" then the binary
version of this integer is 00101111. Your program should reverse this binary
string which then becomes: 11110100 and then finally return the decimal version
of this string, which is 244.

Sample test cases:

Input:  "213"
Output: "171"

Input:  "4567"
Output: "60296"
*/

#include <iostream>
#include <string>

using namespace std;

string BinaryReversal(string str) {
  int64_t number{stoll(str)};

  if (0 == number)
    return "0";

  int64_t reversed_number{};
  size_t digit_count{};

  while (0 != number) {
    reversed_number <<= 1;
    reversed_number |= number % 2;
    number >>= 1;
    ++digit_count;
  }

  if (0 != digit_count % 8) {
    for (size_t i{}; i < (digit_count / 8 + 1) * 8 - digit_count; ++i)
      reversed_number <<= 1;
  }

  return to_string(reversed_number);
}

int main() {
  // cout << BinaryReversal(gets(stdin));
  cout << BinaryReversal("47") << '\n';    // expected output: "244"
  cout << BinaryReversal("213") << '\n';   // expected output: "171"
  cout << BinaryReversal("4567") << '\n';  // expected output: "60296"
  cout << BinaryReversal("6") << '\n';     // expected output: "96"

  return 0;
}
