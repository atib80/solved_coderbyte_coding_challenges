/*
Coderbyte coding challenge: Letter Capitalize

Using the C++ language, have the function LetterCapitalize(str) take the str
parameter being passed and capitalize the first letter of each word. Words will
be separated by only one space.

Sample test cases:

Input:  "hello world"
Output: "Hello World"

Input:  "i ran there"
Output: "I Ran There"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <type_traits>
#include <unordered_set>

#include <stl_helper_functions.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string LetterCapitalize(string str) {
  str = stl::helper::trim(str);

  bool is_space_char{true};

  const auto& f = use_facet<ctype<char>>(locale{});

  for (auto& ch : str) {
    if (' ' == ch) {
      is_space_char = true;      
    }
    else if (is_space_char) {
      ch = f.toupper(ch);
      is_space_char = false;
    }
  }

  return str;
}

TEST_CASE("Letter Capitalize") {
  REQUIRE(LetterCapitalize("hello world") == "Hello World");
  REQUIRE(LetterCapitalize("i ran there") == "I Ran There");
}

// int main() {
//   // cout << LetterCapitalize(gets(stdin));
//   cout << LetterCapitalize("hello world")
//        << '\n';  // expected output: "Hello World"
//   cout << LetterCapitalize("i ran there")
//        << '\n';  // expected output: "I Ran There"

//   return 0;
// }
