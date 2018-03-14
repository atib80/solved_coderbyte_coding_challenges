/*
Coderbyte coding challenge: Number Encoding

Using the C++ language, have the function NumberEncoding(str) take the str
parameter and encode the message according to the following rule: encode every
letter into its corresponding numbered position in the alphabet. Symbols and
spaces will also be used in the input. For example: if str is "af5c a#!" then
your program should return 1653 1#!.

Sample test cases:

Input:  "hello 45"
Output: 85121215 45

Input:  "jaj-a"
Output: 10110-1
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  while (begin_str <= end_str) {
    bool cont{};
    if (isspace(str[begin_str])) {
      cont = true;
      begin_str++;
    }

    if (isspace(str[end_str])) {
      cont = true;
      end_str--;
    }

    if (!cont)
      break;
  }

  if (begin_str > end_str)
    return string{};

  return str.substr(begin_str, end_str - begin_str + 1);
}

string NumberEncoding_v1(string str) {
  static const string alphabet_str{"abcdefghijklmnopqrstuvwxyz"};

  str = trim(str);

  ostringstream oss{};

  for (size_t i{}; i < str.length(); i++) {
    str[i] = static_cast<char>(tolower(str[i]));
    const size_t index{alphabet_str.find(str[i])};

    if (string::npos == index) {
      oss << str[i];
      continue;
    }

    oss << index + 1;
  }

  return oss.str();
}

string NumberEncoding_v2(string str) {
  str = trim(str);

  ostringstream oss{};

  for (size_t i{}; i < str.length(); i++) {
    const char ch{static_cast<char>(tolower(str[i]))};

    if (isalpha(ch)) {
      oss << static_cast<size_t>(ch - 'a') + 1;
      continue;
    }

    oss << str[i];
  }

  return oss.str();
}

int main() {
  // cout << NumberEncoding_v1(move(string{gets(stdin)}));
  cout << NumberEncoding_v1(move(string{"af5c a#!"}))
       << '\n';  // expected output: 1653 1#!
  cout << NumberEncoding_v1(move(string{"hello 45"}))
       << '\n';  // expected output: 85121215 45
  cout << NumberEncoding_v1(move(string{"jaj-a"}))
       << '\n';  // expected output: 10110-1
  cout << NumberEncoding_v1(move(string{"km#e"}))
       << '\n';  // expected output: 1113#5
  cout << NumberEncoding_v1(move(string{"af5c a#!"}))
       << '\n';  // expected output: 1653 1#!
  cout << NumberEncoding_v1(move(string{"---fc9#"}))
       << '\n';  // expected output: ---639#

  return 0;
}
