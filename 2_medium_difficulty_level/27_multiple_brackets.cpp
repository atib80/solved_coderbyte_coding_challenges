/*
Coderbyte coding challenge: Multiple Brackets

Using the C++ language, have the function MultipleBrackets(str) take the str
parameter being passed and return 1 #ofBrackets if the brackets are correctly
matched and each one is accounted for. Otherwise return 0. For example: if str
is "(hello [world])(!)", then the output should be 1 3 because all the brackets
are matched and there are 3 pairs of brackets, but if str is "((hello [world])"
the the output should be 0 because the brackets do not correctly match up. Only
"(", ")", "[", and "]" will be used as brackets. If str contains no brackets
return 1.

Sample test cases:

Input:  "(coder)[byte)]"
Output: 0

Input:  "(c([od]er)) b(yt[e])"
Output: 1 5
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

  output.erase(find_if(rbegin(output), rend(output),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

string MultipleBrackets(string str) {
  str = trim(str);

  if (str.empty())
    return "1";

  if (!any_of(begin(str), end(str), [](const char ch) {
        return (ch == '(' || ch == ')' || ch == '[' || ch == ']');
      }))
    return "1";

  int parentheses_balance_count{};
  int brackets_balance_count{};

  size_t start{};

  while (('(' != str[start]) && ('[' != str[start])) {
    if (')' == str[start])
      parentheses_balance_count++;
    else if (']' == str[start])
      brackets_balance_count++;
    start++;
  }

  size_t last{str.length() - 1};

  while ((')' != str[last]) && (']' != str[last])) {
    if ('(' == str[last])
      parentheses_balance_count++;
    else if ('[' == str[last])
      brackets_balance_count++;
    last--;
  }

  if (parentheses_balance_count || brackets_balance_count)
    return "0";

  size_t number_of_pairs{};

  for (size_t i{start}; i <= last; i++) {
    if ('(' == str[i])
      parentheses_balance_count++;

    else if ('[' == str[i])
      brackets_balance_count++;

    else if (')' == str[i]) {
      if (parentheses_balance_count <= 0)
        return "0";

      parentheses_balance_count--;

      number_of_pairs++;

    } else if (']' == str[i]) {
      if (brackets_balance_count <= 0)
        return "0";

      brackets_balance_count--;

      number_of_pairs++;
    }
  }

  if (parentheses_balance_count || brackets_balance_count)
    return "0";

  return string{"1 " + to_string(number_of_pairs)};
}

int main() {
  // cout << MultipleBrackets(move(string{gets(stdin)}));
  cout << MultipleBrackets(move(string{"(coder)[byte)]"}))
       << '\n';  // expected output: 0
  cout << MultipleBrackets(move(string{"(c([od]er)) b(yt[e])"}))
       << '\n';  // expected output: 1 5
  cout << MultipleBrackets(move(string{"(hello [world])(!)"}))
       << '\n';  // expected output: 1 3
  cout << MultipleBrackets(move(string{"((hello [world])"}))
       << '\n';  // expected output: 0

  return 0;
}
