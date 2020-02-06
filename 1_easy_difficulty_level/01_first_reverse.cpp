/*
Coderbyte coding challenge: First Reverse

Using the C++ language, have the function FirstReverse(str) take the str
parameter being passed and return the string in reversed order. For example: if
the input string is "Hello World and Coders" then your program should return the
string sredoC dna dlroW olleH.

Sample test cases:

Input:  "coderbyte"
Output: "etybredoc"

Input:  "I Love Code"
Output: "edoC evoL I"
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <unordered_set>

#include "../include/stl_helper_functions.hpp"

using namespace std;

string FirstReverse(string str) {
  str = stl::helper::trim(str);
  const size_t str_len{str.length()};

  if (str_len < 2u)
    return str;

  for (size_t i{}; i < str_len / 2; i++)
    swap(str[i], str[str_len - 1 - i]);

  return str;
}

string FirstReverse_v2(string str) {
  str = stl::helper::trim(str);
  reverse(begin(str), end(str));

  return str;
}

int main() {
  // cout << FirstReverse(gets(stdin));
  cout << FirstReverse("Hello World and Coders")
       << '\n';  // expected output: "sredoC dna dlroW olleH"
  cout << FirstReverse("coderbyte") << '\n';  // expected output: "etybredoc"
  cout << FirstReverse("I Love Code")
       << '\n';  // expected output: "edoC evoL I"

  return 0;
}
