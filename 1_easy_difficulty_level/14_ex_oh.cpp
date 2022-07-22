/*
Coderbyte coding challenge: Ex Oh

Using the C++ language, have the function ExOh(str) take the str parameter being
passed and return the string true if there is an equal number of x's and o's,
otherwise return the string false. Only these two letters will be entered in the
string, no punctuation or numbers. For example: if str is "xooxxxxooxo" then the
output should return false because there are 6 x's and 5 o's.

Sample test cases:

Input:  "xooxxo"
Output: "true"

Input:  "x"
Output: "false"
*/

#include <algorithm>
// #include <iostream>
#include <stl_helper_functions.hpp>
#include <string>
#include <unordered_set>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string ex_oh_v1(string str) {
  str = stl::helper::trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len || str_len % 2 == 1)
    return "false";

  static size_t char_count[128];
  char_count['o'] = 0U;
  char_count['x'] = 0U;

  for (const char ch : str)
    ++char_count[static_cast<size_t>(ch)];

  if (char_count['o'] == char_count['x'])
    return "true";
  return "false";
}

string ex_oh_v2(string str) {
  str = stl::helper::trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len || str_len % 2 == 1)
    return "false";

  int balance{};
  for (const char ch : str)
    balance += (ch == 'o') ? -1 : 1;

  if (0 != balance)
    return "false";

  return "true";
}

string ex_oh_v3(string str) {
  str = stl::helper::trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len || str_len % 2 == 1)
    return "false";

  unordered_multiset<char> char_freq{cbegin(str), cend(str)};

  if (char_freq.count('o') != char_freq.count('x'))
    return "false";

  return "true";
}

string ex_oh_v4(string str) {
  str = stl::helper::trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len || str_len % 2 == 1)
    return "false";

  sort(begin(str), end(str));

  if (str[str_len / 2 - 1] != 'o' && str[str_len / 2] != 'x')
    return "false";

  return "true";
}

TEST_CASE("Ex Oh : ex_oh_v1()") {
  REQUIRE(ex_oh_v1("xooxxxxooxo") == "false");
  REQUIRE(ex_oh_v1("xooxxo") == "true");
  REQUIRE(ex_oh_v1("x") == "false");
}

TEST_CASE("Ex Oh : ex_oh_v2()") {
  REQUIRE(ex_oh_v2("xooxxxxooxo") == "false");
  REQUIRE(ex_oh_v2("xooxxo") == "true");
  REQUIRE(ex_oh_v2("x") == "false");
}

TEST_CASE("Ex Oh : ex_oh_v3()") {
  REQUIRE(ex_oh_v3("xooxxxxooxo") == "false");
  REQUIRE(ex_oh_v3("xooxxo") == "true");
  REQUIRE(ex_oh_v3("x") == "false");
}

TEST_CASE("Ex Oh : ex_oh_v4()") {
  REQUIRE(ex_oh_v4("xooxxxxooxo") == "false");
  REQUIRE(ex_oh_v4("xooxxo") == "true");
  REQUIRE(ex_oh_v4("x") == "false");
}

// int main() {
//   // cout << ex_oh_v1(gets(stdin));
//   cout << ex_oh_v1("xooxxxxooxo") << '\n';  // expected output: "false"
//   cout << ex_oh_v1("xooxxo") << '\n';       // expected output: "true"
//   cout << ex_oh_v1("x") << '\n';            // expected output: "false"

//   return 0;
// }
