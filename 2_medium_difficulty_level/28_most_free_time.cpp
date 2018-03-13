/*
Coderbyte coding challenge: Most Free Time

Using the C++ language, have the function MostFreeTime(strArr) read the strArr
parameter being passed which will represent a full day and will be filled with
events that span from time X to time Y in the day. The format of each event will
be hh:mmAM/PM-hh:mmAM/PM. For example, strArr may be
["10:00AM-12:30PM","02:00PM-02:45PM","09:10AM-09:50AM"]. Your program will have
to output the longest amount of free time available between the start of your
first event and the end of your last event in the format: hh:mm. The start event
should be the earliest event in the day and the latest event should be the
latest event in the day. The output for the previous input would therefore be
01:30 (with the earliest event in the day starting at 09:10AM and the latest
event ending at 02:45PM). The input will contain at least 3 events and the
events may be out of order.

Sample test cases:

Input:  "12:15PM-02:00PM","09:00AM-10:00AM","10:30AM-12:00PM"
Output: "00:30"

Input:  "12:15PM-02:00PM","09:00AM-12:11PM","02:02PM-04:00PM"
Output: "00:04"
*/

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.length()};

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

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

pair<size_t, size_t> parse_event_start_and_end_time(const string& event_str) {
  vector<string> time_parts_str{split(event_str, "-")};

  for (auto& str : time_parts_str)
    str = trim(str);

  if (2 != time_parts_str.size())
    return make_pair(0, 0);

  vector<string> start_time_parts_str{split(time_parts_str[0], ":")};

  for (auto& str : start_time_parts_str)
    str = trim(str);

  if (2 != start_time_parts_str.size())
    return make_pair(0, 0);

  size_t am_pm_start_char{start_time_parts_str[1].find_first_of("apAP")};

  if (string::npos == am_pm_start_char)
    return make_pair(0, 0);

  string start_time_am_pm_str{
      start_time_parts_str[1].substr(am_pm_start_char, 2)};

  start_time_am_pm_str[0] = static_cast<char>(tolower(start_time_am_pm_str[0]));
  start_time_am_pm_str[1] = static_cast<char>(tolower(start_time_am_pm_str[1]));

  size_t start_time_hour{stoul(start_time_parts_str[0])};

  size_t start_time_minutes{
      stoul(start_time_parts_str[1].substr(0, am_pm_start_char))};

  const size_t start_time_in_minutes{
      "am" == start_time_am_pm_str
          ? (start_time_hour % 12) * 60 + start_time_minutes
          : (start_time_hour % 12) * 60 + 720 + start_time_minutes};

  vector<string> end_time_parts_str{split(time_parts_str[1], ":")};

  for (auto& str : end_time_parts_str)
    str = trim(str);

  if (2 != end_time_parts_str.size())
    return make_pair(0, 0);

  size_t am_pm_end_char{end_time_parts_str[1].find_first_of("apAP")};

  if (string::npos == am_pm_end_char)
    return make_pair(0, 0);

  string end_time_am_pm_str{end_time_parts_str[1].substr(am_pm_end_char, 2)};

  end_time_am_pm_str[0] = static_cast<char>(tolower(end_time_am_pm_str[0]));
  end_time_am_pm_str[1] = static_cast<char>(tolower(end_time_am_pm_str[1]));

  size_t end_time_hour{stoul(end_time_parts_str[0])};

  size_t end_time_minutes{
      stoul(end_time_parts_str[1].substr(0, am_pm_end_char))};

  const size_t end_time_in_minutes{
      "am" == end_time_am_pm_str
          ? (end_time_hour % 12) * 60 + end_time_minutes
          : (end_time_hour % 12) * 60 + 720 + end_time_minutes};

  return make_pair(start_time_in_minutes, end_time_in_minutes);
}

string MostFreeTime(string* str_arr, const size_t str_arr_size) {
  vector<size_t> start_end_times{};

  for (size_t i{}; i < str_arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);
    const pair<size_t, size_t> event_time{
        parse_event_start_and_end_time(str_arr[i])};
    start_end_times.emplace_back(event_time.first);
    start_end_times.emplace_back(event_time.second);
  }

  sort(begin(start_end_times), end(start_end_times));

  size_t max_free_time_period{};

  for (size_t i{1}; i < start_end_times.size() - 1; i += 2) {
    if (start_end_times[i + 1] - start_end_times[i] > max_free_time_period)
      max_free_time_period = start_end_times[i + 1] - start_end_times[i];
  }

  ostringstream oss{};

  oss << setfill('0') << setw(2) << max_free_time_period / 60 << ':' << setw(2)
      << max_free_time_period % 60;

  return oss.str();
}

int main() {
  // string A[] = gets(stdin);
  // cout << MostFreeTime(A, sizeof(A)/sizeof(*A));
  string B[] = {"10:00AM-12:30PM", "02:00PM-02:45PM", "09:10AM-09:50AM"};
  cout << MostFreeTime(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "01:30"
  string C[] = {"12:15PM-02:00PM", "09:00AM-10:00AM", "10:30AM-12:00PM"};
  cout << MostFreeTime(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "00:30"
  string D[] = {"12:15PM-02:00PM", "09:00AM-12:11PM", "02:02PM-04:00PM"};
  cout << MostFreeTime(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "00:04"

  return 0;
}
