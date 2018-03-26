/*
Coderbyte coding challenge: Eight Queens

Using the C++ language, have the function EightQueens(strArr) read strArr which
will be an array consisting of the locations of eight Queens on a standard 8x8
chess board with no other pieces on the board. The structure of strArr will be
the following: ["(x,y)", "(x,y)", ...] where (x,y) represents the position of
the current queen on the chessboard (x and y will both range from 1 to 8 where
1,1 is the bottom-left of the chessboard and 8,8 is the top-right). Your program
should determine if all of the queens are placed in such a way where none of
them are attacking each other. If this is true for the given input, return the
string true otherwise return the first queen in the list that is attacking
another piece in the same format it was provided.

For example: if strArr is ["(2,1)", "(4,2)", "(6,3)", "(8,4)", "(3,5)", "(1,6)",
"(7,7)", "(5,8)"] then your program should return the string true. The
corresponding chessboard of queens for this input is below (taken from
Wikipedia). _ _ _ _ _ _ _ _
|_|_|_|Q|_|_|_|_|
|_|_|_|_|_|_|Q|_|
|_|_|Q|_|_|_|_|_|
|_|_|_|_|_|_|_|Q|
|_|Q|_|_|_|_|_|_|
|_|_|_|_|Q|_|_|_|
|Q|_|_|_|_|_|_|_|
|_|_|_|_|_|Q|_|_|

Sample test cases:

Input:  "(2,1)", "(4,3)", "(6,3)", "(8,4)", "(3,4)", "(1,6)", "(7,7)", "(5,8)"
Output: "(2,1)"

Input:  "(2,1)", "(5,3)", "(6,3)", "(8,4)", "(3,4)", "(1,8)", "(7,7)", "(5,8)"
Output: "(5,3)"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string format_queen_coordinates(const pair<size_t, size_t>& queen_position) {
  ostringstream oss{};
  oss << '(' << queen_position.first << ',' << queen_position.second << ')';
  return oss.str();
}

inline size_t distance(const size_t x, const size_t y) {
  return (x < y ? y - x : x - y);
}

pair<size_t, size_t> parse_position_coordinates(const string& position) {
  size_t start{position.find_first_of("0123456789")};
  size_t last{position.find_first_not_of("0123456789", start + 1)};

  const size_t x{stoul(position.substr(start, last - start))};

  start = position.find_first_of("0123456789", last + 1);
  last = position.find_first_not_of("0123456789", start + 1);
  if (string::npos == last)
    last = position.length();

  const size_t y{stoul(position.substr(start, last - start))};

  return make_pair(x, y);
}

string EightQueens(const string* str_arr, const size_t str_arr_size) {
  vector<pair<size_t, size_t>> queens_positions{};

  for (size_t i{}; i < str_arr_size; i++) {
    queens_positions.emplace_back(parse_position_coordinates(str_arr[i]));
  }

  for (size_t i{}; i < queens_positions.size(); i++) {
    for (size_t j{}; j < queens_positions.size(); j++) {
      if (j == i)
        continue;

      if (queens_positions[i].first == queens_positions[j].first ||
          queens_positions[i].second == queens_positions[j].second)
        return format_queen_coordinates(queens_positions[i]);

      if (distance(queens_positions[i].first, queens_positions[j].first) ==
          distance(queens_positions[i].second, queens_positions[j].second))
        return format_queen_coordinates(queens_positions[i]);
    }
  }

  return "true";
}

int main() {
  // string queen_positions[] = gets(stdin);
  // cout << EightQueens(queen_positions,
  // sizeof(queen_positions)/sizeof(*queen_positions));
  string queen_positions1[] = {"(2,1)", "(4,2)", "(6,3)", "(8,4)",
                               "(3,5)", "(1,6)", "(7,7)", "(5,8)"};
  cout << EightQueens(queen_positions1,
                      sizeof(queen_positions1) / sizeof(*queen_positions1))
       << '\n';  // expected output: "true"
  string queen_positions2[] = {"(2,1)", "(4,3)", "(6,3)", "(8,4)",
                               "(3,4)", "(1,6)", "(7,7)", "(5,8)"};
  cout << EightQueens(queen_positions2,
                      sizeof(queen_positions2) / sizeof(*queen_positions2))
       << '\n';  // expected output: "(2,1)"
  string queen_positions3[] = {"(2,1)", "(5,3)", "(6,3)", "(8,4)",
                               "(3,4)", "(1,8)", "(7,7)", "(5,8)"};
  cout << EightQueens(queen_positions3,
                      sizeof(queen_positions3) / sizeof(*queen_positions3))
       << '\n';  // expected output: "(5,3)"

  return 0;
}
