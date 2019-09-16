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

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

std::string trim(const std::string& src,
                 const char* chars_to_trim = " \t\n\f\v\r") {
  if (0U == src.length())
    return {};

  const std::unordered_set<char> trimmed_chars(
      chars_to_trim, chars_to_trim + strlen(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const char ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return {};

  const auto last{std::find_if(std::crbegin(src), std::crend(src),
                               [&trimmed_chars](const char ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return {first, last};
}

std::string to_lower_case(const std::string& src,
                          const std::locale& loc = std::locale{}) {
  std::string src_lc{src};

  if (std::has_facet<std::ctype<char>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char>>(loc);
    std::transform(std::cbegin(src_lc), std::cend(src_lc), std::begin(src_lc),
                   [&f](const char ch) { return f.tolower(ch); });

  } else {
    std::transform(
        std::cbegin(src_lc), std::cend(src_lc), std::begin(src_lc),
        [](const char ch) { return static_cast<char>(std::tolower(ch)); });
  }

  return src_lc;
}

std::vector<std::string> split(const std::string& src,
                               const char* needle,
                               const bool split_on_whole_needle = true,
                               const bool ignore_empty_string = true,
                               size_t const max_count = std::string::npos) {
  const size_t src_len{src.length()};

  if (0U == src_len)
    return {};

  size_t needle_len{strlen(needle)};

  if (0U == needle_len) {
    const size_t upper_limit{max_count < src_len ? max_count : src_len};
    std::vector<std::string> parts{};
    parts.reserve(upper_limit);
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, src[i]);
    return parts;
  }

  if (!split_on_whole_needle)
    needle_len = 1U;

  std::vector<std::string> parts{};
  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current = split_on_whole_needle
                               ? src.find(needle, prev)
                               : src.find_first_of(needle, prev);

    if (std::string::npos == current)
      break;

    if (parts.size() == max_count)
      break;

    if (current - prev > 0 || !ignore_empty_string) {
      if (current - prev > 0)
        parts.emplace_back(std::cbegin(src) + prev, std::cbegin(src) + current);
      else if (!ignore_empty_string)
        parts.emplace_back();

      number_of_parts++;
    }

    prev = current + needle_len;

    if (prev >= src_len)
      break;
  }

  if (parts.size() < max_count) {
    if (prev < src_len)
      parts.emplace_back(std::cbegin(src) + prev, std::cend(src));
    else if (!ignore_empty_string)
      parts.emplace_back();
  }

  return parts;
}

// input: "1:00pm-11:00am"
string counting_minutes_i(string str) {
  str = trim(str);

  const vector<string> times_str{split(str, "-")};

  if (2U != times_str.size())
    return "Not possible!";

  const vector<string> start_times_str{split(times_str[0], ":")};

  if (2U != start_times_str.size())
    return "Not possible!";

  const vector<string> end_times_str{split(times_str[1], ":")};

  if (2U != end_times_str.size())
    return "Not possible!";

  const size_t am_pm_start_char{start_times_str[1].find_first_of("ap")};

  if (string::npos == am_pm_start_char)
    return "Not possible!";

  const string start_time_am_pm_str{
      to_lower_case(start_times_str[1].substr(am_pm_start_char, 2))};

  const size_t start_hour =
      2U == start_times_str[0].length()
          ? (start_times_str[0][0] - '0') * 10 + (start_times_str[0][1] - '0')
          : start_times_str[0][0] - '0';

  const size_t start_minutes =
      4U == start_times_str[1].length()
          ? (start_times_str[1][0] - '0') * 10 + (start_times_str[1][1] - '0')
          : start_times_str[1][0] - '0';

  const size_t am_pm_end_char{end_times_str[1].find_first_of("ap")};

  if (string::npos == am_pm_end_char)
    return "Not possible!";

  const string end_time_am_pm_str{
      to_lower_case(end_times_str[1].substr(am_pm_end_char, 2))};

  const size_t end_hour =
      2U == end_times_str[0].length()
          ? (end_times_str[0][0] - '0') * 10 + (end_times_str[0][1] - '0')
          : end_times_str[0][0] - '0';

  const size_t end_minutes =
      4U == end_times_str[1].length()
          ? (end_times_str[1][0] - '0') * 10 + (end_times_str[1][1] - '0')
          : end_times_str[1][0] - '0';

  const size_t start_time_in_minutes{
      "am" == start_time_am_pm_str
          ? (start_hour % 12) * 60 + start_minutes
          : 720 + (start_hour % 12) * 60 + start_minutes};

  const size_t end_time_in_minutes{
      "am" == end_time_am_pm_str ? (end_hour % 12) * 60 + end_minutes
                                 : 720 + (end_hour % 12) * 60 + end_minutes};

  if (start_time_in_minutes > end_time_in_minutes)
    return to_string(1440U - start_time_in_minutes + end_time_in_minutes);

  return to_string(end_time_in_minutes - start_time_in_minutes);
}

int main() {
  // cout << counting_minutes_i(gets(stdin));
  cout << counting_minutes_i("9:00am-10:00am")
       << '\n';  // expected output: "60"
  cout << counting_minutes_i("1:00pm-11:00am")
       << '\n';  // expected output: "1320"
  cout << counting_minutes_i("12:30pm-12:00am")
       << '\n';  // expected output: "690"
  cout << counting_minutes_i("1:23am-1:08am")
       << '\n';  // expected output: "1425"

  return 0;
}
