/*
Coderbyte coding challenge: Palindrome Creator

Have the function PalindromeCreator(str) take the str parameter being passed and
determine if it is possible to create a palindromic string of at least 3
characters by removing 1 or 2 characters. For example: if str is "abjchba" then
you can remove the characters jc to produce "abhba" which is a palindrome. For
this example your program should return the two characters that were removed
with no delimiter and in the order they appear in the string, so jc. If 1 or 2
characters cannot be removed to produce a palindrome, then return the string not
possible. If the input string is already a palindrome, your program should
return the string palindrome.

The input will only contain lowercase alphabetic characters.
Your program should always attempt to create the longest palindromic substring
by removing 1 or 2 characters (see second sample test case as an example). The 2
characters you remove do not have to be adjacent in the string.

Sample test cases:

Input:  "mmop"
Output: "not possible"

Input:  "kjjjhjjj"
Output: "k"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>

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

bool is_palindrome(const string& str) {
  string reversed_str{str};
  reverse(begin(reversed_str), end(reversed_str));
  return str == reversed_str;
}

bool is_palindrome(const string& str, unordered_set<size_t> ignore_indices) {
  stack<char> s{};
  queue<char> q{};

  for (size_t i{}; i != str.length(); i++) {
    if (ignore_indices.count(i))
      continue;

    s.emplace(str[i]);
    q.emplace(str[i]);
  }

  while (!s.empty() && !q.empty()) {
    if (s.top() != q.front())
      return false;
    s.pop();
    q.pop();
  }

  return true;
}

string PalindromeCreator_v1(string str) {
  str = trim(str);

  if (is_palindrome(str))
    return "palindrome";

  const size_t str_len{str.length()};

  for (size_t i{}; i < str_len; i++) {
    const char needle_char{str[i]};

    str.erase(i, 1);

    if (is_palindrome(str))
      return string(1, needle_char);

    str.insert(i, 1, needle_char);
  }

  if (str_len < 5)
    return "not possible";  // if str's length is less than 5 then we
                            // can only remove 1 character from it at a time

  for (size_t i{}; i < str_len - 1; i++) {
    for (size_t j{i + 1}; j < str_len; j++) {
      const string needle{str[i], str[j]};

      str.erase(i, 1);
      str.erase(j - 1, 1);

      if (is_palindrome(str))
        return needle;

      str.insert(i, 1, needle[0]);
      str.insert(j, 1, needle[1]);
    }
  }

  return "not possible";
}

string PalindromeCreator_v2(string str) {
  str = trim(str);

  if (is_palindrome(str))
    return "palindrome";

  const size_t str_len{str.length()};

  for (size_t i{}; i < str_len; i++) {
    if (is_palindrome(str, move(unordered_set<size_t>{i})))
      return string(1, str[i]);
  }

  if (str_len < 5)
    return "not possible";  // if str's length is less than 5 then we
                            // can only remove 1 character from it at a time

  for (size_t i{}; i < str_len - 1; i++) {
    for (size_t j{i + 1}; j < str_len; j++) {
      if (is_palindrome(str, move(unordered_set<size_t>{i, j})))
        return string({str[i], str[j]});
    }
  }

  return "not possible";
}

int main() {
  // cout << PalindromeCreator_v2(move(string{gets(stdin)}));
  cout << PalindromeCreator_v2(move(string{"abjchba"})) << '\n';  // "jc"
  cout << PalindromeCreator_v2(move(string{"mmop"})) << '\n';  // "not possible"
  cout << PalindromeCreator_v2(move(string{"kjjjhjjj"})) << '\n';      // "k"
  cout << PalindromeCreator_v2(move(string{"vhhgghhgghhk"})) << '\n';  // "vk"

  return 0;
}
