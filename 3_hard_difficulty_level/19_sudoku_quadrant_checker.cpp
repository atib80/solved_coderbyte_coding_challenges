/*
Coderbyte coding challenge: Sudoku Quadrant Checker

Using the C++ language, have the function SudokuQuadrantChecker(strArr) read the strArr parameter being passed
which will represent a 9x9 Sudoku board of integers ranging from 1 to 9.
The rules of Sudoku are to place each of the 9 integers integer in every row and column
and not have any integers repeat in the respective row, column, or 3x3 sub-grid.
The input strArr will represent a Sudoku board and it will be structured in the following format:
["(N,N,N,N,N,x,x,x,x)","(...)","(...)",...)] where N stands for an integer between 1 and 9 and x will stand for an empty cell.
Your program will determine if the board is legal; the board also does not necessarily have to be finished.
If the board is legal, your program should return the string legal but if it isn't legal,
it should return the 3x3 quadrants (separated by commas) where the errors exist.
The 3x3 quadrants are numbered from 1 to 9 starting from top-left going to bottom-right.

For example, if strArr is: ["(1,2,3,4,5,6,7,8,1)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(1,x,x,x,x,x,x,x,x)",
"(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)"]
then your program should return 1,3,4 since the errors are in quadrants 1, 3 and 4 because of the repeating integer 1.

Another example, if strArr is: ["(1,2,3,4,5,6,7,8,9)","(x,x,x,x,x,x,x,x,x)","(6,x,5,x,3,x,x,4,x)","(2,x,1,1,x,x,x,x,x)",
"(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,9)"]
then your program should return 3,4,5,9.
*/

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <utility>
#include <algorithm>

using namespace std;

string trim(const string &str)
{
    const size_t str_len{str.length()};

    if (!str_len)
        return string{};

    size_t first{}, last{str_len - 1};

    for (; first <= last; ++first)
    {
        if (!isspace(str[first]))
            break;
    }

    if (first > last)
        return string{};

    for (; last > first; --last)
    {
        if (!isspace(str[last]))
            break;
    }

    return str.substr(first, last - first + 1);
}

vector<string> split(const string &source, const char *needle,
                     size_t const max_count = string::npos)
{
    vector<string> parts{};

    string needle_st{needle};

    const size_t source_len{source.length()};

    const size_t needle_len{needle_st.size()};

    if ((0u == source_len) || (0u == needle_len))
        return parts;

    size_t number_of_parts{}, prev{};

    while (true)
    {
        const size_t current{source.find(needle_st, prev)};

        if (string::npos == current)
            break;

        number_of_parts++;

        if ((string::npos != max_count) && (parts.size() == max_count))
            break;

        if ((current - prev) > 0)
            parts.emplace_back(source.substr(prev, current - prev));

        prev = current + needle_len;

        if (prev >= source_len)
            break;
    }

    if (prev < source_len)
    {
        if (string::npos == max_count)
            parts.emplace_back(source.substr(prev));

        else if ((string::npos != max_count) && (parts.size() < max_count))
            parts.emplace_back(source.substr(prev));
    }

    return parts;
}

template <typename _Container>
string join(const _Container &items, const string &needle)
{
    ostringstream oss{};

    auto start = begin(items);

    const auto last = end(items);

    while (start != last)
    {
        oss << *start << needle;

        ++start;
    }

    string result{oss.str()};

    const size_t needle_len{needle.length()};

    result.erase(result.length() - needle_len, needle_len);

    return result;
}

void check_sudoku_row(const vector<vector<int>> &sudoku, const size_t row_index,
                      set<size_t> &found_invalid_grid_indices)
{
    if (row_index >= 9 || 9 != sudoku.size() || 9 != sudoku[0].size())
        return;

    unordered_set<int> found_values{};

    for (size_t y{}; y < 9; y++)
    {
        if (-1 == sudoku[row_index][y])
            continue;

        if (found_values.find(sudoku[row_index][y]) == end(found_values))
        {
            found_values.insert(sudoku[row_index][y]);

            if (1 != count(begin(sudoku[row_index]), end(sudoku[row_index]), sudoku[row_index][y]))
            {
                for (size_t column_index{}; column_index < 9; column_index++)
                {
                    if (sudoku[row_index][y] == sudoku[row_index][column_index])
                        found_invalid_grid_indices.insert((row_index / 3) * 3 + column_index / 3 + 1);
                }
            }
        }
    }
}

