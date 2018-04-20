/*
Coderbyte coding challenge: Matrix Border v2

(solution implemented by using iterative method)

Using the C++ language, have the function MatrixBorder(strArr) read the strArr
parameter being passed which will represent an NxN matrix filled with 1's and
0's. Your program should determine the number of swaps between two rows or two
columns that must be made to change the matrix such that the border of the
matrix contains all 1's and the inside contains 0's. The format of strArr will
be: ["(n,n,n...)","(...)",...] where n represents either a 1 or 0. The smallest
matrix will be a 3x3 and the largest will be a 6x6 matrix.

For example: if strArr is: ["(0,1,1)","(1,1,1)","(1,1,1)"] then you can swap the
first two columns and then swap the first two rows to create a matrix with the
1's on the border and the 0 on the inside, therefore your program should
output 2.

Sample test cases:

Input:  "(0,1,1)","(1,1,1)","(1,1,1)"
Output: 2

Input:  "(0,1,0,1)","(1,1,1,1)","(0,1,0,1)","(1,1,1,1)"
Output: 2
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
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

void swap_matrix_rows(vector<vector<int>>& matrix,
                      const size_t i,
                      const size_t j) {
  if (matrix.empty() || i == j || i >= matrix.size() || j >= matrix.size() ||
      matrix[i].size() != matrix[j].size())
    return;

  for (size_t y{}; y < matrix[i].size(); y++) {
    swap(matrix[i][y], matrix[j][y]);
  }
}

void swap_matrix_columns(vector<vector<int>>& matrix,
                         const size_t i,
                         const size_t j) {
  if (matrix.empty() || i == j || i >= matrix.size() || j >= matrix.size())
    return;

  for (size_t x{}; x < matrix[i].size(); x++) {
    swap(matrix[x][i], matrix[x][j]);
  }
}

vector<vector<int>> create_matrix_from_input_string_array(
    string* str_arr,
    const size_t str_arr_size) {
  vector<vector<int>> matrix(str_arr_size, vector<int>(str_arr_size, 0));

  for (size_t i{}; i < str_arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);
    str_arr[i].erase(begin(str_arr[i]));
    str_arr[i].erase(--end(str_arr[i]));
    const vector<string> row_values{split(str_arr[i], ",", str_arr_size)};
    for (size_t j{}; j < row_values.size(); j++)
      matrix[i][j] = stoi(row_values[j]);
  }

  return matrix;
}

bool check_matrix_border_values(const vector<vector<int>>& matrix) {
  if (matrix.empty())
    return false;

  for (size_t y{}; y < matrix.size(); y++) {
    if (!matrix[0][y] || !matrix[matrix.size() - 1][y])
      return false;
  }

  for (size_t x{}; x < matrix.size(); x++) {
    if (!matrix[x][0] || !matrix[x][matrix.size() - 1])
      return false;
  }

  return true;
}

bool check_matrix_row(const vector<vector<int>>& matrix,
                      const size_t row_index,
                      const int flag_value) {
  if (matrix.empty() || row_index >= matrix.size())
    return false;

  for (size_t y{}; y < matrix[row_index].size(); y++) {
    if (flag_value != matrix[row_index][y])
      return false;
  }

  return true;
}

bool check_matrix_column(const vector<vector<int>>& matrix,
                         const size_t col_index,
                         const int flag_value) {
  if (matrix.empty() || col_index >= matrix[0].size())
    return false;

  for (size_t x{}; x < matrix.size(); x++) {
    if (flag_value != matrix[x][col_index])
      return false;
  }

  return true;
}

size_t find_minimum_number_of_swap_operations(vector<vector<int>> matrix) {
  size_t minimum_number_of_swaps{string::npos};
  const int nth = matrix.size() - 1;
  queue<pair<size_t, vector<vector<int>>>> q{{make_pair(0, move(matrix))}};

  while (!q.empty()) {
    const size_t iter_count{q.front().first};
    vector<vector<int>> m{move(q.front().second)};
    q.pop();

    if (check_matrix_border_values(m)) {
      minimum_number_of_swaps = iter_count;
      continue;
    }

    if (iter_count + 1 >= minimum_number_of_swaps)
      continue;

    for (int col1{1}, col2{nth - 1}; col1 <= nth && col2 >= 0; col1++, col2--) {
      if (!check_matrix_column(m, 0, 1)) {
        swap_matrix_columns(m, 0, col1);
        q.emplace(make_pair(iter_count + 1, m));
        swap_matrix_columns(m, 0, col1);
      }

      if (!check_matrix_column(m, nth, 1)) {
        swap_matrix_columns(m, nth, col2);
        q.emplace(make_pair(iter_count + 1, m));
        swap_matrix_columns(m, nth, col2);
      }
    }

    for (int row1{1}, row2{nth - 1}; row1 <= nth && row2 >= 0; row1++, row2--) {
      if (!check_matrix_row(m, 0, 1)) {
        swap_matrix_rows(m, 0, row1);
        q.emplace(make_pair(iter_count + 1, m));
        swap_matrix_rows(m, 0, row1);
      }

      if (!check_matrix_row(m, nth, 1)) {
        swap_matrix_rows(m, nth, row2);
        q.emplace(make_pair(iter_count + 1, m));
        swap_matrix_rows(m, nth, row2);
      }
    }
  }

  return minimum_number_of_swaps;
}

string MatrixBorder(string* str_arr, const size_t str_arr_size) {
  if (!str_arr || str_arr_size < 2)
    return "not possible";

  vector<vector<int>> matrix{
      create_matrix_from_input_string_array(str_arr, str_arr_size)};

  if (matrix.size() != matrix[0].size())
    return "not possible";

  return to_string(find_minimum_number_of_swap_operations(move(matrix)));
}

int main() {
  // string A[] = gets(stdin);
  // cout << MatrixBorder(A, sizeof(A)/sizeof(*A));
  string B[] = {"(0,1,1)", "(1,1,1)", "(1,1,1)"};
  cout << MatrixBorder(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "2"
  string C[] = {"(0,1,0,1)", "(1,1,1,1)", "(0,1,0,1)", "(1,1,1,1)"};
  cout << MatrixBorder(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "2"
  string D[] = {"(0,1,0,1)", "(1,1,1,1)", "(1,1,1,1)", "(0,1,0,1)"};
  cout << MatrixBorder(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "3"
  string E[] = {"(1,1,1,1,1)", "(1,0,0,1,0)", "(1,0,0,1,0)", "(1,0,0,1,0)",
                "(1,1,1,1,1)"};
  cout << MatrixBorder(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "1"
  string F[] = {"(1,0,0,1,0)", "(1,1,1,1,1)", "(1,0,0,1,0)", "(1,0,0,1,0)",
                "(1,1,1,1,1)"};
  cout << MatrixBorder(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "2"
  string G[] = {"(0,1,0,1,0)", "(1,1,1,1,1)", "(0,1,0,1,0)", "(0,1,0,1,0)",
                "(1,1,1,1,1)"};
  cout << MatrixBorder(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: "3"
  string H[] = {"(1,0,0,0,0,1)", "(1,1,1,1,1,1)", "(1,0,0,0,0,1)",
                "(1,0,0,0,0,1)", "(1,1,1,1,1,1)", "(1,0,0,0,0,1)"};
  cout << MatrixBorder(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: "2"

  return 0;
}
