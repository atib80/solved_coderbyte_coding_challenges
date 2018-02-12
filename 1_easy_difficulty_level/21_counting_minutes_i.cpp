/*
Coderbyte coding challenge:

Using the C++ language, have the function CountingMinutesI(str) take the str
parameter being passed which will be two times (each properly formatted with a
colon and am or pm) separated by a hyphen and return the total number of minutes
between the two times. The time will be in a 12 hour clock format. For example:
if str is 9:00am-10:00am then the output should be 60. If str is 1:00pm-11:00am
the output should be 1320.

Sample test cases:

Input:  "12:30pm-12:00am"
Output: 690

Input:  "1:23am-1:08am"
Output: 1425
*/

#include <cctype>
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

string counting_minutes_i(string str) {
  str = trim(str);

  const vector<string> times_str{split(str, "-")};

  if (2u != times_str.size())
    return string{"Not possible!"};

  const vector<string> start_times_str{split(times_str[0], ":")};

  if (2u != start_times_str.size())
    return string{"Not possible!"};

  const vector<string> end_times_str{split(times_str[1], ":")};

  if (2u != end_times_str.size())
    return string{"Not possible!"};

  const size_t am_pm_start_char{start_times_str[1].find_first_of("ap")};

  if (string::npos == am_pm_start_char)
    return string{"Not possible!"};

  const string start_time_am_pm_str{
      start_times_str[1].substr(am_pm_start_char, 2)};

  const size_t start_hour{stoul(start_times_str[0])};

  const size_t start_minutes{
      stoul(start_times_str[1].substr(0, am_pm_start_char))};

  const size_t am_pm_end_char{end_times_str[1].find_first_of("ap")};

  if (string::npos == am_pm_end_char)
    return string{"Not possible!"};

  const string end_time_am_pm_str{end_times_str[1].substr(am_pm_end_char, 2)};

  const size_t end_hour{stoul(end_times_str[0])};

  const size_t end_minutes{stoul(end_times_str[1].substr(0, am_pm_end_char))};

  size_t start_time_in_minutes{
      ("am" == start_time_am_pm_str)
          ? (((start_hour % 12) * 60) + start_minutes)
          : (((start_hour % 12) * 60) + 720 + start_minutes)};

  const size_t end_time_in_minutes{
      ("am" == end_time_am_pm_str)
          ? (((end_hour % 12) * 60) + end_minutes)
          : (((end_hour % 12) * 60) + 720 + end_minutes)};

  if (start_time_in_minutes > end_time_in_minutes) {
    start_time_in_minutes = 1440 - start_time_in_minutes;

    return to_string(start_time_in_minutes + end_time_in_minutes);
  }

  return to_string(end_time_in_minutes - start_time_in_minutes);
}

int main() {
  // cout << counting_minutes_i(move(string{gets(stdin)}));
  cout << counting_minutes_i(move(string{"9:00am-10:00am"}))
       << '\n';  // expected output: "60"
  cout << counting_minutes_i(move(string{"1:00pm-11:00am"}))
       << '\n';  // expected output: "1320"
  cout << counting_minutes_i(move(string{"12:30pm-12:00am"}))
       << '\n';  // expected output: "690"
  cout << counting_minutes_i(move(string{"1:23am-1:08am"}))
       << '\n';  // expected output: "1425"

  return 0;
}
