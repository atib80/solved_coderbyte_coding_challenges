/*
Coderbyte coding challenge: Time Difference

Using the C++ language, have the function TimeDifference(strArr) read the array of strings stored in strArr which will be an unsorted list of times 
in a twelve-hour format like so: HH:MM(am/pm). Your goal is to determine the smallest difference in minutes between two of the times in the list. 
For example: if strArr is ["2:10pm", "1:30pm", "10:30am", "4:42pm"] then your program should return 40 
because the smallest difference is between 1:30pm and 2:10pm with a difference of 40 minutes. 
The input array will always contain at least two elements and all of the elements will be in the correct format and unique.

Sample test cases:

Input:  "1:10pm", "4:40am", "5:00pm"
Output: 230

Input:  "10:00am", "11:45pm", "5:00am", "12:01am"
Output: 16
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

string TimeDifference(const string* str_arr, const size_t str_arr_size) {

  vector<int> times{};

  for (size_t i{}; i != str_arr_size; i++) {

	  vector<string> time_parts_str = split(str_arr[i], ":");

	  if (2u != time_parts_str.size()) return string{"Not possible!"};

      size_t am_pm_start_char { time_parts_str[1].find_first_of("ap") };

	  if (string::npos == am_pm_start_char) return string{"Not possible!"};

	  string time_am_pm_str { time_parts_str[1].substr(am_pm_start_char, 2) };

	  int hour { stoi(time_parts_str[0]) };

	  int minutes { stoi(time_parts_str[1].substr(0, am_pm_start_char)) };

	  int time_in_minutes { "am" == time_am_pm_str ? ((hour % 12) * 60) + minutes : ((hour % 12) * 60) + 720 + minutes };

	  times.emplace_back(time_in_minutes);
  }

  sort(begin(times), end(times));

  int current_minimum{abs(times[1] - times[0])};

  for (size_t i{}; i < (times.size() - 1); i++) {

 	 for (size_t j{ i + 1}; j < times.size(); j++) {

 	 	if ((0u == i) && (1u == j )) continue;

  		if ( abs( times[j] - times[i] ) < current_minimum ) current_minimum = abs( times[j] - times[i] );

  		if ( abs( (1440 - times[j]) + times[i] ) < current_minimum ) current_minimum = abs( (1440 - times[j]) + times[i] );

    }
  
  }

  return to_string(current_minimum); 
            
}

int main() { 
     
  // const string A[] = gets(stdin);
  // cout << TimeDifference(A, sizeof(A)/sizeof(*A));  
  const string B[] = {"2:10pm", "1:30pm", "10:30am", "4:42pm"};
  cout << TimeDifference(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "40"
  const string C[] = {"1:10pm", "4:40am", "5:00pm"};
  cout << TimeDifference(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "230"
  const string D[] = {"10:00am", "11:45pm", "5:00am", "12:01am"};
  cout << TimeDifference(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "16"

  return 0;    
}
