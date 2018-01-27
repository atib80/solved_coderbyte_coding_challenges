/*
Coderbyte coding challenge: Line Ordering

Using the C++ language, have the function LineOrdering(strArr) read the strArr parameter being passed
which will represent the relations among people standing in a line. The structure of the input will be ["A>B","B>C","A<D",etc..].
The letters stand for different people and the greater than and less than signs stand for a person being in front of someone or behind someone.
A>B means A is in front of B and B<C means that B is behind C in line.
For example if strArr is: ["J>B","B<S","D>J"], these are the following ways you can arrange the people in line:
DSJB, SDJB and DJSB. Your program will determine the number of ways people can be arranged in line.
So for this example your program should return the number 3.
It also may be the case that the relations produce an impossible line ordering, resulting in zero as the answer.

Only the symbols <, >, and the uppercase letters A...Z will be used. The maximum number of relations strArr will contain is ten.

Sample test cases:

Input:  "A>B","A<C","C<Z"
Output: 1

Input:  "A>B","B<R","R<G"
Output: 3
*/

#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>
#include <algorithm>

using namespace std;

string trim(const string& str)
{
	const size_t str_len{str.length()};

	if (!str_len)
		return string{};

	size_t first{}, last{str_len - 1};

	for (; first <= last; ++first)
	{
		if (!isspace(str[first]))
			break;
	}

	if (first > last)
		return string{};

	for (; last > first; --last)
	{
		if (!isspace(str[last]))
			break;
	}

	return str.substr(first, last - first + 1);
}

string LineOrdering(const string* str_arr, const size_t str_arr_size)
{
	vector<string> relations(str_arr, str_arr + str_arr_size);

	for (auto& r : relations) r = trim(r);

	vector<pair<char, char>> relation_pairs{};
	unordered_set<char> people{};

	for (const auto& r : relations)
	{
		if ('>' == r[1])
			relation_pairs.emplace_back(make_pair(r[0], r[2]));
		else if ('<' == r[1])
			relation_pairs.emplace_back(make_pair(r[2], r[0]));

		if (people.find(r[0]) == end(people)) people.insert(r[0]);
		if (people.find(r[2]) == end(people)) people.insert(r[2]);
	}

	string line(begin(people), end(people));

	sort(begin(line), end(line));

	size_t combinations{};

	do
	{
		bool is_line_order_correct{true};

		for (const auto& r : relation_pairs)
		{
			if (!(line.find(r.first) < line.find(r.second)))
			{
				is_line_order_correct = false;
				break;
			}
		}

		if (is_line_order_correct) combinations++;
	}
	while (next_permutation(begin(line), end(line)));


	return to_string(combinations);
}

int main()
{
	// const string A[] = gets(stdin);
	// cout << LineOrdering(A, sizeof(A)/sizeof(*A));
	const string B[] = {"J>B","B<S","D>J"};
	cout << LineOrdering(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: "3"
	const string C[] = {"A>B","A<C","C<Z"};
	cout << LineOrdering(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: "1"
	const string D[] = {"A>B","B<R","R<G"};
	cout << LineOrdering(D, sizeof(D) / sizeof(*D)) << '\n'; // expected output: "3"

	return 0;
}
