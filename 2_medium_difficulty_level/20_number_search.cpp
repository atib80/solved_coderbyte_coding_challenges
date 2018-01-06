/*
Coderbyte coding challenge: Number Search

Using the C++ language, have the function NumberSearch(str) take the str parameter, search for all the numbers in the string, add them together, 
then return that final number divided by the total amount of letters in the string. For example: if str is "Hello6 9World 2, Nic8e D7ay!" the output should be 2. 
First if you add up all the numbers, 6 + 9 + 2 + 8 + 7 you get 32. Then there are 17 letters in the string. 32 / 17 = 1.882, 
and the final answer should be rounded to the nearest whole number, so the answer is 2. 
Only single digit numbers separated by characters will be used throughout the whole string (So this won't ever be the case: hello44444 world). 
Each string will also have at least one letter.

Sample test cases:

Input:  "H3ello9-9"
Output: 4

Input:  "One Number*1*"
Output: 0
*/

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

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

string NumberSearch(string str) {

  str = trim(str);
  
  size_t sum{};
  size_t letter_count{};

  for (const char c : str) {
  	if (isdigit(c)) sum += static_cast<size_t>(c - '0');
  	else if (isalpha(c)) letter_count++;
  }

  if (!letter_count || !sum) return "0";

  return to_string(static_cast<long>(round(static_cast<float>(sum)/static_cast<float>(letter_count))));

}

int main() { 
  
  // cout << NumberSearch(move(string{gets(stdin)}));
  cout << NumberSearch(move(string{"Hello6 9World 2, Nic8e D7ay!"})) << '\n'; // expected output: 2
  cout << NumberSearch(move(string{"H3ello9-9"})) << '\n'; 					          // expected output: 4
  cout << NumberSearch(move(string{"One Number*1*"})) << '\n'; 				        // expected output: 0
  return 0;    
}
