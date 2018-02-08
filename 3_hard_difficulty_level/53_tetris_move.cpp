/*
Coderbyte coding challenge: Tetris Move

Using the C++ language, have the function TetrisMove(strArr) take strArr
parameter being passed which will be an array containing one letter followed by
12 numbers representing a Tetris piece followed by the fill levels for the 12
columns of the board. Calculate the greatest number of horizontal lines that can
be completed when the piece arrives at the bottom assuming it is dropped
immediately after being rotated and moved horizontally from the top.
Tricky combinations of vertical and horizontal movements are excluded. The piece
types are represented by capital letters.

For example, with an input of
["L","3","4","4","5","6","2","0","6","5","3","6","6"], the board will look
something like this:

|            |
|            |
|            |
|    #  #  ##|
|   ##  ## ##|
| ####  ## ##|
|#####  #####|
|###### #####|
|###### #####|

Your result should be 3 because the L piece can be rotated and dropped in column
6-7 which will complete 3 full rows of blocks.

Sample test cases:

Input:  "I", "2", "4", "3", "4", "5", "2", "0", "2", "2", "3", "3", "3"
Output: 2

Input:  "O", "4", "3", "2", "3", "5", "1", "0", "1", "2", "4", "3", "4"
Output: 0
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
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

enum class tetris { empty, brick, game_piece };

enum class tetris_game_item { I, J, L, O, S, T, Z };

enum class tetris_game_item_angle { angle_0, angle_90, angle_180, angle_270 };

const vector<vector<tetris>>& generate_tetris_brick(
    const tetris_game_item& game_item_type,
    const tetris_game_item_angle& orientation_angle =
        tetris_game_item_angle::angle_0) {
  static tetris_game_item last_game_item_type{tetris_game_item::I};
  static tetris_game_item_angle last_game_item_angle{
      tetris_game_item_angle::angle_0};
  static vector<vector<tetris>> last_game_item{
      {tetris::brick, tetris::brick, tetris::brick, tetris::brick}};

  if ((game_item_type == last_game_item_type) &&
      (orientation_angle == last_game_item_angle))
    return last_game_item;

  last_game_item_type = game_item_type;
  last_game_item_angle = orientation_angle;

  switch (game_item_type) {
    case tetris_game_item::I:
      switch (orientation_angle) {
        case tetris_game_item_angle::angle_0:
        case tetris_game_item_angle::angle_180:
          last_game_item = {
              {tetris::brick, tetris::brick, tetris::brick, tetris::brick}};
          return last_game_item;

        case tetris_game_item_angle::angle_90:
        case tetris_game_item_angle::angle_270:
          last_game_item = {{tetris::brick},
                            {tetris::brick},
                            {tetris::brick},
                            {tetris::brick}};
          return last_game_item;
      }

    case tetris_game_item::J:
      switch (orientation_angle) {
        case tetris_game_item_angle::angle_0:
          last_game_item = {{tetris::brick, tetris::brick, tetris::brick},
                            {tetris::empty, tetris::empty, tetris::brick}};
          return last_game_item;

        case tetris_game_item_angle::angle_90:
          last_game_item = {{tetris::brick, tetris::brick},
                            {tetris::brick, tetris::empty},
                            {tetris::brick, tetris::empty}};

          return last_game_item;

        case tetris_game_item_angle::angle_180:
          last_game_item = {{tetris::brick, tetris::empty, tetris::empty},
                            {tetris::brick, tetris::brick, tetris::brick}};
          return last_game_item;

        case tetris_game_item_angle::angle_270:
          last_game_item = {{tetris::empty, tetris::brick},
                            {tetris::empty, tetris::brick},
                            {tetris::brick, tetris::brick}};
          return last_game_item;
      }

    case tetris_game_item::L:
      switch (orientation_angle) {
        case tetris_game_item_angle::angle_0:
          last_game_item = {{tetris::empty, tetris::empty, tetris::brick},
                            {tetris::brick, tetris::brick, tetris::brick}};
          return last_game_item;

        case tetris_game_item_angle::angle_90:
          last_game_item = {{tetris::brick, tetris::brick},
                            {tetris::empty, tetris::brick},
                            {tetris::empty, tetris::brick}};

          return last_game_item;

        case tetris_game_item_angle::angle_180:
          last_game_item = {{tetris::brick, tetris::brick, tetris::brick},
                            {tetris::brick, tetris::empty, tetris::empty}};
          return last_game_item;

        case tetris_game_item_angle::angle_270:
          last_game_item = {{tetris::brick, tetris::empty},
                            {tetris::brick, tetris::empty},
                            {tetris::brick, tetris::brick}};
          return last_game_item;
      }

    case tetris_game_item::O:

      switch (orientation_angle) {
        case tetris_game_item_angle::angle_0:
        case tetris_game_item_angle::angle_90:
        case tetris_game_item_angle::angle_180:
        case tetris_game_item_angle::angle_270:
          last_game_item = {{tetris::brick, tetris::brick},
                            {tetris::brick, tetris::brick}};
          return last_game_item;
      }

    case tetris_game_item::S:
      switch (orientation_angle) {
        case tetris_game_item_angle::angle_0:
        case tetris_game_item_angle::angle_180:
          last_game_item = {{tetris::empty, tetris::brick, tetris::brick},
                            {tetris::brick, tetris::brick, tetris::empty}};
          return last_game_item;

        case tetris_game_item_angle::angle_90:
        case tetris_game_item_angle::angle_270:
          last_game_item = {{tetris::brick, tetris::empty},
                            {tetris::brick, tetris::brick},
                            {tetris::empty, tetris::brick}};
          return last_game_item;
      }

    case tetris_game_item::T:
      switch (orientation_angle) {
        case tetris_game_item_angle::angle_0:
          last_game_item = {{tetris::brick, tetris::brick, tetris::brick},
                            {tetris::empty, tetris::brick, tetris::empty}};
          return last_game_item;

        case tetris_game_item_angle::angle_90:
          last_game_item = {{tetris::brick, tetris::empty},
                            {tetris::brick, tetris::brick},
                            {tetris::brick, tetris::empty}};
          return last_game_item;

        case tetris_game_item_angle::angle_180:
          last_game_item = {{tetris::empty, tetris::brick, tetris::empty},
                            {tetris::brick, tetris::brick, tetris::brick}};
          return last_game_item;

        case tetris_game_item_angle::angle_270:
          last_game_item = {{tetris::empty, tetris::brick},
                            {tetris::brick, tetris::brick},
                            {tetris::empty, tetris::brick}};
          return last_game_item;
      }

    case tetris_game_item::Z:

      switch (orientation_angle) {
        case tetris_game_item_angle::angle_0:
        case tetris_game_item_angle::angle_180:
          last_game_item = {{tetris::brick, tetris::brick, tetris::empty},
                            {tetris::empty, tetris::brick, tetris::brick}};
          return last_game_item;

        case tetris_game_item_angle::angle_90:
        case tetris_game_item_angle::angle_270:
          last_game_item = {{tetris::empty, tetris::brick},
                            {tetris::brick, tetris::brick},
                            {tetris::brick, tetris::empty}};
          return last_game_item;
      }

    default:
      return last_game_item;
  }
}

const vector<vector<vector<tetris>>>&
generate_all_possible_states_for_specified_game_item(
    const tetris_game_item& game_item_type) {
  static vector<vector<vector<tetris>>> game_item_states{
      {generate_tetris_brick(tetris_game_item::I,
                             tetris_game_item_angle::angle_0)},
      {generate_tetris_brick(tetris_game_item::I,
                             tetris_game_item_angle::angle_90)}};

  static tetris_game_item last_game_item_type{tetris_game_item::I};

  if (game_item_type == last_game_item_type)
    return game_item_states;

  last_game_item_type = game_item_type;

  game_item_states.clear();

  switch (game_item_type) {
    case tetris_game_item::I:
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::I, tetris_game_item_angle::angle_0));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::I, tetris_game_item_angle::angle_90));
      return game_item_states;

    case tetris_game_item::J:
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::J, tetris_game_item_angle::angle_0));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::J, tetris_game_item_angle::angle_90));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::J, tetris_game_item_angle::angle_180));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::J, tetris_game_item_angle::angle_270));
      return game_item_states;

    case tetris_game_item::L:
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::L, tetris_game_item_angle::angle_0));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::L, tetris_game_item_angle::angle_90));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::L, tetris_game_item_angle::angle_180));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::L, tetris_game_item_angle::angle_270));
      return game_item_states;

    case tetris_game_item::O:
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::O, tetris_game_item_angle::angle_0));
      return game_item_states;

    case tetris_game_item::S:
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::S, tetris_game_item_angle::angle_0));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::S, tetris_game_item_angle::angle_90));
      return game_item_states;

    case tetris_game_item::T:
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::T, tetris_game_item_angle::angle_0));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::T, tetris_game_item_angle::angle_90));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::T, tetris_game_item_angle::angle_180));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::T, tetris_game_item_angle::angle_270));
      return game_item_states;

    case tetris_game_item::Z:
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::Z, tetris_game_item_angle::angle_0));
      game_item_states.emplace_back(generate_tetris_brick(
          tetris_game_item::Z, tetris_game_item_angle::angle_90));
      return game_item_states;

    default:
      return game_item_states;
  }
}

vector<vector<tetris>> create_tetris_game_board_from_input_string_array(
    string* str_arr,
    const size_t str_arr_size) {
  const size_t game_board_width{str_arr_size};
  const size_t game_board_height{2 * str_arr_size};
  vector<vector<tetris>> game_board(
      game_board_height, vector<tetris>(game_board_width, tetris::empty));

  for (size_t i{}; i < game_board_width; i++) {
    str_arr[i] = trim(str_arr[i]);
    const size_t current_level{stoul(str_arr[i])};

    for (size_t j{game_board_height - 1};
         j >= game_board_height - current_level; j--)
      game_board[j][i] = tetris::brick;
  }

  return game_board;
}

tetris_game_item get_correct_tetris_game_item(const char letter) {
  static string game_item_letters{"IJLOSTZ"};
  static random_device rd{};
  static mt19937 rand_engine{rd()};
  static auto game_item_distr =
      uniform_int_distribution<size_t>(0, game_item_letters.length() - 1);

  switch (letter) {
    case 'i':
    case 'I':
      return tetris_game_item::I;

    case 'j':
    case 'J':
      return tetris_game_item::J;

    case 'l':
    case 'L':
      return tetris_game_item::L;

    case 'o':
    case 'O':
      return tetris_game_item::O;

    case 's':
    case 'S':
      return tetris_game_item::S;

    case 't':
    case 'T':
      return tetris_game_item::T;

    case 'z':
    case 'Z':
      return tetris_game_item::Z;

    default:
      return get_correct_tetris_game_item(
          game_item_letters[game_item_distr(rand_engine)]);
  }
}

void print_game_board(const vector<vector<tetris>>& game_board) {
  size_t start_row{};

  for (; start_row < game_board.size(); start_row++) {
    if (0 != count(begin(game_board[start_row]), end(game_board[start_row]),
                   tetris::game_piece))
      break;
    if (0 != count(begin(game_board[start_row]), end(game_board[start_row]),
                   tetris::brick))
      break;
  }

  const string empty_line(game_board[0].size(), ' ');

  printf("\n|%s|", empty_line.c_str());
  printf("\n|%s|\n", empty_line.c_str());

  for (size_t x{start_row}; x < game_board.size(); x++) {
    printf("|");
    for (size_t y{}; y < game_board[0].size(); y++) {
      printf("%c", tetris::brick == game_board[x][y]
                       ? '#'
                       : tetris::game_piece == game_board[x][y] ? '@' : ' ');
    }
    printf("|\n");
  }

  printf("Press ENTER to continue...");
  cin.get();
}

void add_coordinate_pair_to_list_of_temporarily_filled_fields(
    vector<pair<int, int>>& steps,
    const int x,
    const int y) {
  steps.emplace_back(make_pair(x, y));
}

void clear_previously_filled_fields(vector<vector<tetris>>& game_board,
                                    vector<pair<int, int>>& steps) {
  while (!steps.empty()) {
    game_board[steps.back().first][steps.back().second] = tetris::empty;
    steps.pop_back();
  }
}

size_t count_number_of_completed_lines_on_game_board(
    const vector<vector<tetris>>& game_board) {
  size_t completes_lines{};

  const int game_board_width{static_cast<int>(game_board[0].size())};
  const int game_board_height{static_cast<int>(game_board.size())};

  for (int x{game_board_height - 1}; x >= 0; x--) {
    const auto brick_count = count_if(
        begin(game_board[x]), end(game_board[x]), [](const tetris& game_item) {
          return (game_item == tetris::brick ||
                  game_item == tetris::game_piece);
        });

    if (game_board_width == brick_count)
      completes_lines++;

    if (0 == brick_count)
      break;
  }

  return completes_lines;
}

size_t find_max_number_of_lines_for_current_game_item_position(
    vector<vector<tetris>>& game_board,
    const vector<int>& column_fill_heights,
    const vector<vector<tetris>>& game_item_state) {
  size_t max_lines_count{};

  const int game_board_width{static_cast<int>(game_board[0].size())};
  const int game_board_height{static_cast<int>(game_board.size())};
  const int game_item_width{static_cast<int>(game_item_state[0].size())};
  const int game_item_height{static_cast<int>(game_item_state.size())};

  vector<pair<int, int>> steps{};

  for (int y{}; y + game_item_width <= game_board_width; y++) {
    bool is_placement_done{};

    int row_index{column_fill_heights[y] - 1};

    for (; (!is_placement_done && (row_index >= game_item_height - 1));
         row_index--) {
      bool is_position_correct{true};

      for (int i{}; is_position_correct && i < game_item_height; i++) {
        for (int j{}; j < game_item_width; j++) {
          if (tetris::empty == game_item_state[i][j])
            continue;

          if ((row_index + i >= game_board_height) ||
              (y + j >= game_board_width)) {
            if (!steps.empty())
              clear_previously_filled_fields(game_board, steps);
            is_position_correct = false;
            break;
          }

          if (tetris::brick == game_board[row_index + i][y + j]) {
            if (!steps.empty())
              clear_previously_filled_fields(game_board, steps);
            is_position_correct = false;
            break;
          }

          game_board[row_index + i][y + j] = tetris::game_piece;
          add_coordinate_pair_to_list_of_temporarily_filled_fields(
              steps, row_index + i, y + j);
        }
      }

      if (is_position_correct) {
        is_placement_done = true;
        const size_t completed_lines_count{
            count_number_of_completed_lines_on_game_board(game_board)};
        if (completed_lines_count > max_lines_count)
          max_lines_count = completed_lines_count;
        // print_game_board(game_board);
        clear_previously_filled_fields(game_board, steps);
      }
    }
  }

  return max_lines_count;
}

size_t calculate_greatest_number_of_completed_lines(
    const vector<vector<tetris>>& game_board,
    const tetris_game_item& game_item) {
  const int game_board_width{static_cast<int>(game_board[0].size())};
  const int game_board_height{static_cast<int>(game_board.size())};
  vector<int> column_fill_heights(game_board_width, game_board_height);

  for (int x{}; x < game_board_height; x++) {
    for (int y{}; y < game_board_width; y++) {
      if ((tetris::brick == game_board[x][y]) &&
          (game_board_height == column_fill_heights[y]))
        column_fill_heights[y] = x;
    }
  }

  const auto& game_item_states =
      generate_all_possible_states_for_specified_game_item(game_item);

  size_t max_number_of_lines{};

  vector<vector<tetris>> board{game_board};

  for (const auto& game_item_state : game_item_states) {
    const size_t current_number_of_max_lines{
        find_max_number_of_lines_for_current_game_item_position(
            board, column_fill_heights, game_item_state)};
    if (current_number_of_max_lines > max_number_of_lines)
      max_number_of_lines = current_number_of_max_lines;
  }

  return max_number_of_lines;
}

string TetrisMove(string* str_arr, const size_t str_arr_size) {
  *str_arr = trim(*str_arr);

  const tetris_game_item game_item{get_correct_tetris_game_item(str_arr[0][0])};

  const vector<vector<tetris>> game_board{
      create_tetris_game_board_from_input_string_array(str_arr + 1,
                                                       str_arr_size - 1)};

  return to_string(
      calculate_greatest_number_of_completed_lines(game_board, game_item));
}

int main() {
    
  // string A[] = gets(stdin);
  // cout << TetrisMove(A, sizeof(A)/sizeof(*A));
  string B[] = {"L", "3", "4", "4", "5", "6", "2",
                "0", "6", "5", "3", "6", "6"};
  cout << TetrisMove(B, sizeof(B) / sizeof(*B)) << '\n';  // expected output : 3
  string C[] = {"I", "2", "4", "3", "4", "5", "2",
                "0", "2", "2", "3", "3", "3"};
  cout << TetrisMove(C, sizeof(C) / sizeof(*C)) << '\n';  // expected output : 2
  string D[] = {"O", "4", "3", "2", "3", "5", "1",
                "0", "1", "2", "4", "3", "4"};
  cout << TetrisMove(D, sizeof(D) / sizeof(*D)) << '\n';  // expected output : 0

  return 0;
}
