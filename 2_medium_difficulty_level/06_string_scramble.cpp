/*
Coderbyte coding challenge: String Scramble

Using the C++ language, have the function StringScramble(str1,str2) take both
parameters being passed and return the string true if a portion of str1
characters can be rearranged to match str2, otherwise return the string false.
For example: if str1 is "rkqodlw" and str2 is "world" the output should return
true. Punctuation and symbols will not be entered with the parameters.

Sample test cases:

Input:  "cdore" & str2= "coder"
Output: "true"

Input:  "h3llko" & str2 = "hello"
Output: "false"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

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

string StringScramble_v1(string str1, string str2) {
  str1 = trim(str1);
  str2 = trim(str2);

  sort(begin(str1), end(str1));
  sort(begin(str2), end(str2));

  string intersection{};

  set_intersection(begin(str1), end(str1), begin(str2), end(str2),
                   back_inserter(intersection));

  if (intersection.length() == str2.length())
    return "true";

  return "false";
}

string StringScramble_v2(string str1, string str2) {
  str1 = trim(str1);
  str2 = trim(str2);

  unordered_map<char, size_t> str1_char_count{};
  unordered_map<char, size_t> str2_char_count{};

  for (const char c : str1)
    str1_char_count[c]++;
  for (const char c : str2)
    str2_char_count[c]++;

  for (const auto& ch_count : str2_char_count) {
    if (str1_char_count.find(ch_count.first) == end(str1_char_count))
      return "false";

    if (str1_char_count[ch_count.first] < ch_count.second)
      return "false";
  }

  return "true";
}

string StringScramble_v3(string str1, string str2) {
  str1 = trim(str1);
  str2 = trim(str2);

  unordered_map<char, size_t> str1_char_freq{};

  for (const char c : str1)
    str1_char_freq[c]++;

  for (const char c : str2) {
    if (str1_char_freq.find(c) == end(str1_char_freq) || !str1_char_freq[c])
      return "false";

    str1_char_freq[c]--;
  }

  return "true";
}

int main() {
  // cout << StringScramble_v3(gets(stdin));
  cout << StringScramble_v3(move(string{"rkqodlw"}), move(string{"world"}))
       << '\n';  // expected output: "true"
  cout << StringScramble_v3(move(string{"cdore"}), move(string{"coder"}))
       << '\n';  // expected output: "true"
  cout << StringScramble_v3(move(string{"h3llko"}), move(string{"hello"}))
       << '\n';  // expected output: "false"
  cout << StringScramble_v3(move(string{"abcgggdfe"}), move(string{"abcdef"}))
       << '\n';  // expected output: "true"
  cout << StringScramble_v3(move(string{"aqwe"}), move(string{"qa"}))
       << '\n';  // expected output: "true"
  cout << StringScramble_v3(move(string{"yelowrqwedlk"}),
                            move(string{"yellowred"}))
       << '\n';  // expected output: "true"

  return 0;
}
