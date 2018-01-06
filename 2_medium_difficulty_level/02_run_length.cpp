/*
Coderbyte coding challenge: Run Length

Using the C++ language, have the function RunLength(str) take the str parameter being passed and return a compressed version of the string 
using the Run-length encoding algorithm. This algorithm works by taking the occurrence of each repeating character and outputting that number 
along with a single character of the repeating sequence. For example: "wwwggopp" would return 3w2g1o2p. 
The string will not contain any numbers, punctuation, or symbols.

Sample test cases:

Input:  "aabbcde"
Output: "2a2b1c1d1e"

Input:  "wwwbbbw"
Output: "3w3b1w"
*/

#include <iostream>
#include <sstream>
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


string run_length(string str) { 

	str = trim(str);

	if (str.empty()) return string{};

	const size_t str_len{str.length()};	

	ostringstream oss{};

	if (1u == str_len) {
		oss << '1' << str[0];		
		return oss.str();
	}

	char current_ch{str[0]};
	size_t current_ch_count{1u};

	for (size_t i{1u}; i != str_len; i++) {

		if (current_ch == str[i]) {

			current_ch_count++;
			continue;

		}
		
		oss << current_ch_count << current_ch;			
		current_ch = str[i];
		current_ch_count = 1u;
	}

	oss << current_ch_count << current_ch;	

    return oss.str();
    
}

int main() { 
  
  // cout << run_length(move(string{gets(stdin)}));
  cout << run_length(move(string{"wwwggopp"})) << '\n';  // expected output: "3w2g1o2p"
  cout << run_length(move(string{"aabbcde"})) << '\n';   // expected output: "2a2b1c1d1e"
  cout << run_length(move(string{"wwwbbbw"})) << '\n';   // expected output: "3w3b1w"

  return 0;
    
}
