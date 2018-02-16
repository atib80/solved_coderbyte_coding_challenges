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
#include <iostream>
#include <string>

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

string HammingDistance(const string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 2)
    return "Not possible!";

  size_t number_of_ch_differences{};

  const string str1{trim(str_arr[0])};
  const string str2{trim(str_arr[1])};

  const size_t str1_len{str_arr[0].length()};
  const size_t str2_len{str_arr[1].length()};

  const size_t diff_len{
      ((str1_len < str2_len) ? (str2_len - str1_len) : (str1_len - str2_len))};

  for (size_t i{}; i < min(str1_len, str2_len); i++) {
    if (str1[i] != str2[i])
      number_of_ch_differences++;
  }

  if (diff_len)
    number_of_ch_differences += diff_len;

  return to_string(number_of_ch_differences);
}

int main() {
  // const string A[] = gets(stdin);
  // cout << HammingDistance(A, sizeof(A)/sizeof(A[0]));
  const string A[] = {"coder", "codec"};
  cout << HammingDistance(A, sizeof(A) / sizeof(A[0]))
       << '\n';  // expected output: 1
  const string B[] = {"10011", "10100"};
  cout << HammingDistance(B, sizeof(B) / sizeof(B[0]))
       << '\n';  // expected output: 3
  const string C[] = {"helloworld", "worldhello"};
  cout << HammingDistance(C, sizeof(C) / sizeof(C[0]))
       << '\n';  // expected output: 8

  return 0;
}
