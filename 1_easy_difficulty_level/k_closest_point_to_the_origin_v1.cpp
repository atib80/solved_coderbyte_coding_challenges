#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

float distance(const pair<float, float>& point1,
               const pair<float, float>& point2 = pair<float, float>{0.f,
                                                                     0.f}) {
  return sqrt(pow(point1.first - point2.first, 2.f) +
              pow(point1.second - point2.second, 2.f));
}

vector<pair<float, float>> find_k_closest_points_to_origin(
    vector<pair<float, float>>& points,
    size_t k = 1) {
  if (k > points.size())
    k = points.size();

  stable_sort(begin(points), end(points),
              [](const pair<float, float>& p1, const pair<float, float>& p2) {
                return distance(p1) < distance(p2);
              });

  vector<pair<float, float>> k_closest_points{};

  copy(begin(points), begin(points) + k, back_inserter(k_closest_points));

  return k_closest_points;
}

pair<float, float> parse_x_y_coordinate_pair(const string& coordinates) {
  pair<float, float> coord{};

  size_t start{};

  start = coordinates.find_first_of("+-.eE0123456789", start);

  if (string::npos == start)
    return coord;

  size_t last{coordinates.find_first_not_of("+-.eE0123456789", start + 1)};

  if (string::npos == last) {
    coord.first = stof(coordinates.substr(start));
    return coord;
  }

  coord.first = stof(coordinates.substr(start, last - start));

  start = coordinates.find_first_of("+-.eE0123456789", last + 1);

  if (string::npos == start)
    return coord;

  last = coordinates.find_first_not_of("+-.eE0123456789", start + 1);

  if (string::npos == last) {
    coord.second = stof(coordinates.substr(start));
    return coord;
  }

  coord.second = stof(coordinates.substr(start, last - start));

  return coord;
}

vector<pair<float, float>> parse_2d_point_coordinates(string input) {
  vector<pair<float, float>> points{};

  size_t start{};

  while (start < input.length()) {
    start = input.find('(', start);

    if (string::npos == start)
      return points;

    const size_t last{input.find(')', start + 1)};

    if (string::npos == last)
      return points;

    points.emplace_back(
        parse_x_y_coordinate_pair(input.substr(start + 1, last - (start + 1))));

    start = last + 1;
  }

  return points;
}

int main() {
  cout << "Enter 2D point coordinates separated by space in the following "
          "format:\n (1,3) (-7,5) (12,8) ..., etc.\n [Press Enter to process input data.]\n";
  string input{};

  getline(cin, input);

  vector<pair<float, float>> points{parse_2d_point_coordinates(move(input))};

  cout << "Enter k parameter's value: ";
  size_t k{1};
  cin >> k;

  const vector<pair<float, float>> k_closest_points{
      find_k_closest_points_to_origin(points, k)};

  cout << "\n\nK closest points to the default origin (0,0) are the "
          "following:\n{ ";

  for (size_t i{}; i < k_closest_points.size(); i++) {
    cout << '(' << k_closest_points[i].first << ','
         << k_closest_points[i].second << ") ";
  }

  cout << "}\n";

  return 0;
}
