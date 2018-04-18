/*
Coderbyte coding challenge: Connect Four Winner

Using the C++ language, have the function ConnectFourWinner(strArr) read the
strArr parameter being passed which will represent a 6x7 Connect Four board. The
rules of the game are: two players alternate turns and place a colored disc down
into the grid from the top and the disc falls down the column until it hits the
bottom or until it hits a piece beneath it. The object of the game is to connect
four of one's own discs of the same color next to each other vertically,
horizontally, or diagonally before your opponent. The input strArr will
represent a Connect Four board and it will be structured in the following
format: ["R/Y","(R,Y,x,x,x,x,x)","(...)","(...)",...)] where R represents the
player using red discs, Y represents the player using yellow discs and x
represents an empty space on the board. The first element of strArr will be
either R or Y and it represents whose turn it is. Your program should determine,
based on whose turn it is, whether a space exists that can give that player a
win. If a space does exist your program should return the space in the following
format: (RxC) where R=row and C=column. If no space exists, return the string
none. The board will always be in a legal setup.

For example, if strArr is:
["R","(x,x,x,x,x,x,x)","(x,x,x,x,x,x,x)","(x,x,x,x,x,x,x)","(x,x,x,R,x,x,x)","(x,x,x,R,x,x,x)","(x,x,x,R,Y,Y,Y)"]
then your program should return (3x4).

Another example, if strArr is:
["Y","(x,x,x,x,x,x,x)","(x,x,x,x,x,x,x)","(x,x,x,x,x,x,x)","(x,x,Y,Y,x,x,x)","(x,R,R,Y,Y,x,R)","(x,Y,R,R,R,Y,R)"]
then your program should return (3x3).
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
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

enum class cf { red_disc, yellow_disc, empty_slot };

// winning sequence of discs (R or Y) stretching across a horizontal, vertical
// or one of the 2 valid diagonal directions
bool is_there_a_winning_sequence_of_discs_at_specified_position(
    const vector<vector<cf>>& game_board,
    const pair<int, int>& position) {
  const cf player_disc{game_board[position.first][position.second]};

  // 1. check vertical direction for >= 4 player discs of same disc color
  // (cf::red_disc or cf::yellow_disc)

  size_t count{1};

  int xu{position.first - 1};

  while (xu >= 0 && player_disc == game_board[xu][position.second]) {
    count++;
    xu--;
  }

  if (count >= 4)
    return true;

  int xd{position.first + 1};

  while (xd <= 5 && player_disc == game_board[xd][position.second]) {
    count++;
    xd++;
  }

  if (count >= 4)
    return true;

  count = 1;

  int yl{position.second - 1};

  while (yl >= 0 && player_disc == game_board[position.first][yl]) {
    count++;
    yl--;
  }

  if (count >= 4)
    return true;

  int yr{position.second + 1};

  while (yr <= 6 && player_disc == game_board[position.first][yr]) {
    count++;
    yr++;
  }

  if (count >= 4)
    return true;

  // 3. check first diagonal direction (k=1) for >= 4 player discs of same
  // disc color (cf::red_disc or cf::yellow_disc)

  count = 1;

  for (int x{position.first - 1}, y{position.second - 1}; x >= 0 && y >= 0;
       x--, y--) {
    if (player_disc != game_board[x][y])
      break;
    count++;
  }

  if (count >= 4)
    return true;

  for (int x{position.first + 1}, y{position.second + 1}; x <= 5 && y <= 6;
       x++, y++) {
    if (player_disc != game_board[x][y])
      break;
    count++;
  }

  if (count >= 4)
    return true;

  // 4. check second diagonal direction (k=-1) for >= 4 player discs of same
  // disc color (cf::red_disc or cf::yellow_disc)

  count = 1;

  for (int x{position.first + 1}, y{position.second - 1}; x <= 5 && y >= 0;
       x++, y--) {
    if (player_disc != game_board[x][y])
      break;
    count++;
  }

  if (count >= 4)
    return true;

  for (int x{position.first - 1}, y{position.second + 1}; x >= 0 && y <= 6;
       x--, y++) {
    if (player_disc != game_board[x][y])
      break;
    count++;
  }

  if (count >= 4)
    return true;

  return false;
}

vector<pair<int, cf>> get_top_level_game_items(
    const vector<vector<cf>>& game_board) {
  vector<pair<int, cf>> top_level_game_items(7,
                                             pair<int, cf>{5, cf::empty_slot});

  for (int y{}; y < 7; y++) {
    for (int x{}; x < 6; x++) {
      if (cf::empty_slot != game_board[x][y]) {
        top_level_game_items[y] = make_pair(x, game_board[x][y]);
        break;
      }
    }
  }

  return top_level_game_items;
}

string play_the_game(vector<vector<cf>>& game_board, const cf& player) {
  const vector<pair<int, cf>> top_level_game_items{
      get_top_level_game_items(game_board)};

  for (size_t y{}; y < 7; y++) {
    // if there's a non-empty cf game item present in the top-most row of column
    // 'y' then skip to next column (continue)
    // 0 -> top-most row index, 5 -> bottom-most row index
    if (0 == top_level_game_items[y].first &&
        cf::empty_slot != top_level_game_items[y].second)
      continue;

    const int x_pos_for_player_disc{cf::empty_slot !=
                                            top_level_game_items[y].second
                                        ? top_level_game_items[y].first - 1
                                        : top_level_game_items[y].first};

    const cf prev_game_item{game_board[x_pos_for_player_disc][y]};

    game_board[x_pos_for_player_disc][y] = player;

    if (is_there_a_winning_sequence_of_discs_at_specified_position(
            game_board, make_pair(x_pos_for_player_disc, y))) {
      ostringstream oss{};
      oss << '(' << x_pos_for_player_disc + 1 << 'x' << y + 1 << ')';
      return oss.str();
    }

    game_board[x_pos_for_player_disc][y] = prev_game_item;
  }

  return "none";
}

vector<vector<cf>> construct_connect_four_game_board(
    string* str_arr,
    const size_t str_arr_size) {
  vector<vector<cf>> game_board(
      6, vector<cf>(7, cf::empty_slot));  // gameboard's dimensions: 6 x 7

  for (size_t i{1}; i < str_arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);
    str_arr[i].erase(begin(str_arr[i]));
    str_arr[i].erase(--end(str_arr[i]));
    const vector<string> row_elements{split(str_arr[i], ",", 7)};
    if (7 != row_elements.size()) {
      ostringstream oss{};
      oss << "str_arr[" << i << "] string only contains " << row_elements.size()
          << " comma-separated substring elements,\n"
          << "whereas it should contain at least 7 substring elements!";
      throw invalid_argument{oss.str()};
    }
    for (size_t j{}; j < 7; j++) {
      if ("x" == row_elements[j] || "X" == row_elements[j])
        continue;

      game_board[i - 1][j] = "R" == row_elements[j] || "r" == row_elements[j]
                                 ? cf::red_disc
                                 : cf::yellow_disc;
    }
  }

  return game_board;
}

string ConnectFourWinner(string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 7)
    return "not possible";

  const cf player{"R" == *str_arr || "r" == *str_arr ? cf::red_disc
                                                     : cf::yellow_disc};

  vector<vector<cf>> game_board{
      construct_connect_four_game_board(str_arr, str_arr_size)};

  return play_the_game(game_board, player);
}

int main() {
  // string A[] = gets(stdin);
  // cout << ConnectFourWinner(A, sizeof(A)/sizeof(*A));

  string B[] = {"R",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,R,x,x,x)",
                "(x,x,x,R,x,x,x)",
                "(x,x,x,R,Y,Y,Y)"};
  cout << ConnectFourWinner(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "(3x4)"
  string C[] = {"Y",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,Y,Y,x,x,x)",
                "(x,R,R,Y,Y,x,R)",
                "(x,Y,R,R,R,Y,R)"};
  cout << ConnectFourWinner(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "(3x3)"
  string D[] = {"R",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,R,x,x,x)",
                "(x,x,x,R,x,x,x)",
                "(x,x,x,R,Y,Y,Y)"};
  cout << ConnectFourWinner(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "(3x4)"
  string E[] = {"Y",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,Y,Y,x,x,x)",
                "(x,R,R,Y,Y,x,R)",
                "(x,Y,R,R,R,Y,R)"};
  cout << ConnectFourWinner(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "(3x3)"
  string F[] = {"Y",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(Y,Y,Y,x,R,R,R)"};
  cout << ConnectFourWinner(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "(6x4)"
  string G[] = {"R",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(Y,Y,Y,x,R,R,R)"};
  cout << ConnectFourWinner(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: "(6x4)"
  string H[] = {"R",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(Y,x,x,x,x,x,R)",
                "(Y,x,x,x,x,x,R)",
                "(Y,x,x,x,x,x,R)"};
  cout << ConnectFourWinner(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: "(3x7)"
  string I[] = {"Y",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,R,Y,x,Y)",
                "(x,x,x,R,R,Y,R)",
                "(x,x,x,Y,R,R,Y)"};
  cout << ConnectFourWinner(I, sizeof(I) / sizeof(*I))
       << '\n';  // expected output: "(3x4)"
  string J[] = {"R",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(x,x,x,x,x,x,x)",
                "(R,x,Y,x,x,x,x)",
                "(R,Y,R,Y,R,Y,Y)",
                "(R,Y,R,Y,R,Y,R)"};
  cout << ConnectFourWinner(J, sizeof(J) / sizeof(*J))
       << '\n';  // expected output: "(3x1)"

  return 0;
}
