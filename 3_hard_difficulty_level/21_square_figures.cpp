/*
Coderbyte coding challenge: Square Figures

Using the C++ language, have the function SquareFigures(num) read num which will be an integer.
Your program should return the smallest integer that when squared has a length equal to num.
For example: if num is 6 then your program should output 317 because 317^2 = 100489 while 316^2 = 99856 which does not have a length of six.

Sample test cases:

Input:  2
Output: 4

Input:  1
Output: 0
*/

#include <cstdint>
#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

int64_t find_minimum_number_for_specified_length(const int64_t current_number, const size_t target_number_len)
{
	int64_t next_number{current_number};
	string number_str{to_string(current_number * current_number)};
	const vector<int64_t> decrement_factors{
		0LL, 1LL, 10LL, 100LL, 1'000LL, 10'000LL, 100'000LL, 1'000'000LL, 10'000'000LL,
		100'000'000LL, 1'000'000'000LL, 10'000'000'000LL, 100'000'000'000LL
	};
	const size_t initial_decrement_factor_index{to_string(current_number).length()};

	// could decrement number by 1000, 100, 10 and then 1 depending on its original initial length (specified by 'target_number_len')
	for (size_t i{initial_decrement_factor_index}; i >= 1; i--)
	{
		while (true)
		{
			next_number -= decrement_factors[i];
			number_str = to_string(next_number * next_number);
			const size_t current_number_len{number_str.length()};
			if (target_number_len > current_number_len)
			{
				next_number += decrement_factors[i];
				if (i == 1) return next_number;
				break;
			}
			if (!next_number && (i == 1)) return 0;
		}
	}

	return next_number;
}

int64_t SquareFigures(const size_t target_number_len)
{	// the first initial step is to find the closest number using the binary search algorithm
	int64_t lower_bound{}, upper_bound{static_cast<int64_t>(sqrt(numeric_limits<int64_t>::max()))};

	while (true)
	{
		const int64_t current_number{(lower_bound + upper_bound) / 2};

		const string current_number_str{to_string(current_number * current_number)};

		const size_t current_number_len{current_number_str.length()};

		if (target_number_len == current_number_len)
			return find_minimum_number_for_specified_length(
				current_number, target_number_len);

		if (target_number_len < current_number_len) upper_bound = current_number;

		else lower_bound = current_number;
	}
}

int main()
{
	// cout << SquareFigures(gets(stdin));	
	cout << SquareFigures(6) << '\n'; // expected output: 317
	cout << SquareFigures(2) << '\n'; // expected output: 4
	cout << SquareFigures(1) << '\n'; // expected output: 0
	cout << SquareFigures(11) << '\n'; // expected output: 100000

	return 0;
}
