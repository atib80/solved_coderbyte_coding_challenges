/*
Coderbyte coding challenge: Knight Jumps

Using the C++ language, have the function KnightJumps(str) read str which will
be a string consisting of the location of a knight on a standard 8x8 chess board
with no other pieces on the board. The structure of str will be the following:
"(x y)" which represents the position of the knight with x and y ranging from 1
to 8. Your program should determine the number of spaces the knight can move to
from a given location. For example: if str is "(4 5)" then your program should
output 8 because the knight can move to 8 different spaces from position x=4 and
y=5.

Sample test cases:

Input:  "(1 1)"
Output: 2

Input:  "(2 8)"
Output: 3
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <utility>

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

pair<int, int> parse_coordinate_pair_values(string str) {
  str.erase(begin(str));
  str.erase(--end(str));
  return make_pair(stoi(str.substr(0, 1)), stoi(str.substr(2, 1)));
}

string KnightJumps(string str) {
  str = trim(str);

  const pair<int, int> coord{parse_coordinate_pair_values(move(str))};

  if ((1 == coord.first && 1 == coord.second) ||
      (1 == coord.first && 8 == coord.second) ||
      (8 == coord.first && 1 == coord.second) ||
      (8 == coord.first && 8 == coord.second))
    return "2";

  if (coord.first >= 3 && coord.first <= 6 && coord.second >= 3 &&
      coord.second <= 6)
    return "8";

  size_t moves_count{};

  if (coord.first >= 3) {
    if (coord.second <= 7)
      moves_count++;
    if (coord.second >= 2)
      moves_count++;
  }

  if (coord.first <= 6) {
    if (coord.second <= 7)
      moves_count++;
    if (coord.second >= 2)
      moves_count++;
  }

  if (coord.first <= 7) {
    if (coord.second <= 6)
      moves_count++;
    if (coord.second >= 3)
      moves_count++;
  }

  if (coord.first >= 2) {
    if (coord.second <= 6)
      moves_count++;
    if (coord.second >= 3)
      moves_count++;
  }

  return to_string(moves_count);
}

int main() {
  // cout << KnightJumps(string{gets(stdin)});
  cout << KnightJumps(string{"(4 5)"}) << '\n';  // expected output: "8"
  cout << KnightJumps(string{"(1 1)"}) << '\n';  // expected output: "2"
  cout << KnightJumps(string{"(2 8)"}) << '\n';  // expected output: "3"

  return 0;
}
