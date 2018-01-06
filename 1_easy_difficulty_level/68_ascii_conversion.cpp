/*
Coderbyte coding challenge: ASCII Conversion

Using the C++ language, have the function ASCIIConversion(str) take the str parameter being passed and return a new string where every character, 
aside from the space character, is replaced with its corresponding decimal character code. 
For example: if str is "dog" then your program should return the string 100111103 because d = 100, o = 111, g = 103.

Sample test cases:

Input:  "hello world"
Output: "104101108108111 119111114108100"

Input:  "abc **"
Output: "979899 4242"
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


string ASCIIConversion(string str) {

  str = trim(str);

  string result{};
  result.reserve(3 * str.length());

  char buffer[4];

  for (const char ch : str) {
  	
  	if (' ' == ch) {
  		result.push_back(' ');  		
  		continue;
  	}

  	sprintf(buffer, "%lu", static_cast<size_t>(ch));

  	result += buffer;

  }

  result.shrink_to_fit();
  return result;            
}

int main() { 

  // cout << ASCIIConversion(move(string{gets(stdin)}));
  cout << ASCIIConversion(move(string{"dog"})) << '\n';         // expected output: "100111103"
  cout << ASCIIConversion(move(string{"hello world"})) << '\n'; // expected output: "104101108108111 119111114108100"
  cout << ASCIIConversion(move(string{"abc **"})) << '\n';      // expected output: "979899 4242"
  
  return 0;    
}
