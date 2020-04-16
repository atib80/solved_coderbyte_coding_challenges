/*
Coderbyte coding challenge: Basic Roman Numerals

Using the C++ language, have the function BasicRomanNumerals(str) read str which
will be a string of Roman numerals. The numerals being used are: I for 1, V for
5, X for 10, L for 50, C for 100, D for 500 and M for 1000. In Roman numerals,
to create a number like 11 you simply add a 1 after the 10, so you get XI. But
to create a number like 19, you use the subtraction notation which is to add an
I before an X or V (or add an X before an L or C). So 19 in Roman numerals is
XIX.

The goal of your program is to return the decimal equivalent of the Roman
numeral given. For example: if str is "XXIV" your program should return 24.

Sample test cases:

Input:  "IV"
Output: 4

Input:  "XLVI"
Output: 46
*/

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
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

string BasicRomanNumerals(string str) {
  str = trim(str);

  if (str.empty())
    return "0";

  const unordered_map<string_view, size_t> rn{
      {"M", 1000U}, {"D", 500U}, {"C", 100U}, {"L", 50U},
      {"X", 10U},   {"V", 5U},   {"I", 1U},   {"IV", 4U},
      {"IX", 9U},   {"XL", 40U}, {"XC", 90U}};

  size_t number{};

  for (size_t i{}; i < str.length(); ++i) {
    const size_t needle_len{i < str.length() - 1 ? 2U : 1U};
    string_view key{&str[i], needle_len};

    if (rn.find(key) != cend(rn)) {
      number += rn.at(key);  // number += (*rn.find(key)).second;
      ++i;

    } else {
      key = {&str[i], 1};
      if (rn.find(key) != cend(rn))
        number += rn.at(key);
    }
  }

  return to_string(number);
}

int main() {
  // cout << BasicRomanNumerals(gets(stdin));
  cout << BasicRomanNumerals("XI") << '\n';    // expected output: 11
  cout << BasicRomanNumerals("XIX") << '\n';   // expected output: 19
  cout << BasicRomanNumerals("XXIV") << '\n';  // expected output: 24
  cout << BasicRomanNumerals("IV") << '\n';    // expected output: 4
  cout << BasicRomanNumerals("XLVI") << '\n';  // expected output: 46

  return 0;
}
