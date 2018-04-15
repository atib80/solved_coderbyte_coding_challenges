/*
Coderbyte coding challenge: Quick Knight

Using the C++ language, have the function QuickKnight(str) read str which will
be a string consisting of the location of a knight on a standard 8x8 chess board
with no other pieces on the board and another space on the chess board. The
structure of str will be the following: "(x y)(a b)" where (x y) represents the
position of the knight with x and y ranging from 1 to 8 and (a b) represents
some other space on the chess board with a and b also ranging from 1 to 8. Your
program should determine the least amount of moves it would take the knight to
go from its position to position (a b). For example if str is "(2 3)(7 5)" then
your program should output 3 because that is the least amount of moves it would
take for the knight to get from (2 3) to (7 5) on the chess board.

Sample test cases:

Input:  "(1 1)(8 8)"
Output: 6

Input:  "(2 2)(3 3)"
Output: 2
 */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <utility>
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

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.length()};

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

    if (string::npos != max_count && parts.size() == max_count)
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

pair<int, int> parse_coordinate_pair_values(const string& str) {
  pair<int, int> coord{};
  size_t si{str.find_first_of("1234567890")};
  if (string::npos == si)
    return coord;
  size_t ei{str.find_first_not_of("1234567890", si + 1)};
  if (string::npos == ei)
    return coord;
  coord.first = stoi(str.substr(si, ei - si));

  si = str.find_first_of("1234567890", ei + 1);
  if (string::npos == si)
    return coord;
  ei = str.find_first_not_of("1234567890", si + 1);
  if (string::npos == ei)
    coord.second = stoi(str.substr(si));
  else
    coord.second = stoi(str.substr(si, ei - si));

  return coord;
}

vector<pair<int, int>> find_next_positions(const pair<int, int>& position) {
  vector<pair<int, int>> next_positions{};

  if (position.first - 2 >= 1) {
    if (position.second - 1 >= 1)
      next_positions.emplace_back(
          make_pair(position.first - 2, position.second - 1));
    if (position.second + 1 <= 8)
      next_positions.emplace_back(
          make_pair(position.first - 2, position.second + 1));
  }

  if (position.first + 2 <= 8) {
    if (position.second - 1 >= 1)
      next_positions.emplace_back(
          make_pair(position.first + 2, position.second - 1));
    if (position.second + 1 <= 8)
      next_positions.emplace_back(
          make_pair(position.first + 2, position.second + 1));
  }

  if (position.first - 1 >= 1) {
    if (position.second - 2 >= 1)
      next_positions.emplace_back(
          make_pair(position.first - 1, position.second - 2));
    if (position.second + 2 <= 8)
      next_positions.emplace_back(
          make_pair(position.first - 1, position.second + 2));
  }

  if (position.first + 1 <= 8) {
    if (position.second - 2 >= 1)
      next_positions.emplace_back(
          make_pair(position.first + 1, position.second - 2));
    if (position.second + 2 <= 8)
      next_positions.emplace_back(
          make_pair(position.first + 1, position.second + 2));
  }

  return next_positions;
}

void find_minimum_number_of_jumps(vector<vector<int>>& chessboard,
                                  const pair<int, int>& position,
                                  size_t& min_number_of_jumps,
                                  const size_t current_number_of_jumps = 0) {
  if (current_number_of_jumps + 1 >= min_number_of_jumps)
    return;

  const vector<pair<int, int>> next_positions{find_next_positions(position)};

  for (const pair<int, int>& next_pos : next_positions) {
    const int x{next_pos.first - 1};
    const int y{next_pos.second - 1};

    if (-1 == chessboard[x][y])
      continue;

    if (1 == chessboard[x][y]) {
      min_number_of_jumps = current_number_of_jumps + 1;
      return;
    }

    chessboard[x][y] = -1;

    find_minimum_number_of_jumps(chessboard, next_pos, min_number_of_jumps,
                                 current_number_of_jumps + 1);

    chessboard[x][y] = 0;
  }
}

string QuickKnight(string str) {
  str = trim(str);
  str.erase(begin(str));
  str.erase(--end(str));
  const vector<string> coord_pairs{split(str, ")(", 2)};
  const pair<int, int> knight_pos{parse_coordinate_pair_values(coord_pairs[0])};
  const pair<int, int> target_pos{parse_coordinate_pair_values(coord_pairs[1])};

  vector<vector<int>> chessboard(8, vector<int>(8));
  chessboard[knight_pos.first - 1][knight_pos.second - 1] = -1;
  chessboard[target_pos.first - 1][target_pos.second - 1] = 1;
  size_t min_number_of_jumps{string::npos};
  find_minimum_number_of_jumps(chessboard, knight_pos, min_number_of_jumps, 0);

  if (string::npos == min_number_of_jumps)
    return "not possible";

  return to_string(min_number_of_jumps);
}

int main() {
  // cout << QuickKnight(string{gets(stdin)});
  cout << QuickKnight(string{"(2 3)(7 5)"}) << '\n';  // expected output: "3"
  cout << QuickKnight(string{"(1 1)(8 8)"}) << '\n';  // expected output: "6"
  cout << QuickKnight(string{"(2 2)(3 3)"}) << '\n';  // expected output: "2"

  return 0;
}
