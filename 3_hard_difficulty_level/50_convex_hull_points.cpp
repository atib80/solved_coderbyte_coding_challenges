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
#include <stack>
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

struct Point {
  Point(const int x_val = 0, const int y_val = 0) : x{x_val}, y{y_val} {}

  int x;
  int y;
};

Point next_to_top(stack<Point>& s) {
  const Point p{s.top()};

  s.pop();

  const Point res{s.top()};

  s.emplace(p);

  return res;
}

void swap(Point& p1, Point& p2) noexcept {
  const Point temp{p1};

  p1 = p2;

  p2 = temp;
}

int distance(const Point& p1, const Point& p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(const Point& p, const Point& q, const Point& r) {
  const int orientation{(q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y)};

  if (!orientation)
    return 0;

  return (orientation > 0) ? 1 : 2;
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
    const int o{orientation(p0, p1, p2)};

    if (!o)
      return distance(p0, p2) >= distance(p0, p1);

    return 2 == o;
  });

  stack<Point> s{};
  for (size_t i{}; i < 3; i++)
    s.emplace(points[i]);

  for (size_t i{3}; i < points.size(); i++) {
    while (2 != orientation(next_to_top(s), s.top(), points[i]))
      s.pop();

    s.emplace(points[i]);
  }

  return s.size();
}

string ConvexHullPoints(string* str_arr, const size_t str_arr_size) {
  vector<Point> points{};

  for (size_t i{}; i != str_arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);
    str_arr[i].erase(begin(str_arr[i]));
    str_arr[i].erase(--end(str_arr[i]));

    auto const coordinates_str = split(str_arr[i], ",", 2);

    if (coordinates_str.size() < 2u)
      continue;

    points.emplace_back(stoi(coordinates_str[0]), stoi(coordinates_str[1]));
  }

  return to_string(find_convex_hull(points));
}

int main() {
	
  // string A[] = gets(stdin);
  // cout << ConvexHullPoints(A, sizeof(A)/sizeof(*A));
  string B[] = {"(2,2)", "(3,1)", "(2,6)", "(0,-2)"};
  cout << ConvexHullPoints(B, sizeof(B) / sizeof(*B)) << '\n';  // expected output: "3"
  string C[] = {"(2,2)", "(3,1)", "(2,6)", "(0,1)", "(2,3)", "(5,2)"};
  cout << ConvexHullPoints(C, sizeof(C) / sizeof(*C)) << '\n';  // expected output: "4"
  string D[] = {"(0,1)", "(3,6)", "(2,2)", "(0,7)"};
  cout << ConvexHullPoints(D, sizeof(D) / sizeof(*D)) << '\n';  // expected output: "4"

  return 0;
}
