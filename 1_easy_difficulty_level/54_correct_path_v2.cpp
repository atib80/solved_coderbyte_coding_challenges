/*
Coderbyte coding challenge: Correct Path v2
(iterative solution using queue<T>)

Using the C++ language, have the function CorrectPath(str) read the str
parameter being passed, which will represent the movements made in a 5x5 grid of
cells starting from the top left position. The characters in the input string
will be entirely composed of: r, l, u, d, ?. Each of the characters stand for
the direction to take within the grid, for example: r = right, l = left, u = up,
d = down. Your goal is to determine what characters the question marks should be
in order for a path to be created to go from the top left of the grid all the
way to the bottom right without touching previously travelled on cells in the
grid.

For example: if str is "r?d?drdd" then your program should output the final
correct string that will allow a path to be formed from the top left of a 5x5
grid to the bottom right. For this input, your program should therefore return
the string rrdrdrdd. There will only ever be one correct path and there will
always be at least one question mark within the input string.

Sample test cases:

Input:  "???rrurdr?"
Output: "dddrrurdrd"

Input:  "drdr??rrddd?"
Output: "drdruurrdddd"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_set>

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

size_t distance(const size_t x_src,
                const size_t y_src,
                const size_t x_dst = 4,
                const size_t y_dst = 4) {
  return ((x_src <= x_dst ? x_dst - x_src : x_src - x_dst) +
          (y_src <= y_dst ? y_dst - y_src : y_src - y_dst));
}

string CorrectPath_v2(string path) {
  path = trim(path);
  const size_t path_len{path.length()};

  queue<tuple<size_t, size_t, size_t, string, unordered_set<size_t>>> q{
      {make_tuple(0, 0, 0, path, unordered_set<size_t>{})}};

  while (!q.empty()) {
    const size_t x{get<0>(q.front())};
    const size_t y{get<1>(q.front())};
    const size_t current_path_index{get<2>(q.front())};
    string current_path{move(get<3>(q.front()))};
    unordered_set<size_t> already_visited_coordinates{move(get<4>(q.front()))};
    q.pop();

    if (x == 4 && y == 4 && current_path_index == path_len)
      return current_path;

    if (distance(x, y, 4, 4) > path_len - current_path_index)
      continue;

    already_visited_coordinates.insert(x * 5 + y);

    if ('u' == current_path[current_path_index]) {
      if (x > 0 && !already_visited_coordinates.count((x - 1) * 5 + y))
        q.emplace(make_tuple(x - 1, y, current_path_index + 1, current_path,
                             already_visited_coordinates));
      else
        continue;
    }

    else if ('d' == current_path[current_path_index]) {
      if (x < 4 && !already_visited_coordinates.count((x + 1) * 5 + y))
        q.emplace(make_tuple(x + 1, y, current_path_index + 1, current_path,
                             already_visited_coordinates));
      else
        continue;
    }

    else if ('l' == current_path[current_path_index]) {
      if (y > 0 && !already_visited_coordinates.count(x * 5 + y - 1))
        q.emplace(make_tuple(x, y - 1, current_path_index + 1, current_path,
                             already_visited_coordinates));
      else
        continue;
    }

    else if ('r' == current_path[current_path_index]) {
      if (y < 4 && !already_visited_coordinates.count(x * 5 + y + 1))
        q.emplace(make_tuple(x, y + 1, current_path_index + 1, current_path,
                             already_visited_coordinates));
      else
        continue;
    }

    else if ('?' == path[current_path_index]) {
      if (x > 0 && !already_visited_coordinates.count((x - 1) * 5 + y)) {
        current_path[current_path_index] = 'u';
        q.emplace(make_tuple(x - 1, y, current_path_index + 1, current_path,
                             already_visited_coordinates));
        current_path[current_path_index] = '?';
      }

      if (x < 4 && !already_visited_coordinates.count((x + 1) * 5 + y)) {
        current_path[current_path_index] = 'd';
        q.emplace(make_tuple(x + 1, y, current_path_index + 1, current_path,
                             already_visited_coordinates));
        current_path[current_path_index] = '?';
      }

      if (y > 0 && !already_visited_coordinates.count(x * 5 + y - 1)) {
        current_path[current_path_index] = 'l';
        q.emplace(make_tuple(x, y - 1, current_path_index + 1, current_path,
                             already_visited_coordinates));
        current_path[current_path_index] = '?';
      }

      if (y < 4 && !already_visited_coordinates.count(x * 5 + y + 1)) {
        current_path[current_path_index] = 'r';
        q.emplace(make_tuple(x, y + 1, current_path_index + 1, current_path,
                             already_visited_coordinates));
        current_path[current_path_index] = '?';
      }
    }
  }

  return "not possible";
}

int main() {
  // cout << CorrectPath_v2(move(string{gets(stdin)}));
  cout << CorrectPath_v2(move(string{"r?d?drdd"}))
       << '\n';  // expected output: "rrdrdrdd"
  cout << CorrectPath_v2(move(string{"???rrurdr?"}))
       << '\n';  // expected output: "dddrrurdrd"
  cout << CorrectPath_v2(move(string{"drdr??rrddd?"}))
       << '\n';  // expected output: "drdruurrdddd"
  cout << CorrectPath_v2(move(string{"rd?u??dld?ddrr"}))
       << '\n';  // expected output: "rdrurrdldlddrr"
  cout << CorrectPath_v2(move(string{"ddr?rdrrd?dr"}))
       << '\n';  // expected output: "ddrurdrrdldr"
  cout << CorrectPath_v2(move(string{"rdrdr??rddd?dr"}))
       << '\n';  // expected output: "rdrdruurdddldr"

  return 0;
}
