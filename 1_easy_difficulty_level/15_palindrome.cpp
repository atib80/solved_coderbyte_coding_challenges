/*
Coderbyte coding challenge: Palindrome

Using the C++ language, have the function Palindrome(str) take the str parameter
being passed and return the string true if the parameter is a palindrome, (the
string is the same forward as it is backward) otherwise return the string false.
For example: "racecar" is also "racecar" backwards. Punctuation and numbers will
not be part of the string.

Sample test cases:

Input:  "never odd or even"
Output: "true"

Input:  "eye"
Output: "true"
*/

#include <cctype>
// #include <iostream>
#include <locale>
#include <queue>
#include <stack>
#include <stl_helper_functions.hpp>
#include <string>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string palindrome_v1(string str) {
  str = stl::helper::trim(str);

  if (str.length() < 2)
    return "false";

  deque<char> d{};
  locale loc{};

  for (const char ch : str) {
    if (isspace(ch, loc))
      continue;
    d.push_back(ch);
  }

  while (d.size() > 1) {
    if (d.front() != d.back())
      return "false";
    d.pop_back();
    d.pop_front();
  }

  return "true";
}

string palindrome_v2(string str) {
  str = stl::helper::trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2)
    return "false";

  size_t i{}, j{str_len - 1};
  locale loc{};

  while (i < j) {
    if (!isalpha(str[i], loc)) {
      i++;
      continue;
    }

    if (!isalpha(str[j], loc)) {
      j--;
      continue;
    }

    if (str[i] != str[j])
      return "false";

    i++;
    j--;
  }

  return "true";
}

string palindrome_v3(string str) {
  str = stl::helper::trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2U)
    return "false";

  string str_no_spaces{};
  str_no_spaces.reserve(str_len);
  locale loc{};

  for (const char ch : str) {
    if (isalpha(ch, loc))
      str_no_spaces.push_back(ch);
  }

  for (size_t i{}, j{str_no_spaces.length() - 1}; i < j; ++i, --j) {
    if (str_no_spaces[i] != str_no_spaces[j])
      return "false";
  }

  return "true";
}

TEST_CASE("Palindrome : std::string palindrome_v1(std::string)") {
  REQUIRE(palindrome_v1("racecar") == "true");
  REQUIRE(palindrome_v1("never odd or even") == "true");
  REQUIRE(palindrome_v1("eye") == "true");
  REQUIRE(palindrome_v1("apple") == "false");
  REQUIRE(palindrome_v1("rotor") == "true");
}

TEST_CASE("Palindrome : std::string palindrome_v2(std::string)") {
  REQUIRE(palindrome_v2("racecar") == "true");
  REQUIRE(palindrome_v2("never odd or even") == "true");
  REQUIRE(palindrome_v2("eye") == "true");
  REQUIRE(palindrome_v2("apple") == "false");
  REQUIRE(palindrome_v2("rotor") == "true");
}

TEST_CASE("Palindrome : std::string palindrome_v3(std::string)") {
  REQUIRE(palindrome_v3("racecar") == "true");
  REQUIRE(palindrome_v3("never odd or even") == "true");
  REQUIRE(palindrome_v3("eye") == "true");
  REQUIRE(palindrome_v3("apple") == "false");
  REQUIRE(palindrome_v3("rotor") == "true");
}

// int main() {
//   // cout << palindrome_v1(gets(stdin));
//   cout << palindrome_v1("racecar") << '\n';  // expected output: "true"
//   cout << palindrome_v1("never odd or even")
//        << '\n';                            // expected output: "true"
//   cout << palindrome_v1("eye") << '\n';    // expected output: "true"
//   cout << palindrome_v1("apple") << '\n';  // expected output: "false"
//   cout << palindrome_v1("rotor") << '\n';  // expected output: "true"

//   return 0;
// }
