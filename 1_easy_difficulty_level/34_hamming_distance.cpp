/*
Coderbyte coding challenge: Hamming Distance

Using the C++ language, have the function HammingDistance(strArr) take the array
of strings stored in strArr, which will only contain two strings of equal length
and return the Hamming distance between them. The Hamming distance is the number
of positions where the corresponding characters are different. For example: if
strArr is ["coder", "codec"] then your program should return 1. The string will
always be of equal length and will only contain lowercase characters from the
alphabet and numbers.

Sample test cases:

Input:  "10011", "10100"
Output: 3

Input:  "helloworld", "worldhello"
Output: 8
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

std::string trim(const std::string& src,
                 const char* chars_to_trim = " \t\n\f\v\r") {
  if (0U == src.length())
    return {};

  const std::unordered_set<char> trimmed_chars(
      chars_to_trim, chars_to_trim + strlen(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const char ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return {};

  const auto last{std::find_if(std::crbegin(src), std::crend(src),
                               [&trimmed_chars](const char ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return {first, last};
}

string HammingDistance(const string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 2U)
    return "Not possible!";

  size_t number_of_ch_differences{};

  const string str1{trim(str_arr[0])};
  const string str2{trim(str_arr[1])};

  const size_t str1_len{str_arr[0].length()};
  const size_t str2_len{str_arr[1].length()};

  const size_t max_len{max(str1_len, str2_len)};
  const size_t min_len{min(str1_len, str2_len)};

  const size_t diff_len{max_len - min_len};

  for (size_t i{}; i < min_len; ++i)
    number_of_ch_differences = str1[i] != str2[i] ? number_of_ch_differences + 1
                                                  : number_of_ch_differences;

  number_of_ch_differences += diff_len;

  return to_string(number_of_ch_differences);
}

int main() {
  // const string A[] = gets(stdin);
  // cout << HammingDistance(A, sizeof(A)/sizeof(A[0]));
  const string A[]{"coder", "codec"};
  cout << HammingDistance(A, sizeof(A) / sizeof(*A))
       << '\n';  // expected output: 1
  const string B[]{"10011", "10100"};
  cout << HammingDistance(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 3
  const string C[]{"helloworld", "worldhello"};
  cout << HammingDistance(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 8

  return 0;
}
