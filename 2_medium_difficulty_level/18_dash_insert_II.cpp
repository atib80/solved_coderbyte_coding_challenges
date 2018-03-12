/*
Coderbyte coding challenge: Dash Insert II

Using the C++ language, have the function DashInsertII(str) insert dashes ('-')
between each two odd numbers and insert asterisks ('*') between each two even
numbers in str. For example: if str is 4546793 the output should be 454*67-9-3.
Don't count zero as an odd or even number.

Sample test cases:

Input:  "99946"
Output: "9-9-94*6"

Input:  "56647304"
Output: "56*6*47-304"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string trim(const string& input) {
  
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

string DashInsertII_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2)
    return str;

  string result(1, str[0]);
  size_t digit{static_cast<size_t>(str[0] - '0')};
  bool is_prev_digit_zero{digit == 0};
  bool is_prev_odd{digit % 2 == 1};

  for (size_t i{1}; i < str_len; i++) {
    digit = static_cast<size_t>(str[i] - '0');

    if (!is_prev_digit_zero && digit) {
      if (is_prev_odd && (digit % 2 == 1))
        result.push_back('-');
      else if (!is_prev_odd && (digit % 2 == 0))
        result.push_back('*');
    }

    result.push_back(str[i]);
    is_prev_digit_zero = digit == 0;
    is_prev_odd = digit % 2 == 1;
  }

  return result;
}

string DashInsertII_v2(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2)
    return str;

  ostringstream oss{};
  oss << str[0];

  size_t digit{static_cast<size_t>(str[0] - '0')};
  bool is_prev_digit_zero{digit == 0};
  bool is_prev_odd{digit % 2 == 1};

  for (size_t i{1}; i < str_len; i++) {
    digit = static_cast<size_t>(str[i] - '0');

    if (!is_prev_digit_zero && digit) {
      if (is_prev_odd && (digit % 2 == 1))
        oss << '-';
      else if (!is_prev_odd && (digit % 2 == 0))
        oss << '*';
    }

    oss << str[i];

    is_prev_digit_zero = digit == 0;
    is_prev_odd = digit % 2 == 1;
  }

  return oss.str();
}

int main() {
  // cout << DashInsertII_v2(move(string{gets(stdin)}));
  cout << DashInsertII_v2(move(string{"4546793"}))
       << '\n';  // expected output: "454*67-9-3"
  cout << DashInsertII_v2(move(string{"99946"}))
       << '\n';  // expected output: "9-9-94*6"
  cout << DashInsertII_v2(move(string{"56647304"}))
       << '\n';  // expected output: "56*6*47-304"

  return 0;
}
