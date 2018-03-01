/*
Coderbyte coding challenge: Palindrome

Using the C++ language, have the function Palindrome(str) take the str parameter
being passed and return the string true if the parameter is a palindrome, (the
string is the same forward as it is backward) otherwise return the string false.
For example: "racecar" is also "racecar" backwards. Punctuation and numbers will
not be part of the string.

Sample test cases:

Input:  "never odd or even"
Output: "true"

Input:  "eye"
Output: "true"
*/

#include <cctype>
#include <iostream>
#include <queue>
#include <stack>
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

string palindrome(string str) {
  str = trim(str);

  stack<char> s{};
  queue<char> q{};

  for (const char ch : str) {
    if (isspace(ch))
      continue;

    s.emplace(ch);
    q.emplace(ch);
  }

  while (!s.empty() && !q.empty()) {
    if (s.top() != q.front())
      return "false";
    s.pop();
    q.pop();
  }

  return "true";
}

string palindrome_v2(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2)
    return "false";

  size_t i{}, j{str_len - 1};

  while (i < j) {
    if (!isalpha(str[i])) {
      i++;
      continue;
    }

    if (!isalnum(str[j])) {
      j--;
      continue;
    }

    if (str[i] != str[j])
      return "false";

    i++;
    j--;
  }

  return "true";
}

int main() {
  // cout << palindrome_v2(move(string{gets(stdin)}));
  cout << palindrome_v2(move(string{"racecar"}))
       << '\n';  // expected output: "true"
  cout << palindrome_v2(move(string{"never odd or even"}))
       << '\n';  // expected output: "true"
  cout << palindrome_v2(move(string{"eye"}))
       << '\n';  // expected output: "true"

  return 0;
}
