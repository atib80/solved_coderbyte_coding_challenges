/*
Coderbyte coding challenge: Bitwise One

Using the C++ language, have the function BitwiseOne(strArr) take the array of
strings stored in strArr, which will only contain two strings of equal length
that represent binary numbers, and return a final binary string that performed
the bitwise OR operation on both strings. A bitwise OR operation places a 0 in
the new string where there are zeroes in both binary strings, otherwise it
places a 1 in that spot. For example: if strArr is ["1001", "0100"] then your
program should return the string "1101"

Sample test cases:

Input:  "100", "000"
Output: "100"

Input:  "00011", "01010"
Output: "01011"
*/

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

string BitwiseOne_v1(string* binary_numbers, const size_t str_arr_size) {
  if (str_arr_size < 2)
    return "Not possible!";

  binary_numbers[0] = trim(binary_numbers[0]);
  binary_numbers[1] = trim(binary_numbers[1]);

  if (binary_numbers[0].length() != binary_numbers[1].length())
    return "Not possible!";

  string result(binary_numbers[0].length(), '0');

  for (size_t i{}; i < binary_numbers[0].length(); i++) {
    if (('1' == binary_numbers[0][i]) || ('1' == binary_numbers[1][i]))
      result[i] = '1';
  }

  return result;
}

string BitwiseOne_v2(const string* binary_numbers, const size_t str_arr_size) {
  if (str_arr_size < 2)
    return "Not possible!";

  if (binary_numbers[0].length() != binary_numbers[1].length())
    return "Not possible!";

  int result{stoi(binary_numbers[0], nullptr, 2) |
             stoi(binary_numbers[1], nullptr, 2)};

  string result_str{};

  while (result) {
    if (result % 2 == 1)
      result_str.insert(begin(result_str), '1');
    else
      result_str.insert(begin(result_str), '0');

    result /= 2;
  }

  result_str.insert(begin(result_str),
                    binary_numbers[0].length() - result_str.length(), '0');

  return result_str;
}

int main() {

  // const string str_arr1[] = gets(stdin);
  // cout << BitwiseOne_v2(str_arr1, sizeof(str_arr1)/sizeof(*str_arr1));
  string str_arr2[] = {"1001", "0100"};
  cout << BitwiseOne_v2(str_arr2, sizeof(str_arr2) / sizeof(*str_arr2))
       << '\n';  // expected output: "1101"
  string str_arr3[] = {"100", "000"};
  cout << BitwiseOne_v2(str_arr3, sizeof(str_arr3) / sizeof(*str_arr3))
       << '\n';  // expected output: "100"
  string str_arr4[] = {"00011", "01010"};
  cout << BitwiseOne_v2(str_arr4, sizeof(str_arr4) / sizeof(*str_arr4))
       << '\n';  // expected output: "01011"

  return 0;
}
