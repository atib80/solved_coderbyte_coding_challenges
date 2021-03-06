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
#include <mutex>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return {};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return {};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str]))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string LetterChanges_v1(string str) {
  str = trim(str);

  const unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};

  for (auto& ch : str) {
    if ((ch >= 'a' && ch < 'z') || (ch >= 'A' && ch < 'Z'))
      ++ch;
    else if ('z' == ch || 'Z' == ch)
      ch -= 'z' - 'a';
  }

  const auto& f = use_facet<std::ctype<char>>(locale{});

  transform(cbegin(str), cend(str), begin(str), [&](const char ch) {
    if (vowels.find(ch) != end(vowels))
      return f.toupper(ch);
    return ch;
  });

  return str;
}

struct lookup_table {
  using byte = unsigned char;
  array<byte, 256> offsets;
  array<byte, 256> capitalized_letters;
  static constexpr const byte byte_max_value{numeric_limits<byte>::max()};

  constexpr lookup_table() : offsets{}, capitalized_letters{} {
    for (byte i{}; i < 'A'; i++) {
      offsets[i] = i;
      capitalized_letters[i] = i;
    }
    for (byte i{'Z' + 1}; i < 'a'; i++) {
      offsets[i] = i;
      capitalized_letters[i] = i;
    }
    for (byte i = 'z' + 1; i < byte_max_value; i++) {
      offsets[i] = i;
      capitalized_letters[i] = i;
    }

    for (byte i{'a'}, j{'A'}; i < 'z'; i++, j++) {
      offsets[i] = i + 1;
      offsets[j] = j + 1;
      capitalized_letters[i] = i;
      capitalized_letters[j] = j;
    }

    offsets['Z'] = 'A';
    offsets['z'] = 'a';
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

int main() {
  // cout << LetterChanges(gets(stdin));
  cout << LetterChanges_v2("hello*3") << '\n';  // expected output: "Ifmmp*3"
  cout << LetterChanges_v2("fun times!")
       << '\n';  // expected output: "gvO Ujnft!"

  return 0;
}
