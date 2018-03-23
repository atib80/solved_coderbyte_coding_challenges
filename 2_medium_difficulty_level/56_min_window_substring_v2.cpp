/*
Coderbyte coding challenge: Min Window Substring v2
(alternative iterative solution implemented by using brute-force method with the
help of std::next_permutation)

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

size_t calculate_min_substring_length(const string& src,
                                      const size_t src_substr_offset,
                                      const size_t src_substr_len,
                                      const string& needle_str) {
  size_t min_index{string::npos};

  for (size_t i{src_substr_offset}; i < src_substr_offset + src_substr_len;
       i++) {
    if (needle_str.front() == src[i]) {
      min_index = i;
      break;
    }
  }

  if (string::npos == min_index)
    return string::npos;

  size_t max_index{string::npos}, prev_index{min_index};

  for (size_t i{1}; i < needle_str.length(); i++) {
    max_index = string::npos;
    for (size_t j{prev_index + 1}; j < src_substr_offset + src_substr_len;
         j++) {
      if (needle_str[i] == src[j]) {
        max_index = j;
        break;
      }
    }

    if (string::npos == max_index)
      return string::npos;

    prev_index = max_index;
  }

  return (max_index - min_index + 1);
}

string MinWindowSubstring_v2(string* str_arr, const size_t str_arr_size) {
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

  sort(begin(needle_str), end(needle_str));

  size_t min_substr_len{string::npos};

  string found_substr{};

  do {
    size_t current_substr_len{needle_len};

    const size_t min_start_offset{source_str.find(needle_str.front())};

    size_t current_substr_offset{min_start_offset};

    while (current_substr_offset + current_substr_len <= src_len) {
      const size_t current_min_substr_len{calculate_min_substring_length(
          source_str, current_substr_offset, current_substr_len, needle_str)};

      if (current_min_substr_len != string::npos &&
          current_min_substr_len < min_substr_len) {
        min_substr_len = current_min_substr_len;
        found_substr =
            source_str.substr(current_substr_offset, current_substr_len);
        if (needle_len == min_substr_len)
          return found_substr;
      }

      current_substr_offset++;

      if (current_substr_offset + current_substr_len > src_len) {
        current_substr_len++;
        current_substr_offset = min_start_offset;
      }
    }

  } while (next_permutation(begin(needle_str), end(needle_str)));

  if (found_substr.empty())
    return "not possible";

  return found_substr;
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
