/*
Coderbyte coding challenge: AB Check (v1, v2)

Using the C++ language, have the function ABCheck(str) take the str parameter
being passed and return the string true if the characters a and b are separated
by exactly 3 places anywhere in the string at least once (ie. "lane borrowed"
would result in true because there is exactly three characters between a and b).
Otherwise return the string false.

Sample test cases:

Input:  "after badly"
Output: "false"

Input:  "Laura sobs"
Output: "true"
*/

#include <algorithm>
#include <cctype>
#include <cmath>
// #include <iostream>
#include <locale>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

#include <stl_helper_functions.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string ABCheck_v1(string str) {
  str = stl::helper::trim(str);

  const int str_len = str.length();

  for (int i{}, j{str_len - 1}; i < str_len - 4 && j > 3 && i < j; i++, j--) {
    if (('a' == str[i] && 'b' == str[i + 4]) ||
        ('b' == str[i] && 'a' == str[i + 4]) ||
        ('a' == str[j] && 'b' == str[j - 4]) ||
        ('b' == str[j] && 'a' == str[j - 4]))
      return "true";
  }

  return "false";
}

string ABCheck_v2(string str) {
  str = stl::helper::trim(str);

  size_t start{str.find_first_of("ab")};

  if (string::npos == start)
    return "false";

  while (true) {
    const char prev_char{str[start]};

    const size_t next_char_pos{str.find_first_of("ab", start + 1)};

    if (string::npos == next_char_pos)
      return "false";

    if (prev_char != str[next_char_pos] && next_char_pos - start == 4)
      return "true";

    start = next_char_pos;
  }
}

TEST_CASE("AB Check : ABCheck_v1") {
  REQUIRE(ABCheck_v1("ab") == "false");
  REQUIRE(ABCheck_v1("a-b") == "false");
  REQUIRE(ABCheck_v1("a--b") == "false");
  REQUIRE(ABCheck_v1("a---b") == "true");
  REQUIRE(ABCheck_v1("lane borrowed") == "true");
  REQUIRE(ABCheck_v1("after badly") == "false");
  REQUIRE(ABCheck_v1("Laura sobs") == "true");
}

TEST_CASE("AB Check : ABCheck_v2") {
  REQUIRE(ABCheck_v2("ab") == "false");
  REQUIRE(ABCheck_v2("a-b") == "false");
  REQUIRE(ABCheck_v2("a--b") == "false");
  REQUIRE(ABCheck_v2("a---b") == "true");
  REQUIRE(ABCheck_v2("lane borrowed") == "true");
  REQUIRE(ABCheck_v2("after badly") == "false");
  REQUIRE(ABCheck_v2("Laura sobs") == "true");
}

// int main() {
//   // cout << ABCheck_v1(gets(stdin));
//   cout << ABCheck_v1("ab") << '\n';             // expected output: "false"
//   cout << ABCheck_v1("a-b") << '\n';            // expected output: "false"
//   cout << ABCheck_v1("a--b") << '\n';           // expected output: "false"
//   cout << ABCheck_v1("a---b") << '\n';          // expected output: "true"
//   cout << ABCheck_v1("lane borrowed") << '\n';  // expected output: "true"
//   cout << ABCheck_v1("after badly") << '\n';    // expected output: "false"
//   cout << ABCheck_v1("Laura sobs") << '\n';     // expected output: "true"
//   return 0;
// }
