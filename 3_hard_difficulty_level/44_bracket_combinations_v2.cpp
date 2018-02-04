/*
Coderbyte coding challenge: Bracket Combinations

Using the C++ language, have the function BracketCombinations(num) read num
which will be an integer greater than or equal to zero, and return the number of
valid combinations that can be formed with num pairs of parentheses. For
example, if the input is 3, then the possible combinations of 3 pairs of
parenthesis, namely:
()()(), are ()()(), ()(()), (())(), ((())), and (()()).
There are 5 total combinations when the input is 3, so your program should
return 5.

Sample test cases:

Input:  3
Output: 5

Input:  2
Output: 2
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool is_valid_combinations_of_bracket_pairs(const string& str)
{
	int brackets_balance_count{};

	if (')' == str[0]) return false;	

	if ('(' == str[str.length() - 1]) return false;

	for (size_t i{}; i <= str.length(); i++)
	{
		if ('(' == str[i]) brackets_balance_count++;

		else if (')' == str[i])
		{
			if (brackets_balance_count <= 0) return false;

			brackets_balance_count--;
		}
	}

	if (brackets_balance_count) return false;

	return true;
}

size_t find_number_of_possible_combinations(const size_t number_of_pairs)
{
	size_t combinations{};

	string brackets{string(number_of_pairs, '(') + string(number_of_pairs, ')')};

	sort(begin(brackets), end(brackets));

	do
	{
		if (is_valid_combinations_of_bracket_pairs(brackets)) combinations++;
	}
	while (next_permutation(begin(brackets), end(brackets)));


	return combinations;
}

size_t BracketCombinations2(const size_t num)
{
	return find_number_of_possible_combinations(num);
}

int main()
{
	// cout << BracketCombinations2(gets(stdin));
	cout << BracketCombinations2(2) << '\n'; // expected output: 2
	cout << BracketCombinations2(3) << '\n'; // expected output: 5
	cout << BracketCombinations2(4) << '\n'; // expected output: 14
	cout << BracketCombinations2(5) << '\n'; // expected output: 42
	cout << BracketCombinations2(6) << '\n'; // expected output: 132	
	cout << BracketCombinations2(7) << '\n'; // expected output: 429	
	cout << BracketCombinations2(8) << '\n'; // expected output: 1430	
	cout << BracketCombinations2(9) << '\n'; // expected output: 4862	
	cout << BracketCombinations2(10) << '\n'; // expected output: 16796
	cout << BracketCombinations2(11) << '\n'; // expected output: 58786
	cout << BracketCombinations2(12) << '\n'; // expected output: 208012

	return 0;
}
