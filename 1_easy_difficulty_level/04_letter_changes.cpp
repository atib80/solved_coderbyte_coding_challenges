/*
Coderbyte coding challenge: Letter Changes

Using the C++ language, have the function LetterChanges(str) take the str
parameter being passed and modify it using the following algorithm. Replace
every letter in the string with the letter following it in the alphabet (ie. c
becomes d, z becomes a). Then capitalize every vowel in this new string (a, e,
i, o, u) and finally return this modified string.

Sample test cases:

Input:  "hello*3"
Output: "Ifmmp*3"

Input:  "fun times!"
Output: "gvO Ujnft!"
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_set>

#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN

using namespace std;

string trim(const string& str) {
  const size_t first = str.find_first_not_of(" \t\n\f\v ");
  const size_t last = str.find_last_not_of(" \t\n\f\v ") + 1;
  return first != string::npos ? string{cbegin(str) + first, cbegin(str) + last}
                               : string{};
}

string LetterChanges_v1(string str) {
  str = trim(str);

  const unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
  const auto& f = use_facet<std::ctype<char>>(locale{});

  for (auto& ch : str) {
    if ((ch >= 'a' && ch < 'z') || (ch >= 'A' && ch < 'Z')) {
      ++ch;
      if (0u != vowels.count(ch)) {
        ch = f.toupper(ch);
      }
    } else if ('z' == ch || 'Z' == ch) {
      ch = 'A';
    }
  }

  return str;
}

struct lookup_table {
  using byte = unsigned char;
  array<byte, 256> offsets;
  array<byte, 256> capitalized_letters;
  static constexpr byte byte_max_value{numeric_limits<byte>::max()};

  constexpr lookup_table() : offsets{}, capitalized_letters{} {
    for (byte i{}; i < 'A'; ++i) {
      offsets[i] = i;
      capitalized_letters[i] = i;
    }
    for (byte i{'Z' + 1}; i < 'a'; ++i) {
      offsets[i] = i;
      capitalized_letters[i] = i;
    }
    for (byte i = 'z' + 1; i < byte_max_value; ++i) {
      offsets[i] = i;
      capitalized_letters[i] = i;
    }

    for (byte i{'a'}, j{'A'}; i < 'z'; ++i, ++j) {
      offsets[i] = i + 1;
      offsets[j] = j + 1;
      capitalized_letters[i] = i;
      capitalized_letters[j] = j;
    }

    offsets['z'] = 'a';
    offsets['Z'] = 'A';
    capitalized_letters['a'] = 'A';
    capitalized_letters['e'] = 'E';
    capitalized_letters['i'] = 'I';
    capitalized_letters['o'] = 'O';
    capitalized_letters['u'] = 'U';
  }

  constexpr pair<byte, byte> operator[](const size_t index) const {
    if (index > byte_max_value) {
      char buffer[128]{};
      _snprintf(buffer, 128, "index's value must be between 0 and %u!",
                byte_max_value);
      throw out_of_range{buffer};
    }

    return {offsets[index], capitalized_letters[index]};
  }
};

static constexpr lookup_table lu{};

string LetterChanges_v2(string str) {
  str = trim(str);

  for (auto& ch : str) {
    ch = lu[ch].first;
    ch = lu[ch].second;
  }

  return str;
}

TEST_CASE("Letter Changes : LetterChanges_v1") {
  REQUIRE(LetterChanges_v1("hello*3") == "Ifmmp*3");
  REQUIRE(LetterChanges_v1("fun times!") == "gvO Ujnft!");
}

TEST_CASE("Letter Changes : LetterChanges_v2") {
  REQUIRE(LetterChanges_v2("hello*3") == "Ifmmp*3");
  REQUIRE(LetterChanges_v2("fun times!") == "gvO Ujnft!");
}

// int main() {
//   // cout << LetterChanges_v1(gets(stdin));
//   cout << LetterChanges_v1("hello*3") << '\n';  // expected output: "Ifmmp*3"
//   cout << LetterChanges_v1("fun times!")
//        << '\n';  // expected output: "gvO Ujnft!"
//
//   return 0;
// }
