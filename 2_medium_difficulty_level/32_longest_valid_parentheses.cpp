/*
Leetcode coding challenge: Longest valid parentheses substring

Given a string containing just the characters '(' and ')', find the length of
the longest valid (well-formed) parentheses substring.

Example 1:
Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"

Example 2:
Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"
*/

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using std::cout;
using std::map;
using std::pair;
using std::stack;
using std::string;
using std::vector;

class Solution {
 public:
  // first iterative solution (int longestValidParentheses_v1(string str)) is
  // implemented by using stack<size_t> and map<size_t, bool> data structures
  // for keeping track of and counting lengths of valid substrings which must
  // consist of even numbers of correctly placed parentheses {'(', ')'} only.

  int longestValidParentheses_v1(string str) {
    if (str.length() < 2)
      return 0;
    size_t start{};
    while (')' == str[start])
      start++;
    size_t last = str.length() - 1;
    while ('(' == str[last])
      last--;

    stack<size_t> s{};
    map<size_t, bool> is_parenthesis_pair_closed{};

    for (size_t i{start}; i <= last; i++) {
      if ('(' == str[i]) {
        s.emplace(i);
        is_parenthesis_pair_closed[i] = false;
      } else if (')' == str[i]) {
        if (!s.empty()) {
          const size_t prnths_start_index{s.top()};
          s.pop();
          is_parenthesis_pair_closed[prnths_start_index] = true;
        } else
          is_parenthesis_pair_closed[i] = false;
      }
    }

    int longest_substr_len{}, current_substr_len{};

    for (const pair<size_t, bool>& p : is_parenthesis_pair_closed) {
      if (p.second)
        current_substr_len += 2;
      else {
        if (current_substr_len > longest_substr_len)
          longest_substr_len = current_substr_len;
        current_substr_len = 0;
      }
    }

    if (current_substr_len > longest_substr_len)
      longest_substr_len = current_substr_len;

    return longest_substr_len;
  }

  // second iterative solution (int longestValidParentheses_v2(string str)) is
  // implemented by using stack<size_t> and vector<int> data structures for
  // keeping track of and counting lengths of valid substrings which must
  // consist of even numbers of correctly placed parentheses {'(', ')'} only.

  int longestValidParentheses_v2(string str) {
    const size_t str_len{str.length()};
    if (str_len < 2)
      return 0;
    int start{};
    while (')' == str[start])
      start++;
    int last = str_len - 1;
    while ('(' == str[last])
      last--;

    if (last < 1)
      return 0;

    stack<size_t> s{};
    vector<int> is_parenthesis_pair_closed(last - start + 1);
    size_t index{};

    for (int i{start}; i <= last; i++) {
      if ('(' == str[i])
        s.emplace(index++);
      else if (')' == str[i]) {
        if (!s.empty()) {
          is_parenthesis_pair_closed[s.top()] = 1;
          s.pop();
        } else
          index++;
      }
    }

    int longest_substr_len{}, current_substr_len{};

    for (const int p : is_parenthesis_pair_closed) {
      if (p)
        current_substr_len += 2;
      else {
        if (current_substr_len > longest_substr_len)
          longest_substr_len = current_substr_len;
        current_substr_len = 0;
      }
    }

    if (current_substr_len > longest_substr_len)
      longest_substr_len = current_substr_len;

    return longest_substr_len;
  }
};

int main() {
  Solution s{};

  cout << s.longestValidParentheses_v2(string{"(()"})
       << '\n';  // expected output: 2
  cout << s.longestValidParentheses_v2(string{")()())"})
       << '\n';  // expected output: 4
  cout << s.longestValidParentheses_v2(string{"()(()"})
       << '\n';  // expected output: 2
  cout << s.longestValidParentheses_v2(string{"(()()"})
       << '\n';  // expected output: 4

  return 0;
}