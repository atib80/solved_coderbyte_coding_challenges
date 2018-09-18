/*
Coderbyte coding challenge: H-distance

Using the C++ language, have the function HDistance(strArr) take the array of
strings stored in strArr, which will only contain two strings of equal length
and return the number of characters at each position that are different between
them. For example: if strArr is ["house", "hours"] then your program should
return 2. The string will always be of equal length and will only contain
lowercase characters from the alphabet and numbers.

Sample test cases:

Input:  "10011", "10100"
Output: 3

Input:  "abcdef", "defabc"
Output: 6
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

string HDistance(const string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 2)
    return "Not possible!";

  size_t number_of_ch_differences{};

  const string str1{trim(str_arr[0])};
  const string str2{trim(str_arr[1])};

  const size_t str1_len{str_arr[0].length()};
  const size_t str2_len{str_arr[1].length()};

  const size_t diff_len{str1_len < str2_len ? str2_len - str1_len
                                            : str1_len - str2_len};

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
  // cout << HDistance(A, sizeof(A)/sizeof(*A));
  const string B[] = {"10011", "10100"};
  cout << HDistance(B, sizeof(B) / sizeof(*B)) << '\n';  // expected output: 3
  const string C[] = {"abcdef", "defabc"};
  cout << HDistance(C, sizeof(C) / sizeof(*C)) << '\n';  // expected output: 6

  return 0;
}
