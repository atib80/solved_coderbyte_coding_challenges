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
#include <string>

#include <stl_helper_functions.hpp>
#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN

using namespace std;
// using namespace string_literals;

string FirstReverse_v1(string str) {
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

TEST_CASE("First Reverse: FirstReverse_v1") {
  REQUIRE(FirstReverse_v1("Hello World and Coders") == "sredoC dna dlroW olleH");
  REQUIRE(FirstReverse_v1("coderbyte") == "etybredoc");
  REQUIRE(FirstReverse_v1("I Love Code") == "edoC evoL I");
}

TEST_CASE("First Reverse: FirstReverse_v2") {
  REQUIRE(FirstReverse_v2("Hello World and Coders") == "sredoC dna dlroW olleH");
  REQUIRE(FirstReverse_v2("coderbyte") == "etybredoc");
  REQUIRE(FirstReverse_v2("I Love Code") == "edoC evoL I");
}

//int main() {
//  // cout << FirstReverse_v1(gets(stdin));
//  cout << FirstReverse_v1("Hello World and Coders")
//       << '\n';  // expected output: "sredoC dna dlroW olleH"
//  cout << FirstReverse_v1("coderbyte") << '\n';  // expected output: "etybredoc"
//  cout << FirstReverse_v1("I Love Code")
//       << '\n';  // expected output: "edoC evoL I"
//
//  return 0;
//}
