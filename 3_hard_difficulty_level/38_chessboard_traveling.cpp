/*
Coderbyte coding challenge: Chessboard Traveling

Using the C++ language, have the function ChessboardTraveling(str) read str
which will be a string consisting of the location of a space on a standard 8x8
chess board with no pieces on the board along with another space on the chess
board. The structure of str will be the following: "(x y)(a b)" where (x y)
represents the position you are currently on with x and y ranging from 1 to 8
and (a b) represents some other space on the chess board with a and b also
ranging from 1 to 8 where a > x and b > y. Your program should determine how
many ways there are of traveling from (x y) on the board to (a b) moving only up
and to the right. For example: if str is (1 1)(2 2) then your program should
output 2 because there are only two possible ways to travel from space (1 1) on
a chessboard to space (2 2) while making only moves up and to the right.

Sample test cases:

Input:  "(1 1)(3 3)"
Output: 6

Input:  "(2 2)(4 3)"
Output: 3
*/

#include <algorithm>
#include <cstdint>
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

uint64_t factorial(const uint64_t number) {
  if (number < 2LL)
    return 1ULL;

  uint64_t result{number};

  for (uint64_t i{result - 1}; i > 1LL; i--)
    result *= i;

  return result;
}

vector<pair<size_t, size_t>> parse_coordinate_pairs(const string& str) {
  vector<pair<size_t, size_t>> coordinate_pairs{};

  size_t start{str.find_first_of("0123456789")};

  if (string::npos == start)
    return coordinate_pairs;

  size_t end{str.find_first_not_of("0123456789", start + 1)};

  if (string::npos == end)
    return coordinate_pairs;

  const size_t x1{stoul(str.substr(start, end - start))};

  start = str.find_first_of("0123456789", end + 1);

  if (string::npos == start)
    return coordinate_pairs;

  end = str.find_first_not_of("0123456789", start + 1);

  if (string::npos == end)
    return coordinate_pairs;

  const size_t y1{stoul(str.substr(start, end - start))};

  start = str.find_first_of("0123456789", end + 1);

  if (string::npos == start)
    return coordinate_pairs;

  end = str.find_first_not_of("0123456789", start + 1);

  if (string::npos == end)
    return coordinate_pairs;

  const size_t x2{stoul(str.substr(start, end - start))};

  start = str.find_first_of("0123456789", end + 1);

  if (string::npos == start)
    return coordinate_pairs;

  end = str.find_first_not_of("0123456789", start + 1);

  if (string::npos == end)
    return coordinate_pairs;

  const size_t y2{stoul(str.substr(start, end - start))};

  coordinate_pairs.emplace_back(make_pair(x1, y1));
  coordinate_pairs.emplace_back(make_pair(x2, y2));

  return coordinate_pairs;
}

string ChessboardTraveling(string str) {
  str = trim(str);

  const vector<pair<size_t, size_t>> coordinates{parse_coordinate_pairs(str)};

  if (coordinates.empty())
    return "0";

  const size_t x1{coordinates[0].first};
  const size_t y1{coordinates[0].second};
  const size_t x2{coordinates[1].first};
  const size_t y2{coordinates[1].second};

  const size_t number_of_moves_needed{x2 - x1 + y2 - y1};

  const size_t number_of_max_moves_right{x2 - x1};

  const size_t number_of_max_moves_up{y2 - y1};

  const uint64_t number_of_move_combinations{
      factorial(number_of_moves_needed) /
      (factorial(number_of_max_moves_up) *
       factorial(number_of_max_moves_right))};

  return to_string(number_of_move_combinations);
}

int main() {
  // cout << ChessboardTraveling(string{gets(stdin)});
  cout << ChessboardTraveling(string{"(1 1)(2 2)"})
       << '\n';  // expected output: "2"
  cout << ChessboardTraveling(string{"(1 1)(3 3)"})
       << '\n';  // expected output: "6"
  cout << ChessboardTraveling(string{"(2 2)(4 3)"})
       << '\n';  // expected output: "3"

  return 0;
}
