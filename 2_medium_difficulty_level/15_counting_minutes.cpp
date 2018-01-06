/*
Coderbyte coding challenge: Counting Minutes

Using the C++ language, have the function CountingMinutes(str) take the str parameter being passed which will be two times 
(each properly formatted with a colon and am or pm) separated by a hyphen and return the total number of minutes between the two times. 
The time will be in a 12 hour clock format. 
For example: if str is 9:00am-10:00am then the output should be 60. 
If str is 1:00pm-11:00am the output should be 1320.

Sample test cases:

Input:  "12:30pm-12:00am"
Output: 690

Input:  "1:23am-1:08am"
Output: 1425
*/

#include <iostream>
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

	size_t prev{};

	string needle_st{needle};

	const size_t source_len{source.length()};

	const size_t needle_len{needle_st.length()};

	if ((0u == source_len) || (0u == needle_len)) return parts;

	size_t number_of_parts{};

	while (true)
	{
		const size_t current{source.find(needle_st, prev)};

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

string CountingMinutes(string str) {

  vector<string> times_str = split(str, "-");

  if (2u != times_str.size()) return string{"Not possible!"};

  vector<string> start_times_str = split(times_str[0], ":");

  if (2u != start_times_str.size()) return string{"Not possible!"};

  vector<string> end_times_str = split(times_str[1], ":");

  if (2u != end_times_str.size()) return string{"Not possible!"};

  size_t am_pm_start_char { start_times_str[1].find_first_of("ap") };

  if (string::npos == am_pm_start_char) return string{"Not possible!"};

  string start_time_am_pm_str { start_times_str[1].substr(am_pm_start_char, 2) };

  size_t start_hour { stoul(start_times_str[0]) };

  size_t start_minutes { stoul(start_times_str[1].substr(0, am_pm_start_char)) };

  size_t am_pm_end_char { end_times_str[1].find_first_of("ap") };

  if (string::npos == am_pm_end_char) return string{"Not possible!"};

  string end_time_am_pm_str { end_times_str[1].substr(am_pm_end_char, 2) };

  size_t end_hour { stoul(end_times_str[0]) };

  size_t end_minutes { stoul(end_times_str[1].substr(0, am_pm_end_char)) };

  size_t start_time_in_minutes { ("am" == start_time_am_pm_str) ? ( ((start_hour % 12) * 60) + start_minutes) : (((start_hour % 12) * 60) + 720 + start_minutes) };

  size_t end_time_in_minutes { ("am" == end_time_am_pm_str) ? ( ((end_hour % 12) * 60) + end_minutes) : (((end_hour % 12) * 60) + 720 + end_minutes) };

  if (start_time_in_minutes > end_time_in_minutes) {

  	start_time_in_minutes = 1440 - start_time_in_minutes;  	

  	return to_string(start_time_in_minutes + end_time_in_minutes);
  
  }

  return to_string(end_time_in_minutes - start_time_in_minutes);
    
}

int main() { 
  
  // cout << CountingMinutes(move(trim(string{gets(stdin)})));
  cout << CountingMinutes(move(trim(string{"9:00am-10:00am"}))) << '\n';  // expected output: "60"
  cout << CountingMinutes(move(trim(string{"1:00pm-11:00am"}))) << '\n';  // expected output: "1320"
  cout << CountingMinutes(move(trim(string{"12:30pm-12:00am"}))) << '\n'; // expected output: "690"
  cout << CountingMinutes(move(trim(string{"1:23am-1:08am"}))) << '\n';   // expected output: "1425"
  
  return 0;
} 