void check_sudoku_column(const vector<vector<int>> &sudoku, const size_t column_index,
                         set<size_t> &found_invalid_grid_indices)
{
    if (column_index >= 9 || 9 != sudoku.size() || 9 != sudoku[0].size())
        return;

    vector<int> column(9);

    for (size_t row_index{}; row_index < 9; row_index++)
    {
        column[row_index] = sudoku[row_index][column_index];
    }

    unordered_set<int> found_values{};

    for (size_t x{}; x < 9; x++)
    {
        if (-1 == column[x])
            continue;

        if (found_values.find(column[x]) == end(found_values))
        {
            found_values.insert(column[x]);

            if (1 != count(begin(column), end(column), column[x]))
            {
                for (size_t row_index{}; row_index < 9; row_index++)
                {
                    if (column[x] == column[row_index])
                        found_invalid_grid_indices.insert((row_index / 3) * 3 + column_index / 3 + 1);
                }
            }
        }
    }
}

void check_sudoku_sub_grid(const vector<vector<int>> &sudoku, const size_t sub_grid_index,
                           set<size_t> &found_invalid_grid_indices)
{
    if (sub_grid_index >= 9 || 9 != sudoku.size() || 9 != sudoku[0].size())
        return;

    vector<int> sub_grid_numbers(9);

    for (size_t row_index{sub_grid_index / 3 * 3}, i{}; row_index < (sub_grid_index / 3) * 3 + 3; row_index++)
    {
        for (size_t column_index{(sub_grid_index % 3) * 3}; column_index < (sub_grid_index % 3) * 3 + 3; column_index++)
        {
            sub_grid_numbers[i++] = sudoku[row_index][column_index];
        }
    }

    unordered_set<int> found_values{};

    for (size_t i{}; i < 9; i++)
    {
        if (-1 == sub_grid_numbers[i])
            continue;

        if (found_values.find(sub_grid_numbers[i]) == end(found_values))
        {
            found_values.insert(sub_grid_numbers[i]);

            if (1 != count(begin(sub_grid_numbers), end(sub_grid_numbers), sub_grid_numbers[i]))
            {
                found_invalid_grid_indices.insert(sub_grid_index + 1);
                return;
            }
        }
    }
}

vector<vector<int>> create_sudoku_game_board(string *str_arr, const size_t str_arr_size)
{
    vector<vector<int>> sudoku(9, vector<int>{});
    for (auto &row : sudoku)
        row.resize(9);

    for (size_t i{}; i != str_arr_size; i++)
    {
        str_arr[i] = trim(str_arr[i]);
        str_arr[i].erase(begin(str_arr[i]));
        str_arr[i].erase(--end(str_arr[i]));

        const auto row_values_str = split(str_arr[i], ",", 9);

        for (size_t j{}; j != 9; j++)
        {
            if ("x" != row_values_str[j])
                sudoku[i][j] = stoi(row_values_str[j]);
            else
                sudoku[i][j] = -1;
        }
    }

    return sudoku;
}

string SudokuQuadrantChecker(string *str_arr, const size_t str_arr_size)
{
    const vector<vector<int>> sudoku{create_sudoku_game_board(str_arr, str_arr_size)};

    set<size_t> found_invalid_grid_indices{};

    for (size_t i{}; i < 9; i++)
    {
        check_sudoku_row(sudoku, i, found_invalid_grid_indices);
        check_sudoku_column(sudoku, i, found_invalid_grid_indices);
        check_sudoku_sub_grid(sudoku, i, found_invalid_grid_indices);
    }

    if (found_invalid_grid_indices.empty())
        return "legal";

    return join(found_invalid_grid_indices, ",");
}

int main()
{
    // string A[] = gets(stdin);
    // cout << SudokuQuadrantChecker(A, sizeof(A)/sizeof(*A));
    string B[] = {
        "(1,2,3,4,5,6,7,8,1)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(1,x,x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)"};
    cout << SudokuQuadrantChecker(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: "1,3,4"
    string C[] = {
        "(1,2,3,4,5,6,7,8,9)", "(x,x,x,x,x,x,x,x,x)", "(6,x,5,x,3,x,x,4,x)", "(2,x,1,1,x,x,x,x,x)",
        "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,9)"};
    cout << SudokuQuadrantChecker(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: "3,4,5,9"

    return 0;
}