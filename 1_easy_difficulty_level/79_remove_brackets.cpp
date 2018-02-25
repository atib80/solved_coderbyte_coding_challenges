/*
Coding challenge: Remove Brackets

Using the C++ language, have the function RemoveBrackets(str) take the str
string parameter being passed, which will contain only the characters "(" and
")", and determine the minimum number of brackets that need to be removed to
create a string of correctly matched brackets. For example: if str is "(()))"
then your program should return the number 1. The answer could potentially be 0,
and there will always be at least one set of matching brackets in the string.

Sample test cases:

Input:  "(())()((("
Output: 3

Input:  "(()("
Output: 2
*/

#include <cctype>
#include <cmath>
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

string RemoveBrackets(string str) {
  str = trim(str);

  int balance_count{};

  size_t start{};

  while (')' == str[start]) {
    start++;
    balance_count++;
  }

  size_t last{str.length() - 1};

  while ('(' == str[last]) {
    last--;
    balance_count++;
  }

  for (size_t i{start}; i <= last; i++) {
    if ('(' == str[i])
      balance_count++;
    else if (')' == str[i])
      balance_count--;
  }

  return to_string(abs(balance_count));
}

int main() {
  // cout << RemoveBrackets(move(string{gets(stdin)}));
  cout << RemoveBrackets(move(string{"(()))"})) << '\n';  //  expected output: 1
  cout << RemoveBrackets(move(string{"(())()((("}))
       << '\n';                                          //  expected output: 3
  cout << RemoveBrackets(move(string{"(()("})) << '\n';  //  expected output: 2
  cout << RemoveBrackets(move(string{")(()"})) << '\n';  //  expected output: 2

  return 0;
}
