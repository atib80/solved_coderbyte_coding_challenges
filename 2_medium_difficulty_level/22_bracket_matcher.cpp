/*
Coderbyte coding challenge: Bracket Matcher

Using the C++ language, have the function BracketMatcher(str) take the str
parameter being passed and return 1 if the brackets are correctly matched and
each one is accounted for. Otherwise return 0. For example: if str is "(hello
(world))", then the output should be 1, but if str is "((hello (world))" the the
output should be 0 because the brackets do not correctly match up. Only "(" and
")" will be used as brackets. If str contains no brackets return 1.

Sample test cases:

Input:  "(coder)(byte))"
Output: 0

Input:  "(c(oder)) b(yte)"
Output: 1
*/

#include <algorithm>
#include <cctype>
#include <iostream>
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

int RemoveBrackets(string str) {
  str = trim(str);

  if (!any_of(begin(str), end(str),
              [](const char ch) { return (ch == '(' || ch == ')'); }))
    return 1;

  int balance_count{};
  size_t start{};

  while (')' == str[start]) {
    start++;
    balance_count++;
  }

  if (balance_count)
    return 0;

  size_t last{str.length() - 1};

  while ('(' == str[last]) {
    last--;
    balance_count++;
  }

  if (balance_count)
    return 0;

  for (size_t i{start}; i <= last; i++) {
    if ('(' == str[i])
      balance_count++;

    else if (')' == str[i]) {
      if (balance_count <= 0)
        return 0;

      balance_count--;
    }
  }

  if (!balance_count)
    return 1;

  return 0;
}

int main() {
  // cout << RemoveBrackets(move(string{gets(stdin)}));
  cout << RemoveBrackets(move(string{"(hello (world))"}))
       << '\n';  // expected output: 1
  cout << RemoveBrackets(move(string{"(coder)(byte))"}))
       << '\n';  // expected output: 0
  cout << RemoveBrackets(move(string{"(c(oder)) b(yte)"}))
       << '\n';  // expected output: 1
  cout << RemoveBrackets(move(string{"the color re(d))()(()"}))
       << '\n';  // expected output: 0

  return 0;
}
