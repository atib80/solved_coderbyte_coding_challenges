/*
Coderbyte coding challenge: Vowel Square

Using the C++ language, have the function VowelSquare(strArr) take the strArr
parameter being passed which will be a 2D matrix of some arbitrary size filled
with letters from the alphabet, and determine if a 2x2 square composed entirely
of vowels exists in the matrix. For example: strArr is ["abcd", "eikr", "oufj"]
then this matrix looks like the following:

a b c d
e i k r
o u f j

Within this matrix there is a 2x2 square of vowels starting in the second row
and first column, namely, ei, ou. If a 2x2 square of vowels is found your
program should return the top-left position (row-column) of the square, so for
this example your program should return 1-0. If no 2x2 square of vowels exists,
then return the string not found. If there are multiple squares of vowels,
return the one that is at the most top-left position in the whole matrix. The
input matrix will at least be of size 2x2.

Sample test cases:

Input:  {"aqrst", "ukaei", "ffooo"}
Output: "1-2"

Input:  {"gg", "ff"}
Output: "not found"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

string VowelSquare(string* str_arr, const size_t row_size) {
  const unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};

  for (size_t i{}; i < row_size; i++) {
    str_arr[i] = trim(str_arr[i]);

    for (auto& ch : str_arr[i])
      ch = static_cast<char>(tolower(ch));
  }

  for (size_t i{}; i < row_size - 1; i++) {
    const string& prev_line{str_arr[i]};
    const string& next_line{str_arr[i + 1]};

    for (size_t j{}; j < prev_line.length() - 1; j++) {
      if ((vowels.find(prev_line[j]) != end(vowels)) &&
          (vowels.find(prev_line[j + 1]) != end(vowels)) &&
          (vowels.find(next_line[j]) != end(vowels)) &&
          (vowels.find(next_line[j + 1]) != end(vowels))) {
        return to_string(i) + string{"-"} + to_string(j);
      }
    }
  }

  return "not found";
}

int main() {
  // string a[] = gets(stdin);
  string a[] = {"abcd", "eikr", "oufj"};
  cout << VowelSquare(a, sizeof(a) / sizeof(*a))
       << '\n';  // expected output: "1-0"
  string b[] = {"aqrst", "ukaei", "ffooo"};
  cout << VowelSquare(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: "1-2"
  string c[] = {"gg", "ff"};
  cout << VowelSquare(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: "not found"
  return 0;
}
