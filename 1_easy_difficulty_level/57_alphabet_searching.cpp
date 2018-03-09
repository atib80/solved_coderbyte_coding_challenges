/*
Coderbyte coding challenge: Alphabet Searching

Using the C++ language, have the function AlphabetSearching(str) take the str
parameter being passed and return the string true if every single letter of the
English alphabet exists in the string, otherwise return the string false. For
example: if str is "zacxyjbbkfgtbhdaielqrm45pnsowtuv" then your program should
return the string true because every character in the alphabet exists in this
string even though some characters appear more than once.

Sample test cases:

Input:  "abcdefghijklmnopqrstuvwxyyyy"
Output: "false"

Input:  "abc123456kmo"
Output: "false"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(rbegin(output), rend(output),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.length()};

  if (!source_len)
    return parts;

  if (!needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if ((string::npos != max_count) && (parts.size() == max_count))
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if ((string::npos != max_count) && (parts.size() < max_count))
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

string AlphabetSearching_v1(string str) {
  str = trim(str);

  unordered_set<char> found_characters{};

  for (char& ch : str) {
    ch = static_cast<char>(tolower(ch));
    if (ch >= 'a' && ch <= 'z') {
      found_characters.insert(ch);
      if (26 == found_characters.size())
        return "true";
    }
  }

  return "false";
}

string AlphabetSearching_v2(string str) {
  str = trim(str);

  for (char& ch : str)
    ch = static_cast<char>(tolower(ch));

  unordered_map<char, size_t> dict{};

  for (char start{'a'}; start <= 'z'; start++)
    dict.insert(make_pair(start, 0));

  for (const char ch : str) {
    if (dict.find(ch) != end(dict))
      dict[ch]++;
  }

  for (const pair<char, size_t>& char_freq : dict) {
    if (!char_freq.second)
      return "false";
  }

  return "true";
}

string AlphabetSearching_v3(string str) {
  str = trim(str);
  sort(begin(str), end(str));
  const size_t first_char_pos{str.find_first_of("abcdefghijklmnopqrstuvwxyz")};
  const size_t last_char_pos{str.find_last_of("abcdefghijklmnopqrstuvwxyz")};
  unordered_set<char> unique_characters(begin(str) + first_char_pos,
                                        begin(str) + last_char_pos + 1);
  return (26 == unique_characters.size() ? "true" : "false");
}

int main() {
  // cout << AlphabetSearching_v3(move(string{gets(stdin)}));
  cout << AlphabetSearching_v3(move(string{"zacxyjbbkfgtbhdaielqrm45pnsowtuv"}))
       << '\n';  // "true"
  cout << AlphabetSearching_v3(move(string{"abcdefghijklmnopqrstuvwxyyyy"}))
       << '\n';  // "false"
  cout << AlphabetSearching_v3(move(string{"abc123456kmo"}))
       << '\n';  // "false"

  return 0;
}
