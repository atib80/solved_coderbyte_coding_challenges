/*
Coderbyte coding challenge: Wildcard Characters

Using the C++ language, have the function WildcardCharacters(str) read str which will contain two strings separated by a space.
The first string will consist of the following sets of characters: +, *, and {N} which is optional.
The plus (+) character represents a single alphabetic character, the asterisk (*) represents a sequence of the same character of length 3
unless it is followed by {N} which represents how many characters should appear in the sequence where N will be at least 1.
Your goal is to determine if the second string exactly matches the pattern of the first string in the input.

For example: if str is "++*{5} gheeeee" then the second string in this case does match the pattern, so your program should return the string true.
If the second string does not match the pattern your program should return the string false.

Sample Test Cases

Input:  "+++++* abcdemmmmmm"
Output: "false"

Input:  "**+*{2} mmmrrrkbb"
Output: "true"
*/

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

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

vector<string> split(const string& source, const char* needle,
                     size_t const max_count = string::npos)
{
	vector<string> parts{};

	string needle_st{needle};

	const size_t source_len{source.length()};

	const size_t needle_len{needle_st.size()};

	if ((0u == source_len) || (0u == needle_len))
		return parts;

	size_t number_of_parts{}, prev{};

	while (true)
	{
		const size_t current{source.find(needle_st, prev)};

		if (string::npos == current)
			break;

		number_of_parts++;

		if ((string::npos != max_count) && (parts.size() == max_count))
			break;

		if ((current - prev) > 0)
			parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source_len)
			break;
	}

	if (prev < source_len)
	{
		if (string::npos == max_count)
			parts.emplace_back(source.substr(prev));

		else if ((string::npos != max_count) && (parts.size() < max_count))
			parts.emplace_back(source.substr(prev));
	}

	return parts;
}

string WildcardCharacters(string str)
{
	str = trim(str);
	const auto string_parts = split(str, " ", 2);
	const auto& pattern = string_parts[0];
	const size_t pattern_len{pattern.length()};
	const auto& text = string_parts[1];
	const size_t text_len{text.length()};

	size_t pi{}, ti{};

	while (pi < pattern_len)
	{
		if ('+' == pattern[pi])
		{
			if (ti >= text_len) return "false";
			ti++;
			pi++;
		}
		else if ('*' == pattern[pi])
		{
			size_t count{3u};

			if (pi + 1 == pattern.find("{", pi + 1))
			{
				const size_t ei{pattern.find("}", pi + 2)};

				if ((string::npos != ei) && (ei > pi + 2))
				{
					count = stoul(pattern.substr(pi + 2, ei - (pi + 2)));
					pi = ei + 1;
				}
			}
			else
			{
				pi++;
			}

			if (ti > text_len - count) return "false";

			const auto first_char = text[ti];

			for (size_t i{ti + 1}; i < ti + count; i++)
			{
				if (first_char != text[i]) return "false";
			}

			ti += count;
		}
	}

	if (ti < text_len) return "false";

	return "true";
}

int main()
{
	// cout << WildcardCharacters(move(string{gets(stdin)}));
	cout << WildcardCharacters(move(string{"++*{5} gheeeee"})) << '\n';     // expected output: "true"
	cout << WildcardCharacters(move(string{"+++++* abcdemmmmmm"})) << '\n'; // expected output: "false"
	cout << WildcardCharacters(move(string{"**+*{2} mmmrrrkbb"})) << '\n';  // expected output: "true"

	return 0;
}
