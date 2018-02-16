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

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

string convert_to_bin_string(int number) {
  string bin_str{};

  size_t i{};

  while (number) {
    if (number % 2 == 1)
      bin_str.push_back('1');
    else
      bin_str.push_back('0');
    number >>= 1;
    i++;
  }

  reverse(begin(bin_str), end(bin_str));

  if ((i % 8) != 0)
    bin_str.insert(0, move(string((i / 8 + 1) * 8 - i, '0')));

  return bin_str;
}

int convert_bin_string_to_decimal_number(const string& bin_str) {
  if (any_of(begin(bin_str), end(bin_str), [](const char digit) {
        return ((digit != '0') && (digit != '1'));
      }))
    return 0;

  int value{};

  for (size_t i{}; i < bin_str.length(); i++) {
    value <<= 1;
    value |= (bin_str[i] - '0');
  }

  return value;
}

string BinaryReversal(string str) {
  str = trim(str);
  const int number{stoi(str)};

  if (!number)
    return "0";

  string bin_str{convert_to_bin_string(number)};

  reverse(begin(bin_str), end(bin_str));

  // return to_string(stoi(bin_str, nullptr, 2));
  return to_string(convert_bin_string_to_decimal_number(bin_str));
}

int main() {
  // cout << BinaryReversal(move(string{gets(stdin)}));
  cout << BinaryReversal(move(string{"47"})) << '\n';  // expected output: "244"
  cout << BinaryReversal(move(string{"213"}))
       << '\n';  // expected output: "171"
  cout << BinaryReversal(move(string{"4567"}))
       << '\n';  // expected output: "60296"

  return 0;
}
