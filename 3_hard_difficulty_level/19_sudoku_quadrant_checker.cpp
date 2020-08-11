/*
Coderbyte coding challenge: Sudoku Quadrant Checker

Using the C++ language, have the function SudokuQuadrantChecker(strArr) read the
strArr parameter being passed which will represent a 9x9 Sudoku board of
integers ranging from 1 to 9. The rules of Sudoku are to place each of the 9
integers integer in every row and column and not have any integers repeat in the
respective row, column, or 3x3 sub-grid. The input strArr will represent a
Sudoku board and it will be structured in the following format:
["(N,N,N,N,N,x,x,x,x)","(...)","(...)",...)] where N stands for an integer
between 1 and 9 and x will stand for an empty cell. Your program will determine
if the board is legal; the board also does not necessarily have to be finished.
If the board is legal, your program should return the string legal but if it
isn't legal, it should return the 3x3 quadrants (separated by commas) where the
errors exist. The 3x3 quadrants are numbered from 1 to 9 starting from top-left
going to bottom-right.

For example, if strArr is:
["(1,2,3,4,5,6,7,8,1)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(1,x,x,x,x,x,x,x,x)",
"(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)"]
then your program should return 1,3,4 since the errors are in quadrants 1, 3 and
4 because of the repeating integer 1.

Another example, if strArr is:
["(1,2,3,4,5,6,7,8,9)","(x,x,x,x,x,x,x,x,x)","(6,x,5,x,3,x,x,4,x)","(2,x,1,1,x,x,x,x,x)",
"(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,9)"]
then your program should return 3,4,5,9.
*/

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

std::string trim(const std::string& input) {
  std::string output{input};
  output.erase(std::cbegin(output),
               std::find_if(std::cbegin(output), std::cend(output),
                            [](const char ch) { return !isspace(ch); }));

  output.erase(std::find_if(output.crbegin(), output.crend(),
                            [](const char ch) { return !isspace(ch); })
                   .base(),
               std::cend(output));

  return output;
}

std::pair<std::size_t, std::size_t> str_find_first_needle_position(
    std::string_view src_sv,
    const std::vector<std::string_view>& needle_parts,
    const size_t start_pos = 0U) {
  size_t first_needle_pos{std::string_view::npos};
  size_t needle_len{};

  for (const auto& needle_sv : needle_parts) {
    const size_t needle_start_pos = src_sv.find(needle_sv, start_pos);
    if (needle_start_pos < first_needle_pos) {
      first_needle_pos = needle_start_pos;
      needle_len = needle_sv.length();
    }
  }

  return {first_needle_pos, needle_len};
}

std::vector<std::string> str_split(const std::string& src,
                                   const char* needle,
                                   const char* needle_parts_separator_token,
                                   const bool split_on_whole_needle = false,
                                   const bool ignore_empty_string = true,
                                   size_t const max_count = std::string::npos) {
  const size_t src_len{src.length()};

  if (0U == src_len)
    return {};

  std::string_view src_sv{src};

  if (nullptr == needle)
    return {};

  const size_t needle_len = std::strlen(needle);

  if (0U == needle_len) {
    const size_t upper_limit{max_count < src_len ? max_count : src_len};
    std::vector<std::string> parts{};
    parts.reserve(upper_limit);
    for (size_t i{}; i < upper_limit; ++i)
      parts.emplace_back(1, src_sv[i]);
    return parts;
  }

  std::string_view needle_sv{needle, needle_len};

  const size_t needle_parts_separator_token_len =
      needle_parts_separator_token != nullptr
          ? std::strlen(needle_parts_separator_token)
          : 0;

  std::string_view needle_parts_separator_token_sv{
      needle_parts_separator_token, needle_parts_separator_token_len};

  std::vector<std::string_view> needle_parts{};

  if (needle_parts_separator_token_len > 0U && !split_on_whole_needle) {
    size_t start_pos{};

    while (true) {
      const size_t next_pos{
          needle_sv.find(needle_parts_separator_token_sv, start_pos)};

      if (std::string_view::npos == next_pos) {
        needle_parts.emplace_back(needle_sv.data() + start_pos,
                                  needle_len - start_pos);
        break;
      }

      needle_parts.emplace_back(needle_sv.data() + start_pos,
                                next_pos - start_pos);

      start_pos = next_pos + needle_parts_separator_token_len;
    }
  } else
    needle_parts.emplace_back(needle_sv);

  std::vector<std::string> parts{};
  size_t number_of_parts{}, prev{};

  while (true) {
    const auto [current, needle_part_len] =
        str_find_first_needle_position(src_sv, needle_parts, prev);

    if (std::string_view::npos == current || 0U == needle_part_len ||
        parts.size() == max_count)
      break;

    if (current - prev > 0U) {
      parts.emplace_back(std::cbegin(src_sv) + prev,
                         std::cbegin(src_sv) + current);
      ++number_of_parts;
    } else if (!ignore_empty_string) {
      parts.emplace_back();
      ++number_of_parts;
    }

    prev = current + needle_part_len;

    if (prev >= src_len)
      break;
  }

  if (parts.size() < max_count) {
    if (prev < src_len)
      parts.emplace_back(std::cbegin(src_sv) + prev, std::cend(src_sv));
    else if (!ignore_empty_string)
      parts.emplace_back();
  }

  return parts;
}

