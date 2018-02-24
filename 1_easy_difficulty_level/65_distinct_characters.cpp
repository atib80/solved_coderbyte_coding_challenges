/*
Coderbyte coding challenge: Distinct Characters

Using the C++ language, have the function DistinctCharacters(str) take the str
parameter being passed and determine if it contains at least 10 distinct
characters, if so, then your program should return the string true, otherwise it
should return the string false. For example: if str is "abc123kkmmmm?" then your
program should return the string false because this string contains only 9
distinct characters: a, b, c, 1, 2, 3, k, m, ? adds up to 9.

Sample test cases:

Input:  "12334bbmma:=6"
Output: "true"

Input:  "eeeemmmmmmmmm1000"
Output: "false"
*/

#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>

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

string DistinctCharacters_v1(string str) {
  str = trim(str);

  unordered_set<char> distinct_characters{};

  for (const char ch : str) {
    distinct_characters.insert(ch);

    if (distinct_characters.size() >= 10)
      return "true";
  }

  return "false";
}

string DistinctCharacters_v2(string str) {
  str = trim(str);

  unordered_set<char> distinct_characters(begin(str), end(str));

  if (distinct_characters.size() >= 10)
    return "true";

  return "false";
}

int main() {
  // cout << DistinctCharacters_v2(move(string{gets(stdin)}));
  cout << DistinctCharacters_v2(move(string{"abc123kkmmmm?"}))
       << '\n';  // expected output: "false"
  cout << DistinctCharacters_v2(move(string{"12334bbmma:=6"}))
       << '\n';  // expected output: "true"
  cout << DistinctCharacters_v2(move(string{"eeeemmmmmmmmm1000"}))
       << '\n';  // expected output: "false"
  return 0;
}
