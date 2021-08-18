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

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

std::string trim(const std::string& src,
                 const string& chars_to_trim = " \t\n\f\v\r") {
  const std::unordered_set<char> trimmed_chars(
      chars_to_trim.c_str(), chars_to_trim.c_str() + chars_to_trim.length());

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const char ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return {};

  const auto last{
      std::find_if(std::crbegin(src), std::make_reverse_iterator(first),
                   [&trimmed_chars](const char ch) {
                     return trimmed_chars.find(ch) == std::cend(trimmed_chars);
                   })
          .base()};

  return {first, last};
}

pair<size_t, size_t> str_find_first_needle_position(
    const string& src,
    const vector<string>& needle_parts,
    const size_t start_pos = 0U) {
  const size_t not_found_index{string::npos};
  size_t first_needle_pos{not_found_index};
  size_t needle_len{};

  for (const auto& needle : needle_parts) {
    const size_t needle_start_pos = src.find(needle, start_pos);
    if (needle_start_pos < first_needle_pos) {
      first_needle_pos = needle_start_pos;
      needle_len = needle.length();
    }
  }

  return {first_needle_pos, needle_len};
}

vector<string> str_split(const string& src,
                         const string& needle,
                         const string& needle_parts_separator_token = "",
                         const bool split_on_whole_needle = true,
                         const bool ignore_empty_string = true,
                         const size_t max_count = string::npos) {
  const size_t src_len{src.length()};

  if (0U == src_len)
    return {};

  const size_t needle_len{needle.length()};

  if (0U == needle_len) {
    const size_t upper_limit{max_count < src_len ? max_count : src_len};
    std::vector<string> parts{};
    parts.reserve(upper_limit);
    for (size_t i{}; i < upper_limit; ++i)
      parts.emplace_back(1, src[i]);
    return parts;
  }

  const size_t needle_parts_separator_token_len{
      needle_parts_separator_token.length()};

  vector<string> needle_parts{};

  if (needle_parts_separator_token_len > 0U && !split_on_whole_needle) {
    size_t start_pos{};

    while (true) {
      const size_t next_pos{
          needle.find(needle_parts_separator_token, start_pos)};

      if (string::npos == next_pos) {
        needle_parts.emplace_back(
            needle.substr(start_pos, needle_len - start_pos));
        break;
      }

      needle_parts.emplace_back(needle.substr(start_pos, next_pos - start_pos));

      start_pos = next_pos + needle_parts_separator_token.length();
    }
  } else
    needle_parts.emplace_back(needle);

  vector<string> parts{};
  size_t number_of_parts{}, prev{};

  while (true) {
    const auto [current, needle_part_len] =
        str_find_first_needle_position(src, needle_parts, prev);

    if (string::npos == current || 0U == needle_part_len ||
        parts.size() == max_count)
      break;

    if (current - prev > 0U) {
      parts.emplace_back(std::cbegin(src) + prev, std::cbegin(src) + current);
      number_of_parts++;
    } else if (!ignore_empty_string) {
      parts.emplace_back();
      number_of_parts++;
    }

    prev = current + needle_part_len;

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

size_t parseTimeInMinutesFromString(const string& time) {
  const vector<string> time_parts_str{str_split(time, ":")};

  if (2 != time_parts_str.size())
    return 0;

  const size_t am_pm_start_char{time_parts_str[1].find_first_of("ap")};

  if (string::npos == am_pm_start_char)
    return 0;

  const string time_am_pm_str{time_parts_str[1].substr(am_pm_start_char, 2)};

  const size_t hour{stoul(time_parts_str[0])};

  const size_t minutes{stoul(time_parts_str[1].substr(0, am_pm_start_char))};

  return "am" == time_am_pm_str ? (hour % 12) * 60 + minutes
                                : (hour % 12) * 60 + 720 + minutes;
}

string TimeDifference(const string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 2)
    return 0;

  constexpr static size_t buffer_size{24 * 60};

  size_t minimum_time_difference{numeric_limits<size_t>::max()};
  array<bool, buffer_size> time_points{};

  for (size_t i{}; i < str_arr_size; ++i) {
    time_points[parseTimeInMinutesFromString(str_arr[i])] = true;
  }

  size_t first{};

  while (!time_points[first])
    ++first;

  size_t last{first};

  for (size_t next{first + 1}; next < time_points.size(); ++next) {
    if (time_points[next]) {
      if (next - last < minimum_time_difference) {
        minimum_time_difference = next - last;
        if (0 == minimum_time_difference)
          return "0";
      }
      last = next;
    }
  }

  if (1440 - last + first < minimum_time_difference)
    minimum_time_difference = 1440 - last + first;

  return to_string(minimum_time_difference);
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
