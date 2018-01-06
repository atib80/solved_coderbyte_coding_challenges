/*
Coderbyte coding challenge: Letter Count

Using the C++ language, have the function LetterCount(str) take the str parameter being passed and return the first word with the greatest number of repeated letters. 
For example: "Today, is the greatest day ever!" should return greatest because it has 2 e's (and 2 t's) and it comes before ever which also has 2 e's. 
If there are no words with repeating letters return -1. Words will be separated by spaces.

Sample test cases:

Input:  "Hello apple pie"
Output: "Hello"

Input:  "No words"
Output: "-1"
*/

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <utility>
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

vector<string> split(const string& source, const char* needle,
                              size_t const max_count = string::npos)
{
	vector<string> parts{};			

	string needle_st{needle};

	const size_t source_len{source.length()};
	const size_t needle_len{needle_st.length()};

	if ((0u == source_len) || (0u == needle_len)) return parts;

	size_t number_of_parts{}, prev{};

	while (true)
	{
		const size_t current { source.find(needle_st, prev) };

		if (string::npos == current) break;

		number_of_parts++;

		if ((string::npos != max_count) && (parts.size() == max_count)) break;

		if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source_len) break;
	}

	if (prev < source_len)
	{
		if (string::npos == max_count) parts.emplace_back(source.substr(prev));

		else if ((string::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
	}

	return parts;
}

string LetterCount(string str) { 

	str = trim(str);

	vector<string> words = split(str, " ");

	vector<pair<string, size_t>> word_char_freq{};

	for (const auto& word : words) {

		size_t rep_char_count{};

		for (const char ch : word) {

			const size_t ch_freq = count(begin(word), end(word), ch);

			if (ch_freq > 1) rep_char_count += ch_freq;
		}

		word_char_freq.emplace_back(make_pair(word, rep_char_count));
	}

	stable_sort(begin(word_char_freq), end(word_char_freq), [](const pair<string, size_t>& lhs, const pair<string, size_t>& rhs) {

		return (lhs.second > rhs.second);

	});

	if (word_char_freq[0].second > 1u) return word_char_freq[0].first;

  	return string{"-1"};
}

int main() { 
  
  // cout << LetterCount(move(string{gets(stdin)}));
  cout << LetterCount(move(string{"Today, is the greatest day ever!"})) << '\n'; // expected output: "greatest"
  cout << LetterCount(move(string{"Hello apple pie"})) << '\n'; 			     // expected output: "Hello"
  cout << LetterCount(move(string{"No words"})) << '\n';						 // expected output: "-1"
  
  return 0;
}
