/*
Coderbyte coding challenge: Caesar Cipher

Using the C++ language, have the function CaesarCipher(str,num) take the str parameter and perform a Caesar Cipher shift on it 
using the num parameter as the shifting number. A Caesar Cipher works by shifting each letter in the string N places down in the alphabet 
(in this case N will be num). Punctuation, spaces, and capitalization should remain intact. For example if the string is "Caesar Cipher" 
and num is 2 the output should be "Ecguct Ekrjgt".

Sample test cases:

Input:  "Hello" & num = 4
Output: "Lipps"

Input:  "abc" & num = 0
Output: "abc"
*/

#include <iostream>
#include <string>
#include <cctype>

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

string CaesarCipher(string str, size_t num) {

	str = trim(str);
	
	if (str.empty()) return str;

	string encoded_str{str};

	num %= 26u;

	for (auto& ch : encoded_str) {		
		
		if (isalpha(ch)) {

			if (islower(ch)) {

				if ((static_cast<size_t>(ch) + num) > 122u) {
					size_t diff = num - (122u - static_cast<size_t>(ch)) - 1u;
					ch = static_cast<char>(97u + diff);
				} else {
					ch = static_cast<char>(static_cast<size_t>(ch) + num);
				}			

			} else {

				if ((static_cast<size_t>(ch) + num) > 90u) {
					size_t diff = num - (90u - static_cast<int>(ch)) - 1u;
					ch = static_cast<char>(65u + diff);
				} else {
					ch = static_cast<char>(static_cast<size_t>(ch) + num);
				}	

			} 
		
		}
	} 

  	return encoded_str;             
}

int main() { 
  
  // cout << CaesarCipher(gets(stdin));
  cout << CaesarCipher("Caesar Cipher", 2) << '\n'; // expected output: "Ecguct Ekrjgt"
  cout << CaesarCipher("Hello", 4) << '\n';         // expected output: "Lipps"
  cout << CaesarCipher("abc", 0) << '\n';           // expected output: "abc"
  cout << CaesarCipher("coderBYTE", 2) << '\n';     // expected output: "eqfgtDAVG"
  cout << CaesarCipher("dogs", 8) << '\n';          // expected output: "lwoa"
  cout << CaesarCipher("byte", 13) << '\n';         // expected output: "olgr"
  return 0;
}
