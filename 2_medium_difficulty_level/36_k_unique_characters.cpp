/*
Coderbyte coding challenge: K Unique Characters

Using the C++ language, have the function KUniqueCharacters(str) take the str
parameter being passed and find the longest substring that contains k unique
characters, where k will be the first character from the string. The substring
will start from the second position in the string because the first character
will be the integer k. For example: if str is "2aabbacbaa" there are several
substrings that all contain 2 unique characters, namely: ["aabba", "ac", "cb",
"ba"], but your program should return "aabba" because it is the longest
substring. If there are multiple longest substrings, then return the first
substring encountered with the longest length. k will range from 1 to 6.

Sample test cases:

Input:  "3aabacbebebe"
Output: "cbebebe"

Input:  "2aabbcbbbadef"
Output: "bbcbbb"
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

string KUniqueCharacters_v1(string str) {
  const size_t k{static_cast<size_t>(str[0] - '0')};

  str = trim(str);

  const size_t str_len{str.length()};

  size_t current_substr_len{str_len - 1};

  while (current_substr_len >= k) {
    for (size_t i{1}; i + current_substr_len <= str_len; i++) {
      unordered_set<char> found_chars(begin(str) + i,
                                      begin(str) + i + current_substr_len);

      if (k == found_chars.size())
        return str.substr(i, current_substr_len);
    }

    current_substr_len--;
  }

  ostringstream oss{};

  oss << "Could not find sub-string with " << k << " unique characters!";
  return oss.str();
}

string KUniqueCharacters_v2(string str) {
  
  const size_t k{static_cast<size_t>(str[0] - '0')};

  str = trim(str);

  const size_t str_len{str.length()};

  size_t current_substr_len{str_len - 1};

  while (current_substr_len >= k) {
    unordered_map<char, size_t> char_freq{};

    for (size_t i{1}; i <= current_substr_len; i++)
      char_freq[str[i]]++;

    for (size_t i{1}; i + current_substr_len <= str_len; i++) {
      if (i > 1) {
        char_freq[str[i - 1]]--;
        if (0 == char_freq[str[i - 1]])
          char_freq.erase(str[i - 1]);

        char_freq[str[i + current_substr_len - 1]]++;
      }

      if (k == char_freq.size())
        return str.substr(i, current_substr_len);
    }

    current_substr_len--;
  }

  ostringstream oss{};

  oss << "Could not find sub-string with " << k << " unique characters!";
  return oss.str();
}

int main() {
  // cout << KUniqueCharacters_v2(move(string{gets(stdin)}));
  cout << KUniqueCharacters_v2(move(string{"2aabbacbaa"}))
       << '\n';  // expected output: "aabba"
  cout << KUniqueCharacters_v2(move(string{"3aabacbebebe"}))
       << '\n';  // expected output: "cbebebe"
  cout << KUniqueCharacters_v2(move(string{"2aabbcbbbadef"}))
       << '\n';  // expected output: "bbcbbb"

  return 0;
}
