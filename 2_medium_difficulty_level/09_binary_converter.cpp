/*
Coderbyte coding challenge: Binary Converter

Using the C++ language, have the function BinaryConverter(str) return the decimal form of the binary value. 
For example: if 101 is passed return 5, or if 1000 is passed return 8.

Sample test cases:

Input:  "100101"
Output: "37"

Input:  "011"
Output: "3"
*/

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

string trim(const string& str)
{
	size_t begin_str{};
	size_t end_str{str.size() - 1};

	if (0u == str.length()) return string{};

	for (; begin_str <= end_str; ++begin_str)
	{
		if (!isspace(str[begin_str])) break;
	}

	if (begin_str > end_str) return string{};

	for (; end_str > begin_str; --end_str)
	{
		if (!isspace(str[end_str])) break;
	}

	return str.substr(begin_str, end_str - begin_str + 1);
}

bool is_valid_binary_string(const string& str) {

	return all_of(begin(str), end(str), [](const char ch) {
		return (ch == '0' || ch == '1');
	});
}

string BinaryConverter(string str) {

  str = trim(str);

  if (!is_valid_binary_string(str)) return string{"Not possible!"};   

  int decimal_number{};

  for (const char ch : str) {

  	decimal_number <<= 1;

  	decimal_number |= static_cast<int>(ch - '0');
  
  }

  return to_string(decimal_number);
            
}

int main() { 
  
  // cout << BinaryConverter(move(string{gets(stdin)}));
  cout << BinaryConverter(move(string{"101"})) << '\n';    // expected output: 5
  cout << BinaryConverter(move(string{"1000"})) << '\n';   // expected output: 8
  cout << BinaryConverter(move(string{"100101"})) << '\n'; // expected output: 37
  cout << BinaryConverter(move(string{"011"})) << '\n';    // expected output: 3

  return 0;    
}
