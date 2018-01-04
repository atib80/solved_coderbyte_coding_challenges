/*
Coderbyte coding challenge: Ex Oh

Using the C++ language, have the function ExOh(str) take the str parameter being passed and return the string true if there is an equal number of x's and o's, 
otherwise return the string false. Only these two letters will be entered in the string, no punctuation or numbers. For example: if str is "xooxxxxooxo" 
then the output should return false because there are 6 x's and 5 o's.

Sample test cases:

Input:  "xooxxo"
Output: "true"

Input:  "x"
Output: "false"
*/

#include <iostream>
#include <cctype>
#include <string>
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

string ex_oh(string str) {

  str = trim(str);

  const auto o_count = count(begin(str), end(str), 'o');
  const auto x_count = count(begin(str), end(str), 'x');

  if (o_count == x_count) return string{"true"};      
  return string{"false"};
}

int main() { 

  // cout << ex_oh(move(string{gets(stdin)}));
  cout << ex_oh(move(string{"xooxxxxooxo"})) << '\n'; // expected output: "false"
  cout << ex_oh(move(string{"xooxxo"})) << '\n';      // expected output: "true"
  cout << ex_oh(move(string{"x"})) << '\n';           // expected output: "false"
  return 0;
}
