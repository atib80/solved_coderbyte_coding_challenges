/*
Coderbyte coding challenge: Serial Number

Using the C++ language, have the function SerialNumber(str) take the str parameter being passed and determine
if it is a valid serial number with the following constraints:

1. It needs to contain three sets each with three digits (1 through 9) separated by a period.
2. The first set of digits must add up to an even number.
3. The second set of digits must add up to an odd number.
4. The last digit in each set must be larger than the two previous digits in the same set.

If all the above constraints are met within the string, the your program should return the string true, otherwise your program should return the string false. 
For example: if str is "224.315.218" then your program should return "true".

Sample test cases:

Input:  "11.124.667"
Output: "false"

Input:  "114.568.112"
Output: "true"
*/

#include <iostream>
#include <cctype>
#include <string>
#include <cctype>
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

string SerialNumber(string str) { 

  str = trim(str);

  vector<string> parts = split(str, ".");

  for (const auto& part : parts) {
  	
  	if (part.length() < 3u) return string{"false"};

  	if ((part[2] < part[1]) || (part[2] < part[0])) return string{"false"};

  }

  int number_value{};

  for (const char ch : parts[0]) number_value += static_cast<int>(ch - '0');

  if (number_value % 2 == 1) return string{"false"};

  number_value = 0;

  for (const char ch : parts[1]) number_value += static_cast<int>(ch - '0');

  if (number_value % 2 == 0) return string{"false"};
 
  return string{"true"}; 
            
}

int main() { 
  
  // cout << SerialNumber(move(string{gets(stdin)}));
  cout << SerialNumber(move(string{"224.315.218"})) << '\n'; // expected output: "true"
  cout << SerialNumber(move(string{"11.124.667"})) << '\n';  // expected output: "false"
  cout << SerialNumber(move(string{"114.568.112"})) << '\n'; // expected output: "true"

  return 0;    
} 
