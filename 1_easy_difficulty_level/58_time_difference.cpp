/*
Coderbyte coding challenge: Time Difference

Using the C++ language, have the function TimeDifference(strArr) read the array
of strings stored in strArr which will be an unsorted list of times in a
twelve-hour format like so: HH:MM(am/pm). Your goal is to determine the smallest
difference in minutes between two of the times in the list. For example: if
strArr is ["2:10pm", "1:30pm", "10:30am", "4:42pm"] then your program should
return 40 because the smallest difference is between 1:30pm and 2:10pm with a
difference of 40 minutes. The input array will always contain at least two
elements and all of the elements will be in the correct format and unique.

Sample test cases:

Input:  "1:10pm", "4:40am", "5:00pm"
Output: 230

Input:  "10:00am", "11:45pm", "5:00am", "12:01am"
Output: 16
*/

#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

  if (!source_len)
    return parts;

  if (!needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true) {
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

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if ((string::npos != max_count) && (parts.size() < max_count))
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

string TimeDifference(const string* str_arr, const size_t str_arr_size) {
  vector<int> times{};

  for (size_t i{}; i != str_arr_size; i++) {
    vector<string> time_parts_str = split(str_arr[i], ":");

    if (2 != time_parts_str.size())
      return "Not possible!";

    size_t am_pm_start_char{time_parts_str[1].find_first_of("ap")};

    if (string::npos == am_pm_start_char)
      return "Not possible!";

    string time_am_pm_str{time_parts_str[1].substr(am_pm_start_char, 2)};

    int hour{stoi(time_parts_str[0])};

    int minutes{stoi(time_parts_str[1].substr(0, am_pm_start_char))};

    int time_in_minutes{"am" == time_am_pm_str
                            ? ((hour % 12) * 60) + minutes
                            : ((hour % 12) * 60) + 720 + minutes};

    times.emplace_back(time_in_minutes);
  }

  int current_minimum{INT_MAX};

  for (size_t i{}; i < times.size() - 1; i++) {
    for (size_t j{i + 1}; j < times.size(); j++) {
       
      if (times[j] > times[i]) {
        if (times[j] - times[i] < current_minimum)
          current_minimum = times[j] - times[i];

        if (1440 - times[j] + times[i] < current_minimum)
          current_minimum = 1440 - times[j] + times[i];

      } else {
        if (times[i] - times[j] < current_minimum)
          current_minimum = times[i] - times[j];

        if (1440 - times[i] + times[j] < current_minimum)
          current_minimum = 1440 - times[i] + times[j];
      }
    }
  }

  return to_string(current_minimum);
}

int main() {

  // const string A[] = gets(stdin);
  // cout << TimeDifference(A, sizeof(A)/sizeof(*A));
  const string B[] = {"2:10pm", "1:30pm", "10:30am", "4:42pm"};
  cout << TimeDifference(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "40"
  const string C[] = {"1:10pm", "4:40am", "5:00pm"};
  cout << TimeDifference(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "230"
  const string D[] = {"10:00am", "11:45pm", "5:00am", "12:01am"};
  cout << TimeDifference(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "16"

  return 0;
}