template <typename ContainerType, typename StringType>
auto join(const ContainerType& items, const StringType& needle, true_type) {
  // puts(__PRETTY_FUNCTION__);

  static_assert(
      is_same_v<string, StringType> || is_same_v<wstring, StringType> ||
          is_same_v<u16string, StringType> || is_same_v<u32string, StringType>,
      "StringType must correspond to one of the existing C++ "
      "basic_string<T> types!");

  using char_type = typename StringType::value_type;

  basic_ostringstream<char_type> oss{};

  auto start = begin(items);

  const auto last = end(items);

  while (start != last) {
    oss << *start << needle;
    ++start;
  }

  const size_t needle_len{needle.length()};

  basic_string<char_type> result{oss.str()};

  result.erase(result.length() - needle_len, needle_len);

  return result;
}

template <typename ContainerType, typename CharacterPointerType>
auto join(const ContainerType& items, CharacterPointerType needle, false_type) {
  using char_type = remove_const_t<remove_pointer_t<CharacterPointerType>>;

  // puts(__PRETTY_FUNCTION__);

  static_assert(is_same_v<const char*, CharacterPointerType> ||
                    is_same_v<const wchar_t*, CharacterPointerType> ||
                    is_same_v<const char16_t*, CharacterPointerType> ||
                    is_same_v<const char32_t*, CharacterPointerType>,
                "CharacterPointerType must correspond to one of the existing "
                "const character pointer types!");

  basic_ostringstream<char_type> oss{};

  auto start = begin(items);

  const auto last = end(items);

  while (start != last) {
    oss << *start << needle;
    ++start;
  }

  basic_string<char_type> needle_str{needle};

  const size_t needle_len{needle_str.length()};

  basic_string<char_type> result{oss.str()};

  result.erase(result.length() - needle_len, needle_len);

  return result;
}

template <typename ContainerType, typename NeedleType>
auto join(const ContainerType& items, const NeedleType& needle) {
  // puts(__PRETTY_FUNCTION__);
  return join(items, needle,
              conditional_t<is_class_v<NeedleType>, true_type, false_type>{});
}

void check_sudoku_row(const vector<vector<int>>& sudoku,
                      const size_t row_index,
                      set<size_t>& found_invalid_grid_indices) {
  if (row_index >= 9) {
    ostringstream oss{};
    oss << "You've specified an invalid row index (" << row_index
        << ")!\nRow index must safisfy the following rule: 0 <= row_index < 9!";
    throw invalid_argument{oss.str()};
  }

  if (9 != sudoku.size()) {
    ostringstream oss{};
    oss << "Invalid row count (" << sudoku.size()
        << ")!\nSudoku matrix must have 9 rows!";
    throw invalid_argument{oss.str()};
  }

  if (9 != sudoku[0].size()) {
    ostringstream oss{};
    oss << "Invalid column count (" << sudoku[0].size()
        << ")!\nSudoku matrix must have 9 columns!";
    throw invalid_argument{oss.str()};
  }

  unordered_set<int> found_values{};

  for (size_t y{}; y < 9; ++y) {
    if (-1 == sudoku[row_index][y])
      continue;

    if (!found_values.count(sudoku[row_index][y])) {
      found_values.insert(sudoku[row_index][y]);

      if (1 != count(begin(sudoku[row_index]), end(sudoku[row_index]),
                     sudoku[row_index][y])) {
        for (size_t column_index{}; column_index < 9; ++column_index) {
          if (sudoku[row_index][y] == sudoku[row_index][column_index])
            found_invalid_grid_indices.insert(row_index / 3 * 3 +
                                              column_index / 3 + 1);
        }
      }
    }
  }
}

