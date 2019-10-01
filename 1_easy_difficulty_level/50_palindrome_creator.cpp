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
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>

using namespace std;

std::string trim(const std::string& src,
                 const char* chars_to_trim = " \t\n\f\v\r") {
  if (0U == src.length())
    return {};

  const std::unordered_set<char> trimmed_chars(
      chars_to_trim, chars_to_trim + strlen(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const char ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return {};

  const auto last{std::find_if(std::crbegin(src), std::crend(src),
                               [&trimmed_chars](const char ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return {first, last};
}

bool is_palindrome(const string& str,
                   size_t ignored_index_a = string::npos,
                   size_t ignored_index_b = string::npos) {
  if (ignored_index_a >= str.length())
    ignored_index_a = string::npos;
  if (ignored_index_b >= str.length())
    ignored_index_b = string::npos;

  const size_t min_required_len{3U +
                                (ignored_index_a != string::npos ? 1U : 0U) +
                                (ignored_index_b != string::npos ? 1U : 0U)};
  if (str.length() < min_required_len)
    return false;

  const bool check_ignored_index_a{string::npos != ignored_index_a};
  const bool check_ignored_index_b{string::npos != ignored_index_b};

  for (size_t i{}, j{str.length() - 1}; i < j; ++i, --j) {
    if (check_ignored_index_a) {
      if (ignored_index_a == i)
        ++i;
      if (ignored_index_a == j)
        --j;
      if (i >= j)
        break;
    }

    if (check_ignored_index_b) {
      if (ignored_index_b == i)
        ++i;
      if (ignored_index_b == j)
        --j;
      if (i >= j)
        break;
    }

    if (str[i] != str[j])
      return false;
  }

  return true;
}

string PalindromeCreator_v1(string str) {
  str = trim(str);

  if (is_palindrome(str))
    return "palindrome";

  const size_t str_len{str.length()};

  for (size_t i{}; i < str_len; ++i) {
    if (is_palindrome(str, i))
      return string(1, str[i]);
  }

  if (str_len < 5U)
    return "not possible";  // if str's length is less than 5 characters then we
                            // can remove only 1 character from it at a time

  for (size_t i{}; i < str_len - 1; ++i) {
    for (size_t j{i + 1}; j < str_len; ++j) {
      if (is_palindrome(str, i, j))
        return {str[i], str[j]};
    }
  }

  return "not possible";
}

bool is_palindrome(const string& str,
                   const unordered_set<size_t>& ignore_indices) {
  stack<char> s{};
  queue<char> q{};

  for (size_t i{}; i < str.length(); ++i) {
    if (1U == ignore_indices.count(i))
      continue;

    s.emplace(str[i]);
    q.emplace(str[i]);
  }

  while (!s.empty()) {
    if (s.top() != q.front())
      return false;
    s.pop();
    q.pop();
  }

  return true;
}

string PalindromeCreator_v2(string str) {
  str = trim(str);

  if (is_palindrome(str))
    return "palindrome";

  const size_t str_len{str.length()};

  unordered_set<size_t> ignore_indices{};

  for (size_t i{}; i < str_len; ++i) {
    ignore_indices.emplace(i);

    if (is_palindrome(str, ignore_indices))
      return string(1, str[i]);

    ignore_indices.erase(i);
  }

  if (str_len < 5U)
    return "not possible";  // if str's length is less than 5 characters then we
                            // can remove only 1 character from it at a time

  for (size_t i{}; i < str_len - 1; ++i) {
    ignore_indices.emplace(i);

    for (size_t j{i + 1}; j < str_len; ++j) {
      ignore_indices.emplace(j);

      if (is_palindrome(str, ignore_indices))
        return {str[i], str[j]};

      ignore_indices.erase(j);
    }

    ignore_indices.erase(i);
  }

  return "not possible";
}

int main() {
  // cout << PalindromeCreator_v1(gets(stdin));
  cout << PalindromeCreator_v1("abjchba") << '\n';       // "jc"
  cout << PalindromeCreator_v1("mmop") << '\n';          // "not possible"
  cout << PalindromeCreator_v1("kjjjhjjj") << '\n';      // "k"
  cout << PalindromeCreator_v1("vhhgghhgghhk") << '\n';  // "vk"

  return 0;
}
