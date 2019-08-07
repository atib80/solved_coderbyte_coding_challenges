/*
Coderbyte coding challenge: Simple Symbols

Using the C++ language, have the function SimpleSymbols(str) take the str
parameter being passed and determine if it is an acceptable sequence by either
returning the string true or false. The str parameter will be composed of + and
= symbols with several letters between them (ie. ++d+===+c++==a) and for the
string to be true each letter must be surrounded by a + symbol. So the string to
the left would be false. The string will not be empty and will have at least one
letter.

Sample test cases:

Input:  "+d+=3=+s+"
Output: "true"

Input:  "f++d+"
Output: "false"
*/

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (0U == str_len)
    return {};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return {};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str]))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string SimpleSymbols_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len)
    return "true";

  if (isalpha(str.front()) || isalpha(str.back()))
    return "false";

  if (str_len < 3U)
    return "true";

  for (size_t i{}; i < str_len - 2; i++) {
    if (str[i] == '+') {
      if (isalpha(str[i + 1])) {
        if (str[i + 2] == '+') {
          i++;
          continue;
        }
        return "false";
      }

    } else if ('=' == str[i] && isalpha(str[i + 1]))
      return "false";
  }

  return "true";
}

string SimpleSymbols_v2(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len)
    return "true";

  if (isalpha(str.front()) || isalpha(str.back()))
    return "false";

  if (str_len < 3U)
    return "true";

  for (size_t i{1}; i < str_len - 1; i++) {
    if (isalpha(str[i])) {
      if (!('+' == str[i - 1] && '+' == str[i + 1]))
        return "false";
      i++;
    }
  }

  return "true";
}

int main() {
  // cout << SimpleSymbols_v2(gets(stdin));
  cout << SimpleSymbols_v2("++d+===+c++==a")
       << '\n';                                   // expected output: "false"
  cout << SimpleSymbols_v2("+d+=3=+s+") << '\n';  // expected output: "true"
  cout << SimpleSymbols_v2("f++d+") << '\n';      // expected output: "false"

  return 0;
}
