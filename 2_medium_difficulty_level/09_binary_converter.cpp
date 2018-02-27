/*
Coderbyte coding challenge: Binary Converter

Using the C++ language, have the function BinaryConverter(str) return the
decimal form of the binary value. For example: if 101 is passed return 5, or if
1000 is passed return 8.

Sample test cases:

Input:  "100101"
Output: "37"

Input:  "011"
Output: "3"
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

bool is_valid_binary_string(const string& str) {
  return all_of(begin(str), end(str),
                [](const char ch) { return (ch == '0' || ch == '1'); });
}

string BinaryConverter_v1(string str) {
  str = trim(str);

  if (!is_valid_binary_string(str))
    return "not possible";

  int decimal_number{};

  for (const char ch : str) {
    decimal_number <<= 1;
    decimal_number |= static_cast<int>(ch - '0');
  }

  return to_string(decimal_number);
}

string BinaryConverter_v2(string str) {
  str = trim(str);

  if (!is_valid_binary_string(str))
    return "not possible";

  const size_t str_len{str.length()};

  int decimal_number{};

  for (size_t i{}; i < str_len; i++) {
    if ('0' == str[i])
      continue;
    decimal_number += 1 << (str_len - i - 1);
  }

  return to_string(decimal_number);
}

string BinaryConverter_v3(string str) {
  str = trim(str);

  if (!is_valid_binary_string(str))
    return "not possible";

  return to_string(stoi(str, nullptr, 2));
}

int main() {
  // cout << BinaryConverter_v1(move(string{gets(stdin)}));
  cout << BinaryConverter_v1(move(string{"101"}))
       << '\n';  // expected output: 5
  cout << BinaryConverter_v1(move(string{"1000"}))
       << '\n';  // expected output: 8
  cout << BinaryConverter_v1(move(string{"100101"}))
       << '\n';  // expected output: 37
  cout << BinaryConverter_v1(move(string{"011"}))
       << '\n';  // expected output: 3

  return 0;
}
