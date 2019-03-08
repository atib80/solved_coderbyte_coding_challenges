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
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <unordered_set>

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

string LetterChanges(string str) {
  str = trim(str);

  const unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};

  for (auto& ch : str) {
    if ((ch >= 'a' && ch < 'z') || (ch >= 'A' && ch < 'Z'))
      ch += 1;
    else if (ch == 'z')
      ch = 'a';
    else if (ch == 'Z')
      ch = 'A';
  }

  const auto& f = use_facet<std::ctype<char>>(locale{});

  transform(cbegin(str), cend(str), begin(str), [&](const char ch) {
    if (vowels.find(ch) != end(vowels))
      return f.toupper(ch);
    return ch;
  });

  return str;
}

int main() {
  // cout << LetterChanges(gets(stdin));
  cout << LetterChanges("hello*3") << '\n';     // expected output: "Ifmmp*3"
  cout << LetterChanges("fun times!") << '\n';  // expected output: "gvO Ujnft!"

  return 0;
}
