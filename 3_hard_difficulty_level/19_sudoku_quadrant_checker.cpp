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
#include <array>
#include <cctype>
#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

std::string str_trim(const std::string& input) {
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
auto str_join(const ContainerType& items, const StringType& needle, true_type) {
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
auto str_join(const ContainerType& items,
              CharacterPointerType needle,
              false_type) {
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
auto str_join(const ContainerType& items, const NeedleType& needle) {
  // puts(__PRETTY_FUNCTION__);
  return str_join(
      items, needle,
      conditional_t<is_class_v<NeedleType>, true_type, false_type>{});
}

array<array<int, 9>, 9> create_sudoku_game_board(string* str_arr,
                                                 const size_t str_arr_size) {
  array<array<int, 9>, 9> sudoku{{}};

  for (size_t i{}; i < str_arr_size; ++i) {
    str_arr[i] = str_trim(str_arr[i]);
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
  const array<array<int, 9>, 9> sudoku{
      create_sudoku_game_board(str_arr, str_arr_size)};

  std::array<std::array<size_t, 10>, 9> sudoku_rows_number_frequency{{}};
  std::array<std::array<size_t, 10>, 9> sudoku_row_numbers_subgrid_indices{{}};

  std::array<std::array<size_t, 10>, 9> sudoku_columns_number_frequency{{}};
  std::array<std::array<size_t, 10>, 9> sudoku_column_numbers_subgrid_indices{
      {}};

  std::array<std::array<size_t, 10>, 9> sudoku_subgrids_number_frequency{{}};

  for (size_t i{}; i < 9; ++i) {
    for (size_t j{}; j < 9; ++j) {
      if (-1 != sudoku[i][j]) {
        ++sudoku_rows_number_frequency[i][sudoku[i][j]];
        sudoku_row_numbers_subgrid_indices[i][sudoku[i][j]] |=
            (1U << (i / 3 * 3 + j / 3));

        ++sudoku_columns_number_frequency[j][sudoku[i][j]];
        sudoku_column_numbers_subgrid_indices[j][sudoku[i][j]] |=
            (1U << (i / 3 * 3 + j / 3));

        ++sudoku_subgrids_number_frequency[i / 3 * 3 + j / 3][sudoku[i][j]];
      }
    }
  }

  size_t found_invalid_grid_indices{};

  for (size_t i{}; i < 9; ++i) {
    for (size_t number{1}; number <= 9; ++number) {
      if (sudoku_rows_number_frequency[i][number] > 1U) {
        for (size_t j{}, mask{1}; j < 9; ++j) {
          const size_t index =
              sudoku_row_numbers_subgrid_indices[i][number] & (mask << j);

          if (0U != index)
            found_invalid_grid_indices |= (mask << j);
        }
      }

      if (sudoku_columns_number_frequency[i][number] > 1U) {
        for (size_t j{}, mask{1}; j < 9; ++j) {
          const size_t index =
              sudoku_column_numbers_subgrid_indices[i][number] & (mask << j);

          if (0U != index)
            found_invalid_grid_indices |= (mask << j);
        }
      }

      if (sudoku_subgrids_number_frequency[i][number] > 1U)
        found_invalid_grid_indices |= (1U << i);
    }
  }

  if (0U != found_invalid_grid_indices) {
    string output{};

    for (size_t i{}, mask{1}; i < 9; ++i) {
      if ((found_invalid_grid_indices & (mask << i)) != 0U) {
        output.append({static_cast<char>('1' + i), ','});
      }
    }

    output.pop_back();
    return output;
  }

  return "legal";
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

  string D[] = {
      "(1,2,3,4,5,6,7,8,9)", "(4,5,6,7,8,9,1,2,3)", "(7,8,9,1,2,3,4,5,6)",
      "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)",
      "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)"};
  cout << SudokuQuadrantChecker(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "legal"

  return 0;
}
