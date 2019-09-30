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

string BitwiseTwo_v1(string* binary_numbers, const size_t str_arr_size) {
  if (nullptr == binary_numbers || str_arr_size < 2U ||
      binary_numbers[0].length() != binary_numbers[1].length())
    return "not possible";

  for (size_t i{}; i < binary_numbers[0].length(); ++i) {
    if ('0' == binary_numbers[1][i])
      binary_numbers[0][i] = '0';
  }

  return move(binary_numbers[0]);
}

string BitwiseTwo_v2(string* binary_numbers, const size_t str_arr_size) {
  if (nullptr == binary_numbers || str_arr_size < 2U ||
      binary_numbers[0].length() != binary_numbers[1].length())
    return "not possible";

  unsigned long result{stoul(binary_numbers[0], nullptr, 2) &
                       stoul(binary_numbers[1], nullptr, 2)};

  int index = binary_numbers[0].length();

  while (0U != result) {
    binary_numbers[0][--index] = '0' + result % 2;
    result /= 2;
  }

  while (index > 0)
    binary_numbers[0][--index] = '0';

  return move(binary_numbers[0]);
}

int main() {
  // string str_arr1[] = gets(stdin);
  // cout << BitwiseTwo_v1(str_arr1, sizeof(str_arr1)/sizeof(*str_arr1));
  string str_arr2[]{"10111", "01101"};
  cout << BitwiseTwo_v1(str_arr2, sizeof(str_arr2) / sizeof(*str_arr2))
       << '\n';  // expected output: "00101"
  string str_arr3[]{"100", "000"};
  cout << BitwiseTwo_v1(str_arr3, sizeof(str_arr3) / sizeof(*str_arr3))
       << '\n';  // expected output: "000"
  string str_arr4[]{"10100", "11100"};
  cout << BitwiseTwo_v1(str_arr4, sizeof(str_arr4) / sizeof(*str_arr4))
       << '\n';  // expected output: "10100"

  return 0;
}
