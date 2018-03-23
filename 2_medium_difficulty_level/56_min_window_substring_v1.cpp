/*
Coderbyte coding challenge: Min Window Substring v1
(iterative solution implemented by using unordered_multiset<char>)

Using the C++ language, have the function MinWindowSubstring(strArr) take the
array of strings stored in strArr, which will contain only two strings, the
first parameter being the string N and the second parameter being a string K of
some characters, and your goal is to determine the smallest substring of N that
contains all the characters in K. For example: if strArr is ["aaabaaddae",
"aed"] then the smallest substring of N that contains the characters a, e, and d
is "dae" located at the end of the string. So for this example your program
should return the string dae.

Another example: if strArr is ["aabdccdbcacd", "aad"] then the smallest
substring of N that contains all of the characters in K is "aabd" which is
located at the beginning of the string. Both parameters will be strings ranging
in length from 2 to 50 characters and all of K's characters will exist somewhere
in the string N. Both strings will only contains lowercase alphabetic
characters.

Sample test cases:

Input:  "ahffaksfajeeubsne", "jefaa"
Output: "aksfaje"

Input:  "aaffhkksemckelloe", "fhea"
Output: "affhkkse"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
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

string MinWindowSubstring_v2(const string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 2)
    return string{
        "string str_arr[] must contain at least 2 elements (source and needle "
        "string)!"};

  const string source_str{trim(str_arr[0])};
  const size_t src_len{source_str.length()};

  string needle_str{trim(str_arr[1])};
  const size_t needle_len{needle_str.length()};

  if (string::npos != source_str.find(needle_str))
    return needle_str;

  const unordered_multiset<char> needle_chars(begin(needle_str),
                                              end(needle_str));

  size_t current_substr_len{needle_len};

  while (current_substr_len <= src_len) {
    unordered_multiset<char> source_chars(
        begin(source_str), begin(source_str) + current_substr_len);

    if (all_of(begin(needle_chars), end(needle_chars), [&](const char ch) {
          return source_chars.count(ch) >= needle_chars.count(ch);
        }))
      return source_str.substr(0, current_substr_len);

    for (size_t offset{1}; offset + current_substr_len <= src_len; offset++) {
      source_chars.erase(source_chars.find(source_str[offset - 1]));
      source_chars.insert(source_str[offset + current_substr_len - 1]);

      if (all_of(begin(needle_chars), end(needle_chars), [&](const char ch) {
            return source_chars.count(ch) >= needle_chars.count(ch);
          }))
        return source_str.substr(offset, current_substr_len);
    }

    current_substr_len++;
  }

  return "not possible";
}

int main() {
  // string A[] = gets(stdin);
  // cout << MinWindowSubstring_v2(A, sizeof(A)/sizeof(*A));
  string B[] = {"aaabaaddae", "aed"};
  cout << MinWindowSubstring_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "dae"
  string C[] = {"aabdccdbcacd", "aad"};
  cout << MinWindowSubstring_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "aabd"
  string D[] = {"ahffaksfajeeubsne", "jefaa"};
  cout << MinWindowSubstring_v2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "aksfaje"
  string E[] = {"aaffhkksemckelloe", "fhea"};
  cout << MinWindowSubstring_v2(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "affhkkse"

  return 0;
}
