/*
Coderbyte coding challenge: Even Pairs

Using the C++ language, have the function EvenPairs(str) take the str parameter
being passed and determine if a pair of adjacent even numbers exists anywhere in
the string. If a pair exists, return the string true, otherwise return false.
For example: if str is "f178svg3k19k46" then there are two even numbers at the
end of the string, "46" so your program should return the string true. Another
example: if str is "7r5gg812" then the pair is "812" (8 and 12) so your program
should return the string true.

Sample test cases:

Input:  "3gy41d216"
Output: "true"

Input:  "f09r27i8e67"
Output: "false"
*/

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
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

bool check_if_num_str_consists_of_two_even_numbers(const string& str,
                                                   size_t start,
                                                   const size_t last) {
  for (; start < last; ++start) {
    if (str[start] % 2 == 0)
      break;
  }

  if (start >= last - 1)
    return false;

  return str[last - 1] % 2 == 0 ? true : false;
}

string EvenPairs(string str) {
  str = trim(str);

  if (str.length() < 2U)
    return "false";

  size_t start{};

  while (true) {
    start = str.find_first_of("123456789", start);

    if (string::npos == start)
      return "false";

    size_t last{str.find_first_not_of("0123456789", start + 1)};

    if (string::npos == last)
      last = str.length();

    if (check_if_num_str_consists_of_two_even_numbers(str, start, last))
      return "true";

    start = last + 1;
  }
}

int main() {
  // cout << EvenPairs(gets(stdin));
  cout << EvenPairs("f178svg3k19k46") << '\n';  // expected output: "true"
  cout << EvenPairs("7r5gg812") << '\n';        // expected output: "true"
  cout << EvenPairs("3gy41d216") << '\n';       // expected output: "true"
  cout << EvenPairs("f09r27i8e67") << '\n';     // expected output: "false"

  return 0;
}
