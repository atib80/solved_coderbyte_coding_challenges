/*
Coderbyte coding challenge: Simple Symbols

Using the C++ language, have the function SimpleSymbols(str) take the str
parameter being passed and determine if it is an acceptable sequence by either
returning the string true or false. The str parameter will be composed of + and
= symbols with several letters between them (ie. ++d+===+c++==a) and for the
string to be true each letter must be surrounded by a + symbol. So the string to
the left would be false. The string will not be empty and will have at least one
letter.

Sample test cases:

Input:  "+d+=3=+s+"
Output: "true"

Input:  "f++d+"
Output: "false"
*/

// #include <iostream>
#include <cctype>
#include <string>
#include <stack>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string trim(const string& str) {
  const size_t first = str.find_first_not_of(" \t\n\f\v ");
  const size_t last = str.find_last_not_of(" \t\n\f\v ") + 1;
  return first != string::npos ? string{cbegin(str) + first, cbegin(str) + last} : string{};
}

string SimpleSymbols_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len)
    return "true";

  if (isalpha(str.front()) || isalpha(str.back()))
    return "false";

  if (str_len < 3U)
    return "true";

  for (size_t i{}; i < str_len - 2; ++i) {
    if (str[i] == '+') {
      if (isalpha(str[i + 1])) {
        if (str[i + 2] == '+') {
          ++i;
          continue;
        }
        return "false";
      }

    } else if ('=' == str[i] && isalpha(str[i + 1]))
      return "false";
  }

  return "true";
}

string SimpleSymbols_v2(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len)
    return "true";

  if (isalpha(str.front()) || isalpha(str.back()))
    return "false";

  if (str_len < 3U)
    return "true";

  for (size_t i{1}; i < str_len - 1; ++i) {
    if (isalpha(str[i])) {
      if (!('+' == str[i - 1] && '+' == str[i + 1]))
        return "false";
      ++i;
    }
  }

  return "true";
}

string SimpleSymbols_v3(string str) {
  stack<char> s;

  for (const char ch : str) {
    if (isalpha(ch) && (s.empty() || s.top() != '+')) return "false";

    if (ch != '+' && !s.empty() && isalpha(s.top())) return "false";

    s.push(ch);

    }  

  return "true";
}

TEST_CASE("Simple Symbols : SimpleSymbols_v1") {

  REQUIRE(SimpleSymbols_v1("++d+===+c++==a") == "false");
  REQUIRE(SimpleSymbols_v1("+d+=3=+s+") == "true");
  REQUIRE(SimpleSymbols_v1("f++d+") == "false");

}

TEST_CASE("Simple Symbols : SimpleSymbols_v2") {

  REQUIRE(SimpleSymbols_v2("++d+===+c++==a") == "false");
  REQUIRE(SimpleSymbols_v2("+d+=3=+s+") == "true");
  REQUIRE(SimpleSymbols_v2("f++d+") == "false");
    
}

TEST_CASE("Simple Symbols : SimpleSymbols_v3") {

  REQUIRE(SimpleSymbols_v3("++d+===+c++==a") == "false");
  REQUIRE(SimpleSymbols_v3("+d+=3=+s+") == "true");
  REQUIRE(SimpleSymbols_v3("f++d+") == "false");
    
}

// int main() {
//   // cout << SimpleSymbols_v2(gets(stdin));
//   cout << SimpleSymbols_v2("++d+===+c++==a")
//        << '\n';                                   // expected output: "false"
//   cout << SimpleSymbols_v2("+d+=3=+s+") << '\n';  // expected output: "true"
//   cout << SimpleSymbols_v2("f++d+") << '\n';      // expected output: "false"

//   return 0;
// }
