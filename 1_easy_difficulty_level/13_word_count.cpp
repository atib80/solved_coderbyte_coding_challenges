/*
Coderbyte coding challenge: Word Count

Using the C++ language, have the function WordCount(str) take the str string
parameter being passed and return the number of words the string contains (e.g.
"Never eat shredded wheat or cake" would return 6). Words will be separated by
single spaces.

Sample test cases:

Input:  "Hello World"
Output: 2

Input:  "one 22 three"
Output: 3
*/

// #include <iostream>
#include <stl_helper_functions.hpp>
#include <string>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string word_count_v1(string str) {
  str = stl::helper::trim(str);

  const size_t str_len{str.length()};

  size_t word_count{};
  size_t start{};

  while (start < str_len) {
    start = str.find_first_not_of(" \t\n\v\f", start);

    if (string::npos == start)
      break;

    const size_t last{str.find_first_of(" \t\n\v\f", start + 1)};

    if (string::npos == last) {
      word_count++;
      break;
    }

    word_count++;

    start = last + 1;
  }

  return to_string(word_count);
}

string word_count_v2(string str) {
  str = stl::helper::trim(str);

  const vector<string> words{stl::helper::str_split(str, " ", "", true)};

  return to_string(words.size());
}

TEST_CASE("Word Count : word_count_v1") {
  REQUIRE(word_count_v1("Never eat shredded wheat or cake") == "6");
  REQUIRE(word_count_v1("Hello World") == "2");
  REQUIRE(word_count_v1("one 22 three") == "3");
  REQUIRE(word_count_v1("Coderbyte") == "1");
  REQUIRE(word_count_v1("h333llLo") == "1");
  REQUIRE(word_count_v1("Yo0") == "1");
  REQUIRE(word_count_v1("commacomma!") == "1");
  REQUIRE(word_count_v1("aq") == "1");
}

TEST_CASE("Word Count : word_count_v2") {
  REQUIRE(word_count_v2("Never eat shredded wheat or cake") == "6");
  REQUIRE(word_count_v2("Hello World") == "2");
  REQUIRE(word_count_v2("one 22 three") == "3");
  REQUIRE(word_count_v2("Coderbyte") == "1");
  REQUIRE(word_count_v2("h333llLo") == "1");
  REQUIRE(word_count_v2("Yo0") == "1");
  REQUIRE(word_count_v2("commacomma!") == "1");
  REQUIRE(word_count_v2("aq") == "1");
}

// int main() {
//   // cout << word_count_v2(gets(stdin));
//   cout << word_count_v2("Never eat shredded wheat or cake")
//        << '\n';                                   // expected output: 6
//   cout << word_count_v2("Hello World") << '\n';   // expected output: 2
//   cout << word_count_v2("one 22 three") << '\n';  // expected output: 3
//   cout << word_count_v2("Coderbyte") << '\n';     // expected output: 1
//   cout << word_count_v2("h333llLo") << '\n';      // expected output: 1
//   cout << word_count_v2("Yo0") << '\n';           // expected output: 1
//   cout << word_count_v2("commacomma!") << '\n';   // expected output: 1
//   cout << word_count_v2("aq") << '\n';            // expected output: 1

//   return 0;
// }
