/*
Coderbyte coding challenge: Correct Path v1
(recursive solution)

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
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

std::string trim(const std::string& src,
                 const char* chars_to_trim = " \t\n\f\v\r") {
  if (src.empty())
    return {};

  const std::unordered_set<char> trimmed_chars(
      chars_to_trim, chars_to_trim + strlen(chars_to_trim));

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

size_t distance(const size_t x_src,
                const size_t y_src,
                const size_t x_dst,
                const size_t y_dst) {
  return (x_src < x_dst ? x_dst - x_src : x_src - x_dst) +
         (y_src < y_dst ? y_dst - y_src : y_src - y_dst);
}

bool find_correct_path(vector<vector<int>>& maze,
                       const size_t x,
                       const size_t y,
                       string& path,
                       const size_t current_path_index = 0) {
  if (x == 4U && y == 4U && current_path_index == path.length())
    return true;

  if (distance(x, y, 4U, 4U) > path.length() - current_path_index)
    return false;

  maze[x][y] = -1;

  if ('u' == path[current_path_index]) {
    if (x > 0U && -1 != maze[x - 1][y] &&
        find_correct_path(maze, x - 1, y, path, current_path_index + 1))
      return true;
  }

  else if ('d' == path[current_path_index]) {
    if (x < 4U && -1 != maze[x + 1][y] &&
        find_correct_path(maze, x + 1, y, path, current_path_index + 1))
      return true;
  }

  else if ('l' == path[current_path_index]) {
    if (y > 0U && -1 != maze[x][y - 1] &&
        find_correct_path(maze, x, y - 1, path, current_path_index + 1))
      return true;
  }

  else if ('r' == path[current_path_index]) {
    if (y < 4U && -1 != maze[x][y + 1] &&
        find_correct_path(maze, x, y + 1, path, current_path_index + 1))
      return true;
  }

  else if ('?' == path[current_path_index]) {
    if (x > 0 && -1 != maze[x - 1][y]) {
      path[current_path_index] = 'u';
      if (find_correct_path(maze, x - 1, y, path, current_path_index + 1))
        return true;
      path[current_path_index] = '?';
    }

    if (x < 4 && -1 != maze[x + 1][y]) {
      path[current_path_index] = 'd';
      if (find_correct_path(maze, x + 1, y, path, current_path_index + 1))
        return true;
      path[current_path_index] = '?';
    }

    if (y > 0 && -1 != maze[x][y - 1]) {
      path[current_path_index] = 'l';
      if (find_correct_path(maze, x, y - 1, path, current_path_index + 1))
        return true;
      path[current_path_index] = '?';
    }

    if (y < 4 && -1 != maze[x][y + 1]) {
      path[current_path_index] = 'r';
      if (find_correct_path(maze, x, y + 1, path, current_path_index + 1))
        return true;
      path[current_path_index] = '?';
    }
  }

  if (x != 0U && y != 0U)
    maze[x][y] = 0;

  return false;
}

string CorrectPath_v1(string str) {
  str = trim(str);

  for (char& ch : str)
    ch = static_cast<char>(tolower(ch));

  vector<vector<int>> maze(5, vector<int>(5));

  if (find_correct_path(maze, 0, 0, str, 0))
    return str;

  return "not possible";
}

int main() {
  // cout << CorrectPath_v1(gets(stdin));
  cout << CorrectPath_v1("r?d?drdd") << '\n';  // expected output: "rrdrdrdd"
  cout << CorrectPath_v1("???rrurdr?")
       << '\n';  // expected output: "dddrrurdrd"
  cout << CorrectPath_v1("drdr??rrddd?")
       << '\n';  // expected output: "drdruurrdddd"
  cout << CorrectPath_v1("rd?u??dld?ddrr")
       << '\n';  // expected output: "rdrurrdldlddrr"
  cout << CorrectPath_v1("ddr?rdrrd?dr")
       << '\n';  // expected output: "ddrurdrrdldr"
  cout << CorrectPath_v1("rdrdr??rddd?dr")
       << '\n';  // expected output: "rdrdruurdddldr"

  return 0;
}