void check_sudoku_column(const vector<vector<int>>& sudoku,
                         const size_t column_index,
                         set<size_t>& found_invalid_grid_indices) {
  if (column_index >= 9) {
    ostringstream oss{};
    oss << "You've specified an invalid column index (" << column_index
        << ")!\nColumn index must safisfy the following rule: 0 <= "
           "column_index < 9!";
    throw invalid_argument{oss.str()};
  }

  if (9 != sudoku.size()) {
    ostringstream oss{};
    oss << "Invalid row count (" << sudoku.size()
        << ")!\nSudoku matrix must have 9 rows!";
    throw invalid_argument{oss.str()};
  }

  if (9 != sudoku[0].size()) {
    ostringstream oss{};
    oss << "Invalid column count (" << sudoku[0].size()
        << ")!\nSudoku matrix must have 9 columns!";
    throw invalid_argument{oss.str()};
  }

  vector<int> column(9);

  for (size_t row_index{}; row_index < 9; ++row_index) {
    column[row_index] = sudoku[row_index][column_index];
  }

  unordered_set<int> found_values{};

  for (size_t x{}; x < 9; ++x) {
    if (-1 == column[x])
      continue;

    if (!found_values.count(column[x])) {
      found_values.insert(column[x]);

      if (1 != count(begin(column), end(column), column[x])) {
        for (size_t row_index{}; row_index < 9; ++row_index) {
          if (column[x] == column[row_index])
            found_invalid_grid_indices.insert(row_index / 3 * 3 +
                                              column_index / 3 + 1);
        }
      }
    }
  }
}

void check_sudoku_sub_grid(const vector<vector<int>>& sudoku,
                           const size_t sub_grid_index,
                           set<size_t>& found_invalid_grid_indices) {
  if (sub_grid_index >= 9) {
    ostringstream oss{};
    oss << "You've specified an invalid sub-grid index index ("
        << sub_grid_index
        << ")!\nSub-grid index index must safisfy the following rule: 0 <= "
           "sub_grid_index < 9!";
    throw invalid_argument{oss.str()};
  }

  if (9 != sudoku.size()) {
    ostringstream oss{};
    oss << "Invalid row count (" << sudoku.size()
        << ")!\nSudoku matrix must have 9 rows!";
    throw invalid_argument{oss.str()};
  }

  if (9 != sudoku[0].size()) {
    ostringstream oss{};
    oss << "Invalid column count (" << sudoku[0].size()
        << ")!\nSudoku matrix must have 9 columns!";
    throw invalid_argument{oss.str()};
  }

  vector<int> sub_grid_numbers(9);

  for (size_t row_index{sub_grid_index / 3 * 3}, i{};
       row_index < sub_grid_index / 3 * 3 + 3; ++row_index) {
    for (size_t column_index{sub_grid_index % 3 * 3};
         column_index < sub_grid_index % 3 * 3 + 3; ++column_index) {
      sub_grid_numbers[i++] = sudoku[row_index][column_index];
    }
  }

  unordered_set<int> found_values{};

  for (size_t i{}; i < 9; ++i) {
    if (-1 == sub_grid_numbers[i])
      continue;

    if (!found_values.count(sub_grid_numbers[i])) {
      found_values.insert(sub_grid_numbers[i]);

      if (1 != count(begin(sub_grid_numbers), end(sub_grid_numbers),
                     sub_grid_numbers[i])) {
        found_invalid_grid_indices.insert(sub_grid_index + 1);
        return;
      }
    }
  }
}

vector<vector<int>> create_sudoku_game_board(string* str_arr,
                                             const size_t str_arr_size) {
  vector<vector<int>> sudoku(9, vector<int>(9));

  for (size_t i{}; i < str_arr_size; ++i) {
    str_arr[i] = trim(str_arr[i]);
    str_arr[i].erase(begin(str_arr[i]));
    str_arr[i].erase(--end(str_arr[i]));

    const vector<string> row_values_str{
        str_split(str_arr[i], ",", nullptr, true, true, 9)};

    for (size_t j{}; j < 9; ++j) {
      if ("x" != row_values_str[j] && "X" != row_values_str[j])
        sudoku[i][j] = stoi(row_values_str[j]);
      else
        sudoku[i][j] = -1;
    }
  }

  return sudoku;
}

string SudokuQuadrantChecker(string* str_arr, const size_t str_arr_size) {
  const vector<vector<int>> sudoku{
      create_sudoku_game_board(str_arr, str_arr_size)};
  set<size_t> found_invalid_grid_indices{};

  for (size_t i{}; i < 9; ++i) {
    check_sudoku_row(sudoku, i, found_invalid_grid_indices);
    check_sudoku_column(sudoku, i, found_invalid_grid_indices);
    check_sudoku_sub_grid(sudoku, i, found_invalid_grid_indices);
  }

  if (found_invalid_grid_indices.empty())
    return "legal";

  return join(found_invalid_grid_indices, ",");
}

int main() {
  // string A[] = gets(stdin);
  // cout << SudokuQuadrantChecker(A, sizeof(A)/sizeof(*A));
  string B[] = {
      "(1,2,3,4,5,6,7,8,1)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)",
      "(1,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)",
      "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)"};
  cout << SudokuQuadrantChecker(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "1,3,4"
  string C[] = {
      "(1,2,3,4,5,6,7,8,9)", "(x,x,x,x,x,x,x,x,x)", "(6,x,5,x,3,x,x,4,x)",
      "(2,x,1,1,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)",
      "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,9)"};
  cout << SudokuQuadrantChecker(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "3,4,5,9"

  return 0;
}
