/*
Coderbyte coding challenge: Closest Enemy II

Using the C++ language, have the function ClosestEnemyII(strArr) read the matrix
of numbers stored in strArr which will be a 2D matrix that contains only the
integers 1, 0, or 2. Then from the position in the matrix where a 1 is, return
the number of spaces either left, right, down, or up you must move to reach an
enemy which is represented by a 2. You are able to wrap around one side of the
matrix to the other as well. For example: if strArr is ["0000", "1000", "0002",
"0002"] then this looks like the following:

0 0 0 0
1 0 0 0
0 0 0 2
0 0 0 2

For this input your program should return 2 because the closest enemy (2) is 2
spaces away from the 1 by moving left to wrap to the other side and then moving
down once. The array will contain any number of 0's and 2's, but only a
single 1. It may not contain any 2's at all as well, where in that case your
program should return a 0.

Sample test cases:

Input:  "000", "100", "200"
Output: 1

Input:  "0000", "2010", "0000", "2002"
Output: 2
*/

#include <cctype>
#include <iostream>
#include <set>
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

size_t abs_diff(const size_t x, const size_t y) {
  return (x < y ? y - x : x - y);
}

size_t find_closest_distance_to_enemy(const pair<size_t, size_t>& one_pos,
                                      const pair<size_t, size_t>& enemy_pos,
                                      const size_t row_count,
                                      const size_t column_count) {
  set<size_t> distances{};

  const size_t one_x{one_pos.first};
  const size_t one_y{one_pos.second};
  const size_t enemy_x{enemy_pos.first};
  const size_t enemy_y{enemy_pos.second};

  const size_t enemy_x_one_x_direct_distance{abs_diff(enemy_x, one_x)};
  const size_t enemy_y_one_y_direct_distance{abs_diff(enemy_y, one_y)};

  distances.insert(enemy_x_one_x_direct_distance +
                   enemy_y_one_y_direct_distance);

  size_t row_distance_opposite_dir, column_distance_opposite_dir;

  if (one_x < enemy_x) {
    row_distance_opposite_dir = one_x + row_count - enemy_x;
    distances.insert(row_distance_opposite_dir + enemy_y_one_y_direct_distance);
  } else if (one_x > enemy_x) {
    row_distance_opposite_dir = row_count - one_x + enemy_x;
    distances.insert(row_distance_opposite_dir + enemy_y_one_y_direct_distance);
  }

  if (one_y < enemy_y) {
    column_distance_opposite_dir = one_y + column_count - enemy_y;
    distances.insert(column_distance_opposite_dir +
                     enemy_x_one_x_direct_distance);
  } else if (one_y > enemy_y) {
    column_distance_opposite_dir = column_count - one_y + enemy_y;
    distances.insert(column_distance_opposite_dir +
                     enemy_x_one_x_direct_distance);
  }

  return *begin(distances);
}

size_t find_distance_to_closest_enemy_position(
    const pair<size_t, size_t>& one_pos,
    const vector<pair<size_t, size_t>>& two_pos,
    const size_t row_count,
    const size_t col_count) {
  vector<size_t> distances{};

  for (const auto& enemy_pos : two_pos) {
    distances.emplace_back(find_closest_distance_to_enemy(
        one_pos, enemy_pos, row_count, col_count));
  }

  size_t current_min_steps{distances[0]};

  for (size_t i{1u}; i < distances.size(); i++) {
    if (distances[i] < current_min_steps)
      current_min_steps = distances[i];
  }

  return current_min_steps;
}

string closest_enemy_ii(string* str_array, const size_t str_array_size) {
  bool found_one{false}, found_twos{false};
  pair<size_t, size_t> one_position{};
  vector<pair<size_t, size_t>> enemy_positions{};

  for (size_t i{}; i < str_array_size; i++) {
    str_array[i] = trim(str_array[i]);
    for (size_t j{}; j != str_array[i].length(); j++) {
      if ('2' == str_array[i][j]) {
        enemy_positions.emplace_back(make_pair(i, j));
        found_twos = true;
        continue;
      }

      if (!found_one && ('1' == str_array[i][j])) {
        one_position = make_pair(i, j);
        found_one = true;
      }
    }
  }

  if (!found_one || !found_twos)
    return "0";

  return to_string(find_distance_to_closest_enemy_position(
      one_position, enemy_positions, str_array_size, str_array[0].length()));
}

int main() {
  // string matrix[] = gets(stdin);
  // cout << closest_enemy_ii(matrix, sizeof(matrix) / sizeof(matrix[0]));

  string m1[] = {"10", "02"};
  cout << closest_enemy_ii(m1, sizeof(m1) / sizeof(m1[0]))
       << '\n';  // expected output: 2

  string m2[] = {"00000", "10000", "00000", "00002", "02002"};
  cout << closest_enemy_ii(m2, sizeof(m2) / sizeof(m2[0]))
       << '\n';  // expected output: 3

  string m3[] = {"0000000", "0001000", "0000000", "0000000",
                 "0000000", "2000000", "0000000"};
  cout << closest_enemy_ii(m3, sizeof(m3) / sizeof(m3[0]))
       << '\n';  // expected output: 6

  string m4[] = {"0000", "1000", "0002", "0002"};
  cout << closest_enemy_ii(m4, sizeof(m4) / sizeof(m4[0]))
       << '\n';  // expected output: 2

  string m5[] = {"000", "100", "200"};
  cout << closest_enemy_ii(m5, sizeof(m5) / sizeof(m5[0]))
       << '\n';  // expected output: 1

  string m6[] = {"0000", "2010", "0000", "2002"};
  cout << closest_enemy_ii(m6, sizeof(m6) / sizeof(m6[0]))
       << '\n';  // expected output: 2

  return 0;
}
