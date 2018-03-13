/*
Coderbyte coding challenge: Overlapping Rectangles

Using the C++ language, have the function OverlappingRectangles(strArr) read the
strArr parameter being passed which will represent two rectangles on a Cartesian
coordinate plane and will contain 8 coordinates with the first 4 making up
rectangle 1 and the last 4 making up rectange 2. It will be in the following
format: ["(0,0),(2,2),(2,0),(0,2),(1,0),(1,2),(6,0),(6,2)"] Your program should
determine the area of the space where the two rectangles overlap, and then
output the number of times this overlapping region can fit into the first
rectangle. For the above example, the overlapping region makes up a rectangle of
area 2, and the first rectangle (the first 4 coordinates) makes up a rectangle
of area 4, so your program should output 2. The coordinates will all be
integers. If there's no overlap between the two rectangles return 0.

Sample test cases:

Input:  "(0,0),(0,-2),(3,0),(3,-2),(2,-1),(3,-1),(2,3),(3,3)"
Output: 6

Input:  "(0,0),(5,0),(0,2),(5,2),(2,1),(5,1),(2,-1),(5,-1)"
Output: 3
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
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

pair<int, int> find_min_max_x_coord(
    const vector<pair<int, int>> rectangle_coordinates) {
  const auto min_max_x_coord_iter_pair =
      minmax_element(begin(rectangle_coordinates), end(rectangle_coordinates),
                     [](const pair<int, int>& lp, const pair<int, int>& rp) {
                       return lp.first < rp.first;
                     });

  return make_pair(min_max_x_coord_iter_pair.first->first,
                   min_max_x_coord_iter_pair.second->first);
}

pair<int, int> find_min_max_y_coord(
    const vector<pair<int, int>> rectangle_coordinates) {
  const auto min_max_y_coord_iter_pair =
      minmax_element(begin(rectangle_coordinates), end(rectangle_coordinates),
                     [](const pair<int, int>& lp, const pair<int, int>& rp) {
                       return lp.second < rp.second;
                     });

  return make_pair(min_max_y_coord_iter_pair.first->second,
                   min_max_y_coord_iter_pair.second->second);
}

pair<int, int> parse_x_y_coordinates(const string& str) {
  size_t start_pos{str.find_first_of("-+0123456789")};

  if (string::npos == start_pos)
    return make_pair(0, 0);

  size_t end_pos{str.find_first_not_of("-+0123456789", start_pos + 1)};

  if (string::npos == end_pos)
    return make_pair(0, 0);

  const int x{stoi(str.substr(start_pos, end_pos - start_pos))};

  start_pos = str.find_first_of("-+0123456789", end_pos + 1);

  if (string::npos == start_pos)
    return make_pair(0, 0);

  end_pos = str.find_first_not_of("-+0123456789", start_pos + 1);

  const int y{string::npos != end_pos
                  ? stoi(str.substr(start_pos, end_pos - start_pos))
                  : stoi(str.substr(start_pos))};

  return make_pair(x, y);
}

vector<pair<int, int>> parse_rectangle_coordinates(const string& input) {
  vector<string> coordinates_str{split(input, "),(")};

  if (8 != coordinates_str.size())
    return vector<pair<int, int>>{};

  for (auto& str : coordinates_str)
    str = trim(str);

  coordinates_str[0].erase(begin(coordinates_str[0]));
  coordinates_str[7].erase(--end(coordinates_str[7]));

  vector<pair<int, int>> first_rectangle_coordinates{};
  vector<pair<int, int>> second_rectangle_coordinates{};

  for (size_t i{}, j{4}; i != 4; i++, j++) {
    first_rectangle_coordinates.emplace_back(
        parse_x_y_coordinates(coordinates_str[i]));
    second_rectangle_coordinates.emplace_back(
        parse_x_y_coordinates(coordinates_str[j]));
  }

  const pair<int, int> min_max_x1{
      find_min_max_x_coord(first_rectangle_coordinates)};
  const int min_x1{min_max_x1.first};
  const int max_x1{min_max_x1.second};

  const pair<int, int> min_max_x2{
      find_min_max_x_coord(second_rectangle_coordinates)};
  const int min_x2{min_max_x2.first};
  const int max_x2{min_max_x2.second};

  const pair<int, int> min_max_y1{
      find_min_max_y_coord(first_rectangle_coordinates)};
  const int min_y1{min_max_y1.first};
  const int max_y1{min_max_y1.second};

  const pair<int, int> min_max_y2{
      find_min_max_y_coord(second_rectangle_coordinates)};
  const int min_y2{min_max_y2.first};
  const int max_y2{min_max_y2.second};

  return vector<pair<int, int>>{min_max_x1, min_max_y1, min_max_x2, min_max_y2};
}

string calculate_area_of_overlapping_rectangle(
    const vector<pair<int, int>>& rect_coordinates) {
  const int min_x1{rect_coordinates[0].first};
  const int max_x1{rect_coordinates[0].second};
  const int min_y1{rect_coordinates[1].first};
  const int max_y1{rect_coordinates[1].second};

  const int min_x2{rect_coordinates[2].first};
  const int max_x2{rect_coordinates[2].second};
  const int min_y2{rect_coordinates[3].first};
  const int max_y2{rect_coordinates[3].second};

  if (max_x1 <= min_x2 || max_y1 <= min_y2)
    return "0";

  if (max_x2 <= min_x1 || max_y2 <= min_y1)
    return "0";

  const int first_rectangle_area{(max_x1 - min_x1) * (max_y1 - min_y1)};

  vector<int> overlapped_rectangle_x_coord{min_x1, max_x1, min_x2, max_x2};

  sort(begin(overlapped_rectangle_x_coord), end(overlapped_rectangle_x_coord));

  vector<int> overlapped_rectangle_y_coord{min_y1, max_y1, min_y2, max_y2};

  sort(begin(overlapped_rectangle_y_coord), end(overlapped_rectangle_y_coord));

  const int overlapped_rectangle_area{
      (overlapped_rectangle_x_coord[2] - overlapped_rectangle_x_coord[1]) *
      (overlapped_rectangle_y_coord[2] - overlapped_rectangle_y_coord[1])};

  return to_string(first_rectangle_area / overlapped_rectangle_area);
}

string OverlappingRectangles(string* str_arr, const size_t str_arr_size) {
  if (!str_arr || !str_arr_size)
    return "not possible";

  const vector<pair<int, int>> coordinates{
      parse_rectangle_coordinates(*str_arr)};

  return calculate_area_of_overlapping_rectangle(coordinates);
}

int main() {
  // string A[] = gets(stdin);
  // cout << OverlappingRectangles(A, sizeof(A)/sizeof(*A));
  string B[] = {"(0,0),(2,2),(2,0),(0,2),(1,0),(1,2),(6,0),(6,2)"};
  cout << OverlappingRectangles(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 2
  string C[] = {"(0,0),(0,-2),(3,0),(3,-2),(2,-1),(3,-1),(2,3),(3,3)"};
  cout << OverlappingRectangles(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 6
  string D[] = {"(0,0),(5,0),(0,2),(5,2),(2,1),(5,1),(2,-1),(5,-1)"};
  cout << OverlappingRectangles(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 3

  return 0;
}
