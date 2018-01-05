/*
Coderbyte coding challenge: Three Numbers

Using the C++ language, have the function ThreeNumbers(str) take the str parameter being passed and determine if exactly three unique, single-digit integers 
occur within each word in the string. The integers can appear anywhere in the word, but they cannot be all adjacent to each other. 
If every word contains exactly 3 unique integers somewhere within it, then return the string true, otherwise return the string false. 
For example: if str is "2hell6o3 wor6l7d2" then your program should return "true" but if the string is "hell268o w6or2l4d" then your program should return "false" 
because all the integers are adjacent to each other in the first word.

Sample test cases:

Input:  "2a3b5 w1o2rl3d g1gg92"
Output: "true"

Input:  "21aa3a ggg4g4g6ggg"
Output: "false"
*/

#include <iostream>
#include <string>
#include <vector>
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

string ThreeNumbers(string str) {

  str = trim(str);

  const vector<string> words { split(str, " ") };

  for (const auto& word : words) {

  	const size_t word_len { word.length() };

  	if (word_len <= 3u) return "false";

  	string w{word};

  	sort(begin(w), end(w));
    
  	if ((w[2] < '0') || (w[2] > '9') || ((w[3] >= '0') && (w[3] <= '9'))) return "false";
  	
  	if ((w[0] == w[1]) || (w[0] == w[2]) || (w[1] == w[2])) return "false";

  	vector<size_t> digit_positions{};

  	for (size_t i{}; i < word_len; i++) {

  		if (word[i] < '0' || word[i] > '9') continue;

  		digit_positions.emplace_back(i);
  	}

  	if (2u == (digit_positions[2] - digit_positions[0])) return "false";

  }

  return "true";
            
}

int main() { 
  
  // cout << ThreeNumbers(move(string{gets(stdin)}));
  cout << ThreeNumbers(move(string{"2hell6o3 wor6l7d2"})) << '\n';     // expected output: "true"
  cout << ThreeNumbers(move(string{"hell268o w6or2l4d"})) << '\n';     // expected output: "false"
  cout << ThreeNumbers(move(string{"2a3b5 w1o2rl3d g1gg92"})) << '\n'; // expected output: "true"
  cout << ThreeNumbers(move(string{"21aa3a ggg4g4g6ggg"})) << '\n';    // expected output: "false"
  return 0;    
} 
