/*
Coderbyte coding challenge: LCS

Using the C++ language, have the function LCS(strArr) take the strArr parameter
being passed which will be an array of two strings containing only the
characters {a,b,c} and have your program return the length of the longest common
subsequence common to both strings. A common subsequence for two strings does
not require each character to occupy consecutive positions within the original
strings. For example: if strArr is ["abcabb","bacb"] then your program should
return 3 because one longest common subsequence for these two strings is "bab"
and there are also other 3-length subsequences such as "acb" and "bcb" but 3 is
the longest common subsequence for these two strings.

Sample test cases:

Input:  "abc","cb"
Output: 1

Input:  "bcacb","aacabb"
Output: 3
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

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

size_t find_longest_common_sequence_v1(const string& left_str,
                                       const string& right_str) {
  size_t lcs{};

  for (size_t i{}; i < left_str.length(); i++) {
    if (left_str.length() - i <= lcs)
      break;

    size_t prev_char_pos{};

    size_t current_lcs{};

    for (size_t j{i}; j < left_str.length(); j++) {
      const size_t next_char_pos{right_str.find(left_str[j], prev_char_pos)};

      if (string::npos == next_char_pos)
        continue;

      prev_char_pos = next_char_pos + 1;

      current_lcs++;
    }

    if (current_lcs > lcs)
      lcs = current_lcs;
  }

  return lcs;
}

string LCS_v1(string* str_arr, const size_t str_arr_size) {
  if (!str_arr || str_arr_size < 2)
    return "not possible";

  str_arr[0] = trim(str_arr[0]);
  str_arr[1] = trim(str_arr[1]);

  if (str_arr[0].empty() || str_arr[1].empty())
    return "not possible";

  return to_string(find_longest_common_sequence_v1(str_arr[0], str_arr[1]));
}

void find_longest_common_sequence_v2(const string& left_str,
                                     const size_t left_str_len,
                                     const size_t pos,
                                     const string& right_str,
                                     size_t& lcs,
                                     size_t prev_char_pos,
                                     const size_t current_lcs = 0) {
  for (size_t i{pos}; i < left_str_len; i++) {
    if (left_str_len - i + current_lcs <= lcs)
      return;

    const size_t next_char_pos{right_str.find(left_str[i], prev_char_pos)};

    if (string::npos != next_char_pos) {
      if (i + 1 < left_str_len)
        find_longest_common_sequence_v2(left_str, left_str_len, i + 1,
                                        right_str, lcs, next_char_pos + 1,
                                        current_lcs + 1);

      else if (current_lcs + 1 > lcs)
        lcs = current_lcs + 1;
    }
  }

  if (current_lcs > lcs)
    lcs = current_lcs;
}

string LCS_v2(string* str_arr, const size_t str_arr_size) {
  if (!str_arr || str_arr_size < 2)
    return "not possible";

  str_arr[0] = trim(str_arr[0]);
  str_arr[1] = trim(str_arr[1]);

  if (str_arr[0].empty() || str_arr[1].empty())
    return "not possible";

  size_t lcs{};
  find_longest_common_sequence_v2(str_arr[0], str_arr[0].length(), 0,
                                  str_arr[1], lcs, 0, 0);
  return to_string(lcs);
}

size_t find_longest_common_sequence_v3(const string& left_str,
                                       const string& right_str) {
  queue<tuple<size_t, size_t, size_t>> q{{make_tuple(0, 0, 0)}};
  const size_t left_str_len{left_str.length()};
  size_t lcs{};

  while (!q.empty()) {
    const size_t pos{get<0>(q.front())};
    const size_t current_lcs{get<1>(q.front())};
    const size_t prev_char_pos{get<2>(q.front())};
    q.pop();

    for (size_t i{pos}; i < left_str_len; i++) {
      if (left_str_len - i + current_lcs <= lcs)
        break;
      const size_t next_char_pos{right_str.find(left_str[i], prev_char_pos)};

      if (string::npos != next_char_pos) {
        if (i + 1 < left_str_len)
          q.emplace(make_tuple(i + 1, current_lcs + 1, next_char_pos + 1));
        else if (current_lcs + 1 > lcs)
          lcs = current_lcs + 1;
      }
    }

    if (current_lcs > lcs)
      lcs = current_lcs;
  }

  return lcs;
}

string LCS_v3(string* str_arr, const size_t str_arr_size) {
  if (!str_arr || str_arr_size < 2)
    return "not possible";

  str_arr[0] = trim(str_arr[0]);
  str_arr[1] = trim(str_arr[1]);

  if (str_arr[0].empty() || str_arr[1].empty())
    return "not possible";

  return to_string(find_longest_common_sequence_v3(str_arr[0], str_arr[1]));
}

int main() {
  // string A[] = gets(stdin);
  // cout << LCS_v1(A, sizeof(A)/sizeof(*A));
  string B[] = {"abcabb", "bacb"};
  cout << LCS_v1(B, sizeof(B) / sizeof(*B)) << '\n';  // expected output: "3"
  string C[] = {"abc", "cb"};
  cout << LCS_v1(C, sizeof(C) / sizeof(*C)) << '\n';  // expected output: "1"
  string D[] = {"bcacb", "aacabb"};
  cout << LCS_v1(D, sizeof(D) / sizeof(*D)) << '\n';  // expected output: "3"
  string E[] = {"a", "a"};
  cout << LCS_v1(E, sizeof(E) / sizeof(*E)) << '\n';  // expected output: "1"
  string F[] = {"aaac", "caaa"};
  cout << LCS_v1(F, sizeof(F) / sizeof(*F)) << '\n';  // expected output: "3"

  return 0;
}
