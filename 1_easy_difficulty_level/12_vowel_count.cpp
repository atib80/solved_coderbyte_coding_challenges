/*
Coderbyte coding challenge: Vowel Count

Using the C++ language, have the function VowelCount(str) take the str string
parameter being passed and return the number of vowels the string contains (ie.
"All cows eat grass and moo" would return 8). Do not count y as a vowel for this
challenge.

Sample test cases:

Input:  "hello"
Output: 2

Input:  "coderbyte"
Output: 3
*/

#include <array>
// #include <iostream>
#include <string>
#include <unordered_set>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string vowel_count_v1(string str) {
  const unordered_set<char> vowels{'A', 'E', 'I', 'O', 'U',
                                   'a', 'e', 'i', 'o', 'u'};

  size_t v_count{};

  for (const auto ch : str) {
    if (vowels.count(ch) != 0)
      ++v_count;
  }

  return to_string(v_count);
}

template <size_t BUFFER_LENGTH>
class vowel_indices {
  int vowels[BUFFER_LENGTH];

 public:
  constexpr vowel_indices() : vowels{} {
    for (const char index : "aeiouAEIOU")
      vowels[static_cast<size_t>(index)] = 1;
  }

  int operator[](const size_t index) const {
    if (index < BUFFER_LENGTH)
      return vowels[index];
    static char buffer[128];
    snprintf(buffer, 128, "index's value must be between 0 and %llu!",
             BUFFER_LENGTH);
    throw out_of_range{buffer};
  }
};

static constexpr vowel_indices<128> char_dict{};

string vowel_count_v2(string str) {
  size_t v_count{};

  for (const auto ch : str) {
    if (char_dict[ch])
      ++v_count;
  }

  return to_string(v_count);
}

TEST_CASE("Vowel Count : vowel_count_v1") {
  REQUIRE(vowel_count_v1("All cows eat grass and moo") == "8");
  REQUIRE(vowel_count_v1("hello") == "2");
  REQUIRE(vowel_count_v1("coderbyte") == "3");
  REQUIRE(vowel_count_v1("Today is a perfect day for taking a long walk and "
                         "finding a good spot for swimming.") == "23");
}

TEST_CASE("Vowel Count : vowel_count_v2") {
  REQUIRE(vowel_count_v2("All cows eat grass and moo") == "8");
  REQUIRE(vowel_count_v2("hello") == "2");
  REQUIRE(vowel_count_v2("coderbyte") == "3");
  REQUIRE(vowel_count_v2("Today is a perfect day for taking a long walk and "
                         "finding a good spot for swimming.") == "23");
}

// int main() {
//   // cout << vowel_count_v2(gets(stdin));
//   cout << vowel_count_v2("All cows eat grass and moo")
//        << '\n';                                 // expected output: 8
//   cout << vowel_count_v2("hello") << '\n';      // expected output: 2
//   cout << vowel_count_v2("coderbyte") << '\n';  // expected output: 3
//   cout << vowel_count_v2(
//               "Today is a perfect day for taking a long walk and finding a "
//               "good spot for swimming.")
//        << '\n';  // expected output: 23

//   return 0;
// }
