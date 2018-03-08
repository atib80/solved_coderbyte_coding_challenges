/*
Coderbyte coding challenge: Correct Path v1

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

#include <cctype>
#include <iostream>
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

bool find_correct_path(vector<vector<int>>& maze,
                       const size_t x,
                       const size_t y,
                       string& path,
                       const size_t current_path_index) {
  
  if ((x == maze.size() - 1) && (y == maze[x].size() - 1) &&
      (current_path_index == path.length()))
    return true;

  if (current_path_index == path.length())
    return false;

  maze[x][y] = -1;

  if (('u' == path[current_path_index]) && (x > 0) && (-1 != maze[x - 1][y]) &&
      find_correct_path(maze, x - 1, y, path, current_path_index + 1))
    return true;

  if (('d' == path[current_path_index]) && (x < maze.size() - 1) &&
      (-1 != maze[x + 1][y]) &&
      find_correct_path(maze, x + 1, y, path, current_path_index + 1))
    return true;

  if (('l' == path[current_path_index]) && (y > 0) && (-1 != maze[x][y - 1]) &&
      find_correct_path(maze, x, y - 1, path, current_path_index + 1))
    return true;

  if (('r' == path[current_path_index]) && (y < maze[x].size() - 1) &&
      (-1 != maze[x][y + 1]) &&
      find_correct_path(maze, x, y + 1, path, current_path_index + 1))
    return true;

  if ('?' == path[current_path_index]) {
    if ((x > 0) && (-1 != maze[x - 1][y])) {
      path[current_path_index] = 'u';

      if (find_correct_path(maze, x - 1, y, path, current_path_index + 1))
        return true;

      path[current_path_index] = '?';
    }

    if ((x < maze.size() - 1) && (-1 != maze[x + 1][y])) {
      path[current_path_index] = 'd';

      if (find_correct_path(maze, x + 1, y, path, current_path_index + 1))
        return true;

      path[current_path_index] = '?';
    }

    if ((y > 0) && (-1 != maze[x][y - 1])) {
      path[current_path_index] = 'l';

      if (find_correct_path(maze, x, y - 1, path, current_path_index + 1))
        return true;

      path[current_path_index] = '?';
    }

    if ((y < maze[x].size() - 1) && (-1 != maze[x][y + 1])) {
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

string CorrectPath(string str) {
  str = trim(str);

  vector<vector<int>> maze(5, vector<int>(5));

  if (find_correct_path(maze, 0, 0, str, 0))
    return str;

  return "not possible";
}

int main() {
  // cout << CorrectPath(move(string{gets(stdin)}));
  cout << CorrectPath(move(string{"r?d?drdd"}))
       << '\n';  // expected output: "rrdrdrdd"
  cout << CorrectPath(move(string{"???rrurdr?"}))
       << '\n';  // expected output: "dddrrurdrd"
  cout << CorrectPath(move(string{"drdr??rrddd?"}))
       << '\n';  // expected output: "drdruurrdddd"
  cout << CorrectPath(move(string{"rd?u??dld?ddrr"}))
       << '\n';  // expected output: "rdrurrdldlddrr"
  cout << CorrectPath(move(string{"ddr?rdrrd?dr"}))
       << '\n';  // expected output: "ddrurdrrdldr"
  cout << CorrectPath(move(string{"rdrdr??rddd?dr"}))
       << '\n';  // expected output: "rdrdruurdddldr"

  return 0;
}
