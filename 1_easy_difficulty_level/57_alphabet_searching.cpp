/*
Coderbyte coding challenge: Alphabet Searching

Using the C++ language, have the function AlphabetSearching(str) take the str parameter being passed and return the string true 
if every single letter of the English alphabet exists in the string, otherwise return the string false. 
For example: if str is "zacxyjbbkfgtbhdaielqrm45pnsowtuv" then your program should return the string true 
because every character in the alphabet exists in this string even though some characters appear more than once.

Sample test cases:

Input:  "abcdefghijklmnopqrstuvwxyyyy"
Output: "false"

Input:  "abc123456kmo"
Output: "false"
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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

string AlphabetSearching(string str) {

  str = trim(str);

  for (char& ch : str) ch = static_cast<char>(tolower(ch));
  
  unordered_map<char, size_t> dict{};

  for (char start{'a'}; start <= 'z'; start++) dict.insert(make_pair(start, 0u));

  for (const char ch : str) {

  	if (dict.find(ch) != end(dict)) dict[ch]++;

  }

  for (const pair<char, size_t>& char_freq : dict) {
  	if (!char_freq.second) return string{"false"};
  }

  return string{"true"}; 
            
}

int main() { 
  
  // cout << AlphabetSearching(move(string{gets(stdin)}));
  cout << AlphabetSearching(move(string{"zacxyjbbkfgtbhdaielqrm45pnsowtuv"})) << '\n'; // "true"
  cout << AlphabetSearching(move(string{"abcdefghijklmnopqrstuvwxyyyy"})) << '\n';     // "false"
  cout << AlphabetSearching(move(string{"abc123456kmo"})) << '\n';                     // "false"
  
  return 0;    
}
