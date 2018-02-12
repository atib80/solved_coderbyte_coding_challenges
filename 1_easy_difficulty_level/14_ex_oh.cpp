/*
Coderbyte coding challenge: Ex Oh

Using the C++ language, have the function ExOh(str) take the str parameter being
passed and return the string true if there is an equal number of x's and o's,
otherwise return the string false. Only these two letters will be entered in the
string, no punctuation or numbers. For example: if str is "xooxxxxooxo" then the
output should return false because there are 6 x's and 5 o's.

Sample test cases:

Input:  "xooxxo"
Output: "true"

Input:  "x"
Output: "false"
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

string ex_oh(string str) {
  str = trim(str);

  const auto o_count = count(begin(str), end(str), 'o');
  const auto x_count = count(begin(str), end(str), 'x');

  if (o_count == x_count)
    return "true";
  return "false";
}

int main() {
  // cout << ex_oh(move(string{gets(stdin)}));
  cout << ex_oh(move(string{"xooxxxxooxo"}))
       << '\n';                                   // expected output: "false"
  cout << ex_oh(move(string{"xooxxo"})) << '\n';  // expected output: "true"
  cout << ex_oh(move(string{"x"})) << '\n';       // expected output: "false"

  return 0;
}
