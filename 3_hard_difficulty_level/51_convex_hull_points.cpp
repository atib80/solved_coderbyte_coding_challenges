/*
Coderbyte coding challenge: Convex Hull Points

Using the C++ language, have the function ConvexHullPoints(strArr) take strArr
which will be an array of integer coordinates that exist on a Cartesian plane in
the form: (x,y). Your program should return the minimum number of points that
are needed to form a convex hull around all the points. For example: if the
input is ["(2,2)", "(3,1)", "(2,6)", "(0,-2)"] then your program should return 3
because only 3 points are needed to create a convex hull that encloses all the
points. The input array will always contain at least 3 points.

Sample test cases:

Input:  "(2,2)", "(3,1)", "(2,6)", "(0,1)", "(2,3)", "(5,2)"
Output: 4

Input:  "(0,1)", "(3,6)", "(2,2)", "(0,7)"
Output: 4
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Point {
  Point(const int x_val = 0, const int y_val = 0) : x{x_val}, y{y_val} {}

  int x;
  int y;
};

inline Point next_to_top(const vector<Point>& v) {
  return v[v.size() - 2];
}

inline void swap(Point& p1, Point& p2) noexcept {
  std::swap(p1.x, p2.x);
  std::swap(p1.y, p2.y);
}

inline int distance(const Point& p1, const Point& p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

inline int orientation(const Point& p, const Point& q, const Point& r) {
  const int orientation{(q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y)};

  if (!orientation)
    return 0;

  return orientation > 0 ? 1 : 2;
}

size_t find_convex_hull(vector<Point>& points) {
  int ymin{points[0].y};
  size_t min_index{};

  for (size_t i{1}; i < points.size(); i++) {
    if ((points[i].y < ymin) ||
        ((points[i].y == ymin) && (points[i].x < points[min_index].x))) {
      ymin = points[i].y;
      min_index = i;
    }
  }

  swap(points[0], points[min_index]);

  Point p0{points[0]};

  sort(begin(points) + 1, end(points), [&](const Point& p1, const Point& p2) {
    const int orient_factor{orientation(p0, p1, p2)};

    if (!orient_factor)
      return distance(p0, p2) >= distance(p0, p1);

    return 2 == orient_factor;
  });

  vector<Point> s{};
  for (size_t i{}; i < 3; i++)
    s.emplace_back(points[i]);

  for (size_t i{3}; i < points.size(); i++) {
    while (2 != orientation(next_to_top(s), s.back(), points[i]))
      s.pop_back();

    s.emplace_back(points[i]);
  }

  return s.size();
}

Point parse_coordinate_pair_values(const string& str) {
  Point point{};
  size_t si{str.find_first_of("-+1234567890")};
  if (string::npos == si)
    return point;
  size_t ei{str.find(',', si + 1)};
  if (string::npos == ei)
    return point;
  point.x = stoi(str.substr(si, ei - si));

  si = str.find_first_of("-+1234567890", ei + 1);
  if (string::npos == si)
    return point;
  ei = str.find_first_not_of("-+1234567890", si + 1);
  if (string::npos == ei)
    point.y = stoi(str.substr(si));
  else
    point.y = stoi(str.substr(si, ei - si));

  return point;
}

string ConvexHullPoints(string* str_arr, const size_t str_arr_size) {
  vector<Point> points{};

  for (size_t i{}; i < str_arr_size; i++) {
    points.emplace_back(parse_coordinate_pair_values(str_arr[i]));
  }

  return to_string(find_convex_hull(points));
}

int main() {
  // string A[] = gets(stdin);
  // cout << ConvexHullPoints(A, sizeof(A)/sizeof(*A));
  string B[] = {"(2,2)", "(3,1)", "(2,6)", "(0,-2)"};
  cout << ConvexHullPoints(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "3"
  string C[] = {"(2,2)", "(3,1)", "(2,6)", "(0,1)", "(2,3)", "(5,2)"};
  cout << ConvexHullPoints(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "4"
  string D[] = {"(0,1)", "(3,6)", "(2,2)", "(0,7)"};
  cout << ConvexHullPoints(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "4"

  return 0;
}
