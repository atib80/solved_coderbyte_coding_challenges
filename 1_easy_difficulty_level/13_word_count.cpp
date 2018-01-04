/*
Coderbyte coding challenge: Word Count

Using the C++ language, have the function WordCount(str) take the str string parameter being passed and return the number of words the string contains 
(e.g. "Never eat shredded wheat or cake" would return 6). Words will be separated by single spaces.

Sample test cases:

Input:  "Hello World"
Output: 2

Input:  "one 22 three"
Output: 3
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>

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

vector<string> split(const string& source, const char* needle, size_t const max_count = string::npos)
{
  vector<string> parts{}; 

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len)) return parts;

  size_t number_of_parts{}, prev{};

  while (true)
  {
    const size_t current = source.find(needle_st, prev);

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

string word_count(string str) {

  str = trim(str);

  const vector<string> words = split(str, " ");

  return to_string(words.size()); 
            
}

int main() { 
  // cout << word_count(move(string{gets(stdin)}));
  cout << word_count(move(string{"Never eat shredded wheat or cake"})) << '\n'; // expected output: 6 
  cout << word_count(move(string{"Hello World"})) << '\n';   					// expected output: 2
  cout << word_count(move(string{"one 22 three"})) << '\n';  				    // expected output: 3
  cout << word_count(move(string{"Coderbyte"})) << '\n';      					// expected output: 1
  cout << word_count(move(string{"h333llLo"})) << '\n'; 				        // expected output: 1
  cout << word_count(move(string{"Yo0"})) << '\n';							 	// expected output: 1
  cout << word_count(move(string{"commacomma!"})) << '\n';						// expected output: 1
  cout << word_count(move(string{"aq"})) << '\n';								// expected output: 1
  return 0;    
} 