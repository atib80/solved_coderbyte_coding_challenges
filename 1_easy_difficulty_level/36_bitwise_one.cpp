/*
Coderbyte coding challenge: Bitwise One

Using the C++ language, have the function BitwiseOne(strArr) take the array of
strings stored in strArr, which will only contain two strings of equal length
that represent binary numbers, and return a final binary string that performed
the bitwise OR operation on both strings. A bitwise OR operation places a 0 in
the new string where there are zeroes in both binary strings, otherwise it
places a 1 in that spot. For example: if strArr is ["1001", "0100"] then your
program should return the string "1101"

Sample test cases:

Input:  "100", "000"
Output: "100"

Input:  "00011", "01010"
Output: "01011"
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

std::string trim(const std::string& src,
                 const char* chars_to_trim = " \t\n\f\v\r") {
  if (0U == src.length())
    return {};

  const std::unordered_set<char> trimmed_chars(
      chars_to_trim, chars_to_trim + strlen(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const char ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return {};

  const auto last{std::find_if(std::crbegin(src), std::crend(src),
                               [&trimmed_chars](const char ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return {first, last};
}

string BitwiseOne_v1(string* binary_numbers, const size_t str_arr_size) {
  if (str_arr_size < 2U)
    return "not possible";

  binary_numbers[0] = trim(binary_numbers[0]);
  binary_numbers[1] = trim(binary_numbers[1]);

  if (binary_numbers[0].length() != binary_numbers[1].length())
    return "not possible";

  string result{binary_numbers[0]};

  for (size_t i{}; i < binary_numbers[0].length(); i++) {
    if ('1' == binary_numbers[1][i])
      result[i] = '1';
  }

  return result;
}

string BitwiseOne_v2(const string* binary_numbers, const size_t str_arr_size) {
  if (str_arr_size < 2U)
    return "not possible";

  if (binary_numbers[0].length() != binary_numbers[1].length())
    return "not possible";

  int64_t result{stoll(binary_numbers[0], nullptr, 2) |
                 stoll(binary_numbers[1], nullptr, 2)};

  string result_str{};
  result_str.reserve(binary_numbers[0].length());

  while (result) {
    if (result % 2)
      result_str.push_back('1');
    else
      result_str.push_back('0');

    result /= 2;
  }

  if (binary_numbers[0].length() > result_str.length())
    result_str.append(binary_numbers[0].length() - result_str.length(), '0');

  reverse(begin(result_str), end(result_str));

  return result_str;
}

int main() {
  // string str_arr1[] = gets(stdin);
  // cout << BitwiseOne_v2(str_arr1, sizeof(str_arr1)/sizeof(*str_arr1));
  string str_arr2[]{"1001", "0100"};
  cout << BitwiseOne_v2(str_arr2, sizeof(str_arr2) / sizeof(*str_arr2))
       << '\n';  // expected output: "1101"
  string str_arr3[]{"100", "000"};
  cout << BitwiseOne_v2(str_arr3, sizeof(str_arr3) / sizeof(*str_arr3))
       << '\n';  // expected output: "100"
  string str_arr4[]{"00011", "01010"};
  cout << BitwiseOne_v2(str_arr4, sizeof(str_arr4) / sizeof(*str_arr4))
       << '\n';  // expected output: "01011"

  return 0;
}
