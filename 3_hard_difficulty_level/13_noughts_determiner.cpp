/*
Coderbyte codingt challenge: Noughts Determiner

Using the C++ language, have the function NoughtsDeterminer(strArr) take the
strArr parameter being passed which will be an array of size eleven. The array
will take the shape of a Tic-tac-toe board with spaces strArr[3] and strArr[7]
being the separators ("<>") between the rows, and the rest of the spaces will be
either "X", "O", or "-" which signifies an empty space. So for example strArr
may be ["X","O","-","<>","-","O","-","<>","O","X","-"]. This is a Tic-tac-toe
board with each row separated by double arrows ("<>"). Your program should
output the space in the array by which any player could win by putting down
either an "X" or "O". In the array above, the output should be 2 because if an
"O" is placed in strArr[2] then one of the players wins. Each board will only
have one solution for a win, not multiple wins. You output should never be 3 or
7 because those are the separator spaces.

Sample test cases:

Input:  "X","O","-","<>","-","O","-","<>","O","X","-"
Output: 2

Input:  "X","-","O","<>","-","-","O","<>","-","-","X"
Output: 5

Input:  "X","O","X","<>","-","O","O","<>","X","X","O"
Output: 4
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
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

    if ((string::npos != max_count) && (parts.size() == max_count))
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

enum class tic_tac_toe_player { X, O, EMPTY, XO };

class tic_tac_toe {
 public:
  explicit tic_tac_toe(const int dimension = 3) {
    if (dimension < 3)
      throw invalid_argument{
          "Invalid dimension value! Dimension for constructing a valid "
          "tic_tac_toe game board must be >= 3."};

    matrix_.assign(dimension, vector<tic_tac_toe_player>(dimension));
  }

  explicit tic_tac_toe(string* str_arr, const size_t str_arr_size) {
    vector<tic_tac_toe_player> row{};

    size_t prev_col_width{};

    for (size_t i{}; i < str_arr_size; i++) {
      str_arr[i] = trim(str_arr[i]);

      if ("<>" != str_arr[i]) {
        if ("X" == str_arr[i])
          row.emplace_back(tic_tac_toe_player::X);
        else if ("O" == str_arr[i])
          row.emplace_back(tic_tac_toe_player::O);
        else if ("-" == str_arr[i])
          row.emplace_back(tic_tac_toe_player::EMPTY);
      } else {
        if (!prev_col_width)
          prev_col_width = row.size();
        else if (row.size() != prev_col_width)
          throw runtime_error{"Matrix rows must have equal column widths!"};
        matrix_.emplace_back(row);
        row.clear();
      }
    }

    if (prev_col_width && row.size() != prev_col_width)
      throw runtime_error{"Matrix rows must have equal column widths!"};

    if (!row.empty())
      matrix_.emplace_back(row);

    if (matrix_.size() != matrix_[0].size())
      throw runtime_error{
          "Matrix must have identical number of rows and columns (square "
          "matrix)!"};
  }

  size_t get_dimension() const noexcept { return matrix_.size(); }

  static vector<vector<tic_tac_toe_player>> transpose(
      const vector<vector<tic_tac_toe_player>>& matrix) {
    if (matrix.empty())
      return vector<vector<tic_tac_toe_player>>{};

    const size_t rc{matrix.size()};
    const size_t cc{matrix[0].size()};

    vector<vector<tic_tac_toe_player>> transposed_matrix(
        cc, vector<tic_tac_toe_player>(rc));

    for (size_t i{}; i < rc; i++) {
      for (size_t j{}; j < cc; j++)

        transposed_matrix[j][i] = matrix[i][j];
    }

    return transposed_matrix;
  }

  static size_t calculate_correct_position_index(const tic_tac_toe& t,
                                                 const size_t position_index) {
    const size_t dim{t.get_dimension()};

    size_t position{dim}, offset{};

    while (position <= position_index) {
      offset++;
      position += dim;
    }

    return position_index + offset;
  }

  static bool check_if_player_won_tic_tac_toe_game(
      const vector<vector<tic_tac_toe_player>>& t,
      const tic_tac_toe_player& tp) {
    for (const auto& row : t) {
      if (all_of(begin(row), end(row),
                 [&](const tic_tac_toe_player& p) { return p == tp; }))
        return true;
    }

    const vector<vector<tic_tac_toe_player>> tt{transpose(t)};

    for (const auto& row : tt) {
      if (all_of(begin(row), end(row),
                 [&](const tic_tac_toe_player& p) { return p == tp; }))
        return true;
    }

    const size_t dim{t.size()};

    if (dim != t[0].size())
      return false;

    bool is_diagonal_match{true};

    for (size_t x1{}, y1{}; x1 < dim; x1++, y1++) {
      if (t[x1][y1] != tp) {
        is_diagonal_match = false;
        break;
      }
    }

    if (is_diagonal_match)
      return true;

    is_diagonal_match = true;

    for (size_t x2{}, y2{dim - 1}; x2 < dim; x2++, y2--) {
      if (t[x2][y2] != tp) {
        is_diagonal_match = false;
        break;
      }
    }

    if (is_diagonal_match)
      return true;

    return false;
  }

  static bool does_player_have_identical_tic_tac_toe_neighbor(
      const tic_tac_toe& game_board,
      const tic_tac_toe_player tp,
      const size_t x,
      const size_t y) {
    const size_t dim{game_board.get_dimension()};

    const size_t min_x{x > 0u ? x - 1 : 0u};
    const size_t max_x{x < dim - 1 ? x + 1 : dim - 1};
    const size_t min_y{y > 0u ? y - 1 : 0u};
    const size_t max_y{y < dim - 1 ? y + 1 : dim - 1};

    for (size_t i{min_x}; i <= max_x; i++) {
      for (size_t j{min_y}; j <= max_y; j++) {
        if (x == i && y == j)
          continue;

        if (tp == game_board(i, j))
          return true;
      }
    }

    return false;
  }

  size_t find_correct_spot_for_winning(
      const tic_tac_toe_player tp = tic_tac_toe_player::XO) {
    tic_tac_toe& t{*this};

    const size_t dim{get_dimension()};

    if (tic_tac_toe_player::XO == tp) {
      for (size_t x{}; x < dim; x++) {
        for (size_t y{}; y < dim; y++) {
          if (tic_tac_toe_player::EMPTY == t(x, y)) {
            if (does_player_have_identical_tic_tac_toe_neighbor(
                    *this, tic_tac_toe_player::X, x, y)) {
              t(x, y) = tic_tac_toe_player::X;
              if (check_if_player_won_tic_tac_toe_game(t.get_matrix_contents(),
                                                       tic_tac_toe_player::X))
                return calculate_correct_position_index(
                    t, x * get_dimension() + y);
            }

            if (does_player_have_identical_tic_tac_toe_neighbor(
                    *this, tic_tac_toe_player::O, x, y)) {
              t(x, y) = tic_tac_toe_player::O;
              if (check_if_player_won_tic_tac_toe_game(t.get_matrix_contents(),
                                                       tic_tac_toe_player::O))
                return calculate_correct_position_index(
                    t, x * get_dimension() + y);
            }
            t(x, y) = tic_tac_toe_player::EMPTY;
          }
        }
      }
    } else if (tic_tac_toe_player::X == tp) {
      for (size_t x{}; x < dim; x++) {
        for (size_t y{}; y < dim; y++) {
          if (tic_tac_toe_player::EMPTY == t(x, y) &&
              does_player_have_identical_tic_tac_toe_neighbor(
                  *this, tic_tac_toe_player::X, x, y)) {
            t(x, y) = tic_tac_toe_player::X;
            if (check_if_player_won_tic_tac_toe_game(t.get_matrix_contents(),
                                                     tic_tac_toe_player::X))
              return calculate_correct_position_index(t,
                                                      x * get_dimension() + y);

            t(x, y) = tic_tac_toe_player::EMPTY;
          }
        }
      }
    } else if (tic_tac_toe_player::O == tp) {
      for (size_t x{}; x < dim; x++) {
        for (size_t y{}; y < dim; y++) {
          if (tic_tac_toe_player::EMPTY == t(x, y) &&
              does_player_have_identical_tic_tac_toe_neighbor(
                  *this, tic_tac_toe_player::O, x, y)) {
            t(x, y) = tic_tac_toe_player::O;
            if (check_if_player_won_tic_tac_toe_game(t.get_matrix_contents(),
                                                     tic_tac_toe_player::O))
              return calculate_correct_position_index(t,
                                                      x * get_dimension() + y);
            t(x, y) = tic_tac_toe_player::EMPTY;
          }
        }
      }
    }

    return string::npos;
  }

  vector<vector<tic_tac_toe_player>>& get_matrix_contents() { return matrix_; };

  const vector<vector<tic_tac_toe_player>>& get_matrix_contents() const {
    return matrix_;
  };

  bool operator==(const tic_tac_toe& t) const {
    const size_t dim{get_dimension()};

    if (t.get_dimension() != dim)
      return false;

    for (size_t x{}; x < dim; x++) {
      for (size_t y{}; y < dim; y++) {
        if (t(x, y) != (*this)(x, y))
          return false;
      }
    }

    return true;
  }

  tic_tac_toe_player operator()(const size_t i, const size_t j) const {
    if (i >= matrix_.size()) {
      ostringstream oss{};
      oss << "Specified row index (i = " << i << ") is out of bounds!";
      throw range_error(oss.str());
    }

    if (j >= matrix_[i].size()) {
      ostringstream oss{};
      oss << "Specified column index (j = " << j << ") is out of bounds!";
      throw range_error(oss.str());
    }

    return matrix_[i][j];
  }

  tic_tac_toe_player& operator()(const size_t i, const size_t j) {
    if (i >= matrix_.size()) {
      ostringstream oss{};
      oss << "Specified row index (i = " << i << ") is out of bounds!";
      throw range_error(oss.str());
    }

    if (j >= matrix_[i].size()) {
      ostringstream oss{};
      oss << "Specified column index (j = " << j << ") is out of bounds!";
      throw range_error(oss.str());
    }

    return matrix_[i][j];
  }

  string to_string() const {
    ostringstream oss{};

    oss << "\n__________\n";

    for (const auto& row : matrix_) {
      for (const auto& element : row) {
        if (tic_tac_toe_player::X == element)
          oss << "|X";
        else if (tic_tac_toe_player::O == element)
          oss << "|O";
      }

      oss << "|\n__________";
    }

    return oss.str();
  }

 private:
  vector<vector<tic_tac_toe_player>> matrix_;
};

ostream& operator<<(ostream& ostr, const tic_tac_toe& m) {
  const auto& matrix_contents = m.get_matrix_contents();

  ostr << "\n__________\n";

  for (const auto& row : matrix_contents) {
    for (const auto& element : row) {
      if (tic_tac_toe_player::X == element)
        ostr << "|X";
      else if (tic_tac_toe_player::O == element)
        ostr << "|O";
    }

    ostr << "|\n__________";
  }

  return ostr;
}

istream& operator>>(istream& istr, tic_tac_toe& m) {
  auto& matrix = m.get_matrix_contents();

  matrix.clear();

  vector<tic_tac_toe_player> row{};
  string line{};
  size_t prev_col_width{};

  while (getline(istr, line)) {
    line = trim(line);

    if (line != "<>") {
      if ("X" == line)
        row.emplace_back(tic_tac_toe_player::X);
      else if ("O" == line)
        row.emplace_back(tic_tac_toe_player::O);
      else if ("-" == line)
        row.emplace_back(tic_tac_toe_player::EMPTY);
    } else {
      if (!prev_col_width)
        prev_col_width = row.size();
      else if (row.size() != prev_col_width)
        throw runtime_error{
            "The rows of matrix must have equal column widths!"};
      matrix.emplace_back(row);
      row.clear();
    }

    if (prev_col_width && (row.size() != prev_col_width))
      throw runtime_error{"The rows of matrix must have equal column widths!"};

    if (!row.empty())
      matrix.emplace_back(row);
  }

  return istr;
}

string NoughtsDeterminer(string* str_arr, const size_t str_arr_size) {
  tic_tac_toe t{str_arr, str_arr_size};

  // called with tic_tac_toe_player::XO by default in order to instruct the
  // function to check both players (tic_tac_toe_player::X,
  // tic_tac_toe_player::O)
  const size_t space{t.find_correct_spot_for_winning()};

  if (string::npos != space)
    return to_string(space);

  return "-1";
}

int main() {
  // string A[] = gets(stdin);
  // cout << NoughtsDeterminer(A, sizeof(A) / sizeof(*A));
  string B[] = {"X", "O", "-", "<>", "-", "O", "-", "<>", "O", "X", "-"};
  cout << NoughtsDeterminer(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "2"
  string C[] = {"X", "-", "O", "<>", "-", "-", "O", "<>", "-", "-", "X"};
  cout << NoughtsDeterminer(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "5"
  string D[] = {"X", "O", "X", "<>", "-", "O", "O", "<>", "X", "X", "O"};
  cout << NoughtsDeterminer(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "4"

  string E[] = {"O", "-", "O", "<>", "-", "X", "-", "<>", "-", "-", "X"};
  cout << NoughtsDeterminer(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "1"
  string F[] = {"X", "-", "X", "<>", "-", "O", "-", "<>", "-", "-", "O"};
  cout << NoughtsDeterminer(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "1"
  string G[] = {"X", "-", "O", "<>", "-", "O", "-", "<>", "-", "-", "X"};
  cout << NoughtsDeterminer(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: "8"

  string H[] = {"X", "O", "X", "<>", "-", "O", "-", "<>", "-", "-", "-"};
  cout << NoughtsDeterminer(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: "9"
  string I[] = {"X", "-", "X", "<>", "-", "-", "O", "<>", "O", "-", "-"};
  cout << NoughtsDeterminer(I, sizeof(I) / sizeof(*I))
       << '\n';  // expected output: "1"
  string J[] = {"-", "-", "X", "<>", "-", "O", "X", "<>", "O", "-", "-"};
  cout << NoughtsDeterminer(J, sizeof(J) / sizeof(*J))
       << '\n';  // expected output: "10"
  string K[] = {"-", "-", "X", "<>", "-", "O", "X", "<>", "O", "-", "-"};
  cout << NoughtsDeterminer(K, sizeof(K) / sizeof(*K))
       << '\n';  // expected output: "10"
  return 0;
}
