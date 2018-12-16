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
#include <iostream>
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

size_t distance(const size_t x_src,
                const size_t y_src,
                const size_t x_dst = 4,
                const size_t y_dst = 4) {
  return ((x_src <= x_dst ? x_dst - x_src : x_src - x_dst) +
          (y_src <= y_dst ? y_dst - y_src : y_src - y_dst));
}

bool find_correct_path(vector<vector<int>>& maze,
                       const size_t x,
                       const size_t y,
                       string& path,
                       const size_t current_path_index) {
  if (x == 4 && y == 4 && current_path_index == path.length())
    return true;

  if (distance(x, y, 4, 4) > path.length() - current_path_index)
    return false;

  maze[x][y] = -1;

  if ('u' == path[current_path_index]) {
    if (x > 0 && -1 != maze[x - 1][y] &&
        find_correct_path(maze, x - 1, y, path, current_path_index + 1))
      return true;
    if (x && y)
      maze[x][y] = 0;
    return false;
  }

  else if ('d' == path[current_path_index]) {
    if (x < 4 && -1 != maze[x + 1][y] &&
        find_correct_path(maze, x + 1, y, path, current_path_index + 1))
      return true;
    if (x && y)
      maze[x][y] = 0;
    return false;
  }

  else if ('l' == path[current_path_index]) {
    if (y > 0 && -1 != maze[x][y - 1] &&
        find_correct_path(maze, x, y - 1, path, current_path_index + 1))
      return true;
    if (x && y)
      maze[x][y] = 0;
    return false;
  }

  else if ('r' == path[current_path_index]) {
    if (y < 4 && -1 != maze[x][y + 1] &&
        find_correct_path(maze, x, y + 1, path, current_path_index + 1))
      return true;
    if (x && y)
      maze[x][y] = 0;
    return false;
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

  if (x && y)
    maze[x][y] = 0;

  return false;
}

string CorrectPath_v1(string str) {
  str = trim(str);

  vector<vector<int>> maze(5, vector<int>(5));

  if (find_correct_path(maze, 0, 0, str, 0))
    return str;

  return "not possible";
}

int main() {
  // cout << CorrectPath_v1(move(string{gets(stdin)}));
  cout << CorrectPath_v1(move(string{"r?d?drdd"}))
       << '\n';  // expected output: "rrdrdrdd"
  cout << CorrectPath_v1(move(string{"???rrurdr?"}))
       << '\n';  // expected output: "dddrrurdrd"
  cout << CorrectPath_v1(move(string{"drdr??rrddd?"}))
       << '\n';  // expected output: "drdruurrdddd"
  cout << CorrectPath_v1(move(string{"rd?u??dld?ddrr"}))
       << '\n';  // expected output: "rdrurrdldlddrr"
  cout << CorrectPath_v1(move(string{"ddr?rdrrd?dr"}))
       << '\n';  // expected output: "ddrurdrrdldr"
  cout << CorrectPath_v1(move(string{"rdrdr??rddd?dr"}))
       << '\n';  // expected output: "rdrdruurdddldr"

  return 0;
}
