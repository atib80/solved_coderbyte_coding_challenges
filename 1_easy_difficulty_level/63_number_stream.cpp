/*
Coderbyte coding challenge: Number Stream

Using the C++ language, have the function NumberStream(str) take the str parameter being passed which will contain the numbers 2 through 9, 
and determine if there is a consecutive stream of digits of at least N length where N is the actual digit value. 
If so, return the string true, otherwise return the string false. 

For example: if str is "6539923335" then your program should return the string true because there is a consecutive stream of 3's of length 3. 
The input string will always contain at least one digit.

Sample test cases:

Input:  "5556293383563665"
Output: "false"

Input:  "5788888888882339999"
Output: "true"
*/

#include <iostream>
#include <string>
#include <algorithm>
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

string NumberStream(string str) { 

	str = trim(str);

	const size_t str_len { str.length() };

	for (size_t i{}; i < str_len - 1; i++) {

		const char digit{str[i]};
		const size_t rep{static_cast<size_t>(str[i] - '0')};

		if ((i + rep) > str_len) {

			if ((str_len - 2 ) == i) return "false";
			
			continue;

		}

		bool is_seq_correct{true};

		for (size_t j{i+1}; j < (i + rep); j++) {
			if (digit != str[j]) {
				is_seq_correct = false;
				i = j - 1;
				break;			
			}
		}

		if (is_seq_correct) return "true";

	}  

  return "false"; 
            
}

int main() { 
  
  // cout << NumberStream(move(string{gets(stdin)}));
  cout << NumberStream(move(string{"6539923335"})) << '\n';          // expected output: "true"
  cout << NumberStream(move(string{"5556293383563665"})) << '\n';    // expected output: "false"
  cout << NumberStream(move(string{"5788888888882339999"})) << '\n'; // expected output: "true"
  
  return 0;
    
}
