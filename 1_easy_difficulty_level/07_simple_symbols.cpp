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

  if (!str_len)
    return string{};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return string{};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str]))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string SimpleSymbols(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (isalpha(str[0]) || isalpha(str[str_len - 1]))
    return "false";

  for (size_t i{}; i < str_len - 2; i++) {
    if (str[i] == '+') {
      if (isalpha(str[i + 1])) {
        if (str[i + 2] == '+')
          continue;

        else
          return "false";
      }

    } else if ('=' == str[i]) {
      if (isalpha(str[i + 1]))
        return "false";
    }
  }

  return "true";
}

string SimpleSymbols_v2(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (isalpha(str[0]) || isalpha(str[str_len - 1]))
    return "false";

  for (size_t i{1}; i < str_len - 1; i++) {
    if (isalpha(str[i]) && ('+' != str[i - 1] || '+' != str[i + 1]))
      return "false";
  }

  return "true";
}

int main() {
  // cout << SimpleSymbols_v2(move(string{gets(stdin)}));
  cout << SimpleSymbols_v2(move(string{"++d+===+c++==a"}))
       << '\n';  // expected output: "false"
  cout << SimpleSymbols_v2(move(string{"+d+=3=+s+"}))
       << '\n';  // expected output: "true"
  cout << SimpleSymbols_v2(move(string{"f++d+"}))
       << '\n';  // expected output: "false"

  return 0;
}
