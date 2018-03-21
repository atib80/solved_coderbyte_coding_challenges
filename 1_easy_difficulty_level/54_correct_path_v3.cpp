/*
Coderbyte coding challenge: Correct Path v3
(brute-force solution using permutation)

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
#include <array>
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

string CorrectPath(string path) {
  string unsolved_path{trim(path)};
  for (auto& ch : unsolved_path)
    ch = static_cast<char>(tolower(ch));

  size_t number_of_question_marks{};
  vector<size_t> question_mark_indices{};

  for (size_t i{}; i < unsolved_path.size(); i++) {
    if ('?' == unsolved_path[i]) {
      number_of_question_marks++;
      question_mark_indices.emplace_back(i);
    }
  }

  string potential_directions{string(number_of_question_marks, 'r') +
                              string(number_of_question_marks, 'd') +
                              string(number_of_question_marks, 'u') +
                              string(number_of_question_marks, 'l')};

  sort(begin(potential_directions), end(potential_directions));

  const size_t path_len{unsolved_path.length()};

  do {
    for (size_t i{}; i < number_of_question_marks; i++) {
      unsolved_path[question_mark_indices[i]] = potential_directions[i];
    }

    array<array<bool, 5>, 5> maze{{}};

    maze[0][0] = true;

    bool is_wrong_path{};

    size_t xi{}, yi{};

    for (size_t i{}; i < path_len; i++) {
      switch (unsolved_path[i]) {
        case 'l':
          if (0 == yi || maze[xi][yi - 1])
            is_wrong_path = true;
          else
            yi--;

          break;

        case 'r':
          if (4 == yi || maze[xi][yi + 1])
            is_wrong_path = true;
          else
            yi++;

          break;

        case 'u':
          if (0 == xi || maze[xi - 1][yi])
            is_wrong_path = true;
          else
            xi--;

          break;

        case 'd':
          if (4 == xi || maze[xi + 1][yi])
            is_wrong_path = true;
          else
            xi++;

          break;

      }

      if (is_wrong_path)
        break;

      if (distance(xi, yi, 4, 4) > path_len - i) {
        is_wrong_path = true;
        break;
      }

      maze[xi][yi] = true;
    }

    if (!is_wrong_path && 4 == xi && 4 == yi)
      return unsolved_path;

  } while (
      next_permutation(begin(potential_directions), end(potential_directions)));

  return "not possible";
}

int main() {
  // cout << CorrectPath(gets(stdin));
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
