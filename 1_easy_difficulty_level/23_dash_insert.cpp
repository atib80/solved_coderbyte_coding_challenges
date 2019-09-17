/*
Coderbyte coding challenge: Dash Insert

Using the C++ language, have the function DashInsert(str) insert dashes ('-')
between each two odd numbers in str. For example: if str is 454793 the output
should be 4547-9-3. Don't count zero as an odd number.

Sample test cases:

Input:  99946
Output: 9-9-946

Input:  56730
Output: 567-30
*/

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <sstream>
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

string DashInsert_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2U)
    return str;

  string result(1, str.front());
  result.reserve(2 * str_len - 1);

  bool is_prev_odd{(str[0] - '0') % 2 == 1};

  for (size_t i{1}; i < str_len; i++) {
    if (is_prev_odd && (str[i] - '0') % 2 == 1) {
      result.push_back('-');
      result.push_back(str[i]);
    } else {
      result.push_back(str[i]);
      is_prev_odd = (str[i] - '0') % 2 == 1;
    }
  }

  return result;
}

string DashInsert_v2(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2U)
    return str;

  ostringstream oss{};
  oss << str.front();

  bool is_prev_odd{(str.front() - '0') % 2 == 1};

  for (size_t i{1}; i < str_len; i++) {
    if (is_prev_odd && (str[i] - '0') % 2 == 1)
      oss << '-' << str[i];
    else {
      oss << str[i];
      is_prev_odd = (str[i] - '0') % 2 == 1;
    }
  }

  return oss.str();
}

int main() {
  // cout << DashInsert_v2(gets(stdin));
  cout << DashInsert_v2("454793") << '\n';  // expected output: "4547-9-3"
  cout << DashInsert_v2("99946") << '\n';   // expected output: "9-9-946"
  cout << DashInsert_v2("56730") << '\n';   // expected output: "567-30"

  return 0;
}
