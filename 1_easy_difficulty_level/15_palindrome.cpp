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
#include <locale>
#include <queue>
#include <stack>
#include <string>

using namespace std;

string trim(const string& str, const locale& loc = locale{}) {
  const size_t str_len{str.length()};

  if (0U == str_len)
    return {};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str], loc))
      break;
  }

  if (begin_str > end_str)
    return {};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str], loc))
      break;
  }

  return {cbegin(str) + begin_str, cbegin(str) + end_str + 1};
}

string palindrome_v1(string str) {
  str = trim(str);

  if (str.length() < 2)
    return "false";

  stack<char> s{};
  queue<char> q{};
  locale loc{};

  for (const char ch : str) {
    if (isspace(ch, loc))
      continue;

    s.emplace(ch);
    q.emplace(ch);
  }

  while (!s.empty()) {
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
  locale loc{};

  while (i < j) {
    if (!isalpha(str[i], loc)) {
      i++;
      continue;
    }

    if (!isalpha(str[j], loc)) {
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

string palindrome_v3(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2U)
    return "false";

  string str_no_spaces{};
  str_no_spaces.reserve(str_len);
  locale loc{};

  for (const char ch : str) {
    if (isalpha(ch, loc))
      str_no_spaces.push_back(ch);
  }

  for (size_t i{}, j{str_no_spaces.length() - 1}; i < j; ++i, --j) {
    if (str_no_spaces[i] != str_no_spaces[j])
      return "false";
  }

  return "true";
}

int main() {
  // cout << palindrome_v3(gets(stdin));
  cout << palindrome_v3("racecar") << '\n';  // expected output: "true"
  cout << palindrome_v3("never odd or even")
       << '\n';                            // expected output: "true"
  cout << palindrome_v3("eye") << '\n';    // expected output: "true"
  cout << palindrome_v3("apple") << '\n';  // expected output: "false"
  cout << palindrome_v3("rotor") << '\n';  // expected output: "true"

  return 0;
}
