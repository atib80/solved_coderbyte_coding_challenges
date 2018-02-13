/*
Coderbyte coding challenge: Rectangle Area

Using the C++ language, have the function RectangleArea(strArr) take the array
of strings stored in strArr, which will only contain 4 elements and be in the
form (x y) where x and y are both integers, and return the area of the rectangle
formed by the 4 points on a Cartesian grid. The 4 elements will be in arbitrary
order. For example: if strArr is ["(0 0)", "(3 0)", "(0 2)", "(3 2)"] then your
program should return 6 because the width of the rectangle is 3 and the height
is 2 and the area of a rectangle is equal to the width * height.

Sample test cases:

Input:  "(1 1)","(1 3)","(3 1)","(3 3)"
Output: 4

Input:  "(0 0)","(1 0)","(1 1)","(0 1)"
Output: 1
*/

#include <cmath>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
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

pair<int, int> parse_x_y_coordinate_pair(const string& str) {
  size_t start_pos{str.find_first_of("0123456789")};

  if (string::npos == start_pos)
    return make_pair(0, 0);

  size_t end_pos{str.find_first_not_of("0123456789", start_pos + 1)};

  if (string::npos == end_pos)
    return make_pair(0, 0);

  const int x{stoi(str.substr(start_pos, end_pos - start_pos))};

  start_pos = str.find_first_of("0123456789", end_pos + 1);

  if (string::npos == start_pos)
    return make_pair(0, 0);

  end_pos = str.find_first_not_of("0123456789", start_pos + 1);

  const int y{string::npos != end_pos
                  ? stoi(str.substr(start_pos, end_pos - start_pos))
                  : stoi(str.substr(start_pos))};

  return make_pair(x, y);
}

string RectangleArea(vector<string> xy_coordinate_pairs) {
  if (xy_coordinate_pairs.size() != 4u)
    return "Not possible!";

  vector<pair<int, int>> coordinates{};

  for (const auto& xy_str : xy_coordinate_pairs) {
    coordinates.emplace_back(parse_x_y_coordinate_pair(xy_str));
  }

  set<int, greater<int>> x_coordinates{};
  set<int, greater<int>> y_coordinates{};

  for (const auto& xy_pair : coordinates) {
    x_coordinates.insert(xy_pair.first);
    y_coordinates.insert(xy_pair.second);
  }

  if (1u == x_coordinates.size() || 1u == y_coordinates.size())
    return "0";

  const auto first_x = begin(x_coordinates);
  auto second_x = first_x;
  ++second_x;
  const int width{*first_x - *second_x};

  const auto first_y = begin(y_coordinates);
  auto second_y = first_y;
  ++second_y;
  const int height{*first_y - *second_y};

  return to_string(width * height);
}

int main() {
  // cout << RectangleArea(move(vector<string>{gets(stdin)}));
  cout << RectangleArea(
              move(vector<string>{"(0 0)", "(3 0)", "(0 2)", "(3 2)"}))
       << '\n';  // expected output: "6"
  cout << RectangleArea(
              move(vector<string>{"(1 1)", "(1 3)", "(3 1)", "(3 3)"}))
       << '\n';  // expected output: "4"
  cout << RectangleArea(
              move(vector<string>{"(0 0)", "(1 0)", "(1 1)", "(0 1)"}))
       << '\n';  // expected output: "1"

  return 0;
}
