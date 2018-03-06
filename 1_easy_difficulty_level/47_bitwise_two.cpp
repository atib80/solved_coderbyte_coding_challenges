/*
Coderbyte coding challenge: Bitwise Two

Using the C++ language, have the function BitwiseTwo(strArr) take the array of
strings stored in strArr, which will only contain two strings of equal length
that represent binary numbers, and return a final binary string that performed
the bitwise AND operation on both strings. A bitwise AND operation places a 1 in
the new string where there is a 1 in both locations in the binary strings,
otherwise it places a 0 in that spot. For example: if strArr is ["10111",
"01101"] then your program should return the string "00101"

Sample test cases:

Input:  "100", "000"
Output: "000"

Input:  "10100", "11100"
Output: "10100"
*/

#include <iostream>
#include <string>

using namespace std;

string BitwiseTwo_v1(const string* binary_numbers, const size_t str_arr_size) {
  if (!binary_numbers || str_arr_size < 2)
    return "Not possible!";

  if (binary_numbers[0].length() != binary_numbers[1].length())
    return "Not possible!";

  string result(binary_numbers[0].length(), '0');

  for (size_t i{}; i < binary_numbers[0].length(); i++) {
    if (('1' == binary_numbers[0][i]) && ('1' == binary_numbers[1][i]))
      result[i] = '1';
  }

  return result;
}

string BitwiseTwo_v2(const string* binary_numbers, const size_t str_arr_size) {
  if (!binary_numbers || str_arr_size < 2)
    return "Not possible!";

  if (binary_numbers[0].length() != binary_numbers[1].length())
    return "Not possible!";

  int result{stoi(binary_numbers[0], nullptr, 2) &
             stoi(binary_numbers[1], nullptr, 2)};

  size_t index{binary_numbers[0].length()};
  string result_str(index, '0');
  index--;

  while (result) {
    if (result % 2 == 1)
      result_str[index] = '1';

    result /= 2;
    index--;
  }

  return result_str;
}

int main() {
  // const string str_arr1[] = gets(stdin);
  // cout << BitwiseTwo_v2(str_arr1, sizeof(str_arr1)/sizeof(*str_arr1));
  const string str_arr2[] = {"10111", "01101"};
  cout << BitwiseTwo_v2(str_arr2, sizeof(str_arr2) / sizeof(*str_arr2))
       << '\n';  // expected output: "00101"
  const string str_arr3[] = {"100", "000"};
  cout << BitwiseTwo_v2(str_arr3, sizeof(str_arr3) / sizeof(*str_arr3))
       << '\n';  // expected output: "000"
  const string str_arr4[] = {"10100", "11100"};
  cout << BitwiseTwo_v2(str_arr4, sizeof(str_arr4) / sizeof(*str_arr4))
       << '\n';  // expected output: "10100"

  return 0;
}
