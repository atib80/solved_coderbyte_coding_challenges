/*
Coderbyte coding challenge: String Merge

Using the C++ language, have the function StringMerge(str) read the str
parameter being passed which will contain a large string of alphanumeric
characters with a single asterisk character splitting the string evenly into two
separate strings. Your goal is to return a new string by pairing up the
characters in the corresponding locations in both strings. For example: if str
is "abc1*kyoo" then your program should return the string akbyco1o because a
pairs with k, b pairs with y, etc. The string will always split evenly with the
asterisk in the center.

Sample test cases:

Input:  "aaa*bbb"
Output: "ababab"

Input:  "123hg*aaabb"
Output: "1a2a3ahbgb"
*/

#include <cctype>
#include <iostream>
#include <sstream>
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

string StringMerge_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 3)
    return "not possible";

  const size_t delim_pos{str.find('*', 1)};

  if (string::npos == delim_pos)
    return "not possible";

  if (2 * delim_pos != str_len - 1)
    return "not possible";

  string result{};
  result.reserve(str_len - 1);

  for (size_t i{}, j{delim_pos + 1}; i != delim_pos; i++, j++) {
    result.push_back(str[i]);
    result.push_back(str[j]);
  }

  return result;
}

string StringMerge_v2(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 3)
    return "not possible";

  const size_t delim_pos{str.find('*', 1)};

  if (string::npos == delim_pos)
    return "not possible";

  if (2 * delim_pos != str_len - 1)
    return "not possible";

  ostringstream oss{};

  for (size_t i{}, j{delim_pos + 1}; i != delim_pos; i++, j++)
    oss << str[i] << str[j];

  return oss.str();
}

int main() {
  // cout << StringMerge_v1(move(string{gets(stdin)}));
  cout << StringMerge_v1(move(string{"abc1*kyoo"}))
       << '\n';  // expected output: "akbyco1o"
  cout << StringMerge_v1(move(string{"aaa*bbb"}))
       << '\n';  // expected output: "ababab"
  cout << StringMerge_v1(move(string{"123hg*aaabb"}))
       << '\n';  // expected output: "1a2a3ahbgb"
  return 0;
}
