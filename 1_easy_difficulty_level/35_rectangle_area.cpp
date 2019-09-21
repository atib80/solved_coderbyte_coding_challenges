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

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

pair<int64_t, int64_t> parse_x_y_coordinate_pair(const string& str) {
  size_t start_pos{str.find_first_of("0123456789")};

  if (string::npos == start_pos)
    return {0, 0};

  size_t end_pos{str.find_first_not_of("0123456789", start_pos + 1)};

  if (string::npos == end_pos)
    return {0, 0};

  const int64_t x{stoll(str.substr(start_pos, end_pos - start_pos))};

  start_pos = str.find_first_of("0123456789", end_pos + 1);

  if (string::npos == start_pos)
    return {0, 0};

  end_pos = str.find_first_not_of("0123456789", start_pos + 1);

  if (string::npos == end_pos)
    end_pos = str.length();

  const int64_t y{stoll(str.substr(start_pos, end_pos - start_pos))};

  return {x, y};
}

string RectangleArea(vector<string> xy_coordinate_pairs) {
  if (xy_coordinate_pairs.size() < 4U)
    return "not possible";

  std::array<int64_t, 4U> x_coordinates;
  std::array<int64_t, 4U> y_coordinates;

  pair<int64_t, int64_t> coord{
      parse_x_y_coordinate_pair(xy_coordinate_pairs[0])};
  x_coordinates[0] = coord.first;
  y_coordinates[0] = coord.second;

  coord = parse_x_y_coordinate_pair(xy_coordinate_pairs[1]);
  x_coordinates[1] = coord.first;
  y_coordinates[1] = coord.second;

  coord = parse_x_y_coordinate_pair(xy_coordinate_pairs[2]);
  x_coordinates[2] = coord.first;
  y_coordinates[2] = coord.second;

  coord = parse_x_y_coordinate_pair(xy_coordinate_pairs[3]);
  x_coordinates[3] = coord.first;
  y_coordinates[3] = coord.second;

  const auto xmin_xmax{
      minmax_element(cbegin(x_coordinates), cend(x_coordinates))};
  const auto ymin_ymax{
      minmax_element(cbegin(y_coordinates), cend(y_coordinates))};

  const int64_t width{*(xmin_xmax.second) - *(xmin_xmax.first)};
  const int64_t height{*(ymin_ymax.second) - *(ymin_ymax.first)};

  return to_string(width * height);
}

int main() {
  // cout << RectangleArea(gets(stdin));
  cout << RectangleArea({"(0 0)", "(3 0)", "(0 2)", "(3 2)"})
       << '\n';  // expected output: "6"
  cout << RectangleArea({"(1 1)", "(1 3)", "(3 1)", "(3 3)"})
       << '\n';  // expected output: "4"
  cout << RectangleArea({"(0 0)", "(1 0)", "(1 1)", "(0 1)"})
       << '\n';  // expected output: "1"

  return 0;
}
