/*
Coderbyte coding challenge: String Periods

Using the C++ language, have the function StringPeriods(str) take the str
parameter being passed and determine if there is some substring K that can be
repeated N > 1 times to produce the input string exactly as it appears. Your
program should return the longest substring K, and if there is none it should
return the string -1.

For example: if str is "abcababcababcab" then your program should return abcab
because that is the longest substring that is repeated 3 times to create the
final string. Another example: if str is "abababababab" then your program should
return ababab because it is the longest substring. If the input string contains
only a single character, your program should return the string -1.

Sample test cases:

Input:  "abcxabc"
Output: "-1"

Input:  "affedaaffed"
Output: "-1"
*/

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

string StringPeriods(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2)
    return "-1";

  size_t current_substr_len{str_len / 2};

  while (current_substr_len > 1) {
    const string current_substr{str.substr(0, current_substr_len)};

    string build_str{current_substr};

    while (build_str.length() < str_len) {
      build_str += current_substr;
    }

    if (str == build_str)
      return current_substr;

    current_substr_len--;
  }

  return "-1";
}

int main() {
  // cout << StringPeriods(move(string{gets(stdin)}));
  cout << StringPeriods(move(string{"abcababcababcab"}))
       << '\n';  // expected output: "abcab"
  cout << StringPeriods(move(string{"abababababab"}))
       << '\n';  // expected output: "ababab"
  cout << StringPeriods(move(string{"abcxabc"}))
       << '\n';  // expected output: "-1"
  cout << StringPeriods(move(string{"affedaaffed"}))
       << '\n';  // expected output: "-1"

  return 0;
}
