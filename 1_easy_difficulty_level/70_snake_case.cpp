/*
Coderbyte coding challenge: Snake Case

Using the C++ language, have the function SnakeCase(str) take the str parameter being passed and return it in proper snake case format 
where each word is lowercased and separated from adjacent words via an underscore. 
The string will only contain letters and some combination of delimiter punctuation characters separating each word.
For example: if str is "BOB loves-coding" then your program should return the string bob_loves_coding.

Sample test cases:

Input:  "cats AND*Dogs-are Awesome"
Output: "cats_and_dogs_are_awesome"

Input:  "a b c d-e-f%g"
Output: "a_b_c_d_e_f_g"
*/

#include <iostream>
#include <string>
#include <cctype>
#include <locale>

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

string convert_to_snake_case(string str, const locale& loc = locale{})
{

	str = trim(str);
	string final_str{};
	final_str.reserve(str.length());

	bool is_new_word{};
	bool is_first_letter_found{};

	for (size_t i{}; i < str.length(); i++)
	{				

		if (!isalnum(str[i])) {
			is_new_word = true;
			continue;
		}

		if (is_new_word) {
			if (is_first_letter_found) final_str.push_back('_');
			is_new_word = false;
		}

		final_str.push_back(static_cast<char>(tolower(str[i], loc)));
		is_first_letter_found = true;

	}

	final_str.shrink_to_fit();
	return final_str;
}

string SnakeCase(string str) { 

	return convert_to_snake_case(move(str)); 
            
}

int main() {

  // cout << SnakeCase(move(string{gets(stdin)}));
  cout << SnakeCase(move(string{"BOB loves-coding"})) << '\n';          // expected output: bob_loves_coding
  cout << SnakeCase(move(string{"cats AND*Dogs-are Awesome"})) << '\n'; // expected output: cats_and_dogs_are_awesome
  cout << SnakeCase(move(string{"a b c d-e-f%g"})) << '\n';             // expected output: a_b_c_d_e_f_g
  
  return 0;

}
