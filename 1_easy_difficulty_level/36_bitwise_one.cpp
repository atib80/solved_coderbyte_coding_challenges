/*
Coderbyte coding challenge: Bitwise One

Using the C++ language, have the function BitwiseOne(strArr) take the array of strings stored in strArr, which will only contain two strings of equal length 
that represent binary numbers, and return a final binary string that performed the bitwise OR operation on both strings. 
A bitwise OR operation places a 0 in the new string where there are zeroes in both binary strings, otherwise it places a 1 in that spot. 
For example: if strArr is ["1001", "0100"] then your program should return the string "1101"

Sample test cases:

Input:  "100", "000"
Output: "100"

Input:  "00011", "01010"
Output: "01011"
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string BitwiseOne(const string* binary_numbers, const size_t str_arr_size) { 

  if (str_arr_size < 2u) return string{"Not possible!"};

  if (binary_numbers[0].length() != binary_numbers[1].length()) return string{"Not possible!"}; 

  string result(binary_numbers[0].length(), '0');

  for (size_t i{}; i != binary_numbers[0].length(); i++) {
  	if ( ( '1' == binary_numbers[0][i] ) || ( '1' == binary_numbers[1][i] ) ) result[i] = '1';  	
  }

  return result;
            
}

int main() { 

  // const string str_arr1[] = gets(stdin);
  // cout << BitwiseOne(str_arr1, sizeof(str_arr1)/sizeof(*str_arr1));
  const string str_arr2[] = {"1001", "0100"};
  cout << BitwiseOne(str_arr2, sizeof(str_arr2)/sizeof(*str_arr2)) << '\n'; // expected output: "1101"
  const string str_arr3[] = {"100", "000"};
  cout << BitwiseOne(str_arr3, sizeof(str_arr3)/sizeof(*str_arr3)) << '\n'; // expected output: "100"
  const string str_arr4[] = {"00011", "01010"};
  cout << BitwiseOne(str_arr4, sizeof(str_arr4)/sizeof(*str_arr4)) << '\n'; // expected output: "01011"

  return 0;

}
