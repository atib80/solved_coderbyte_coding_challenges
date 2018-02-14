/*
Coderbyte coding challenge: Matrix Path

Using the C++ language, have the function MatrixPath(strArr) take the strArr
parameter being passed which will be a 2D matrix of 0 and 1's of some arbitrary
size, and determine if a path of 1's exists from the top-left of the matrix to
the bottom-right of the matrix while moving only in the directions: up, down,
left, and right. If a path exists your program should return the string true,
otherwise your program should return the number of locations in the matrix where
if a single 0 is replaced with a 1, a path of 1's will be created successfully.
If a path does not exist and you cannot create a path by changing a single
location in the matrix from a 0 to a 1, then your program should return the
string not possible. For example: if strArr is ["11100", "10011", "10101",
"10011"] then this looks like the following matrix:

1 1 1 0 0
1 0 0 1 1
1 0 1 0 1
1 0 0 1 1

For the input above, a path of 1's from the top-left to the bottom-right does
not exist. But, we can change a 0 to a 1 in 2 places in the matrix, namely at
locations: 0,3] or [1,2]. So for this input your program should return 2. The
top-left and bottom-right of the input matrix will always be 1's.

Sample test cases:


1 0 0 0 0
1 1 0 1 1
1 0 1 0 1
1 1 0 0 1

Input:  "10000", "11011", "10101", "11001"
Output: 1

Input:  "1000001", "1001111", "1010101"
Output: "not possible"
*/

#include <cctype>
#include <iostream>
#include <stdexcept>
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

bool is_matrix_path_connected(vector<vector<bool>>& matrix,
                              const size_t x,
                              const size_t y,
                              const size_t row_size,
                              const size_t col_size) {
  if ((x == (row_size - 1)) && (y == (col_size - 1)))
    return true;

  matrix[x][y] = false;

  // N direction
  if ((x > 0) && matrix[x - 1][y]) {
    if (is_matrix_path_connected(matrix, x - 1, y, row_size, col_size)) {
      matrix[x][y] = true;
      return true;
    }
  }

  // E direction
  if ((y < (col_size - 1)) && matrix[x][y + 1]) {
    if (is_matrix_path_connected(matrix, x, y + 1, row_size, col_size)) {
      matrix[x][y] = true;
      return true;
    }
  }

  // S direction
  if ((x < (row_size - 1)) && matrix[x + 1][y]) {
    if (is_matrix_path_connected(matrix, x + 1, y, row_size, col_size)) {
      matrix[x][y] = true;
      return true;
    }
  }

  // W direction
  if ((y > 0) && matrix[x][y - 1]) {
    if (is_matrix_path_connected(matrix, x, y - 1, row_size, col_size)) {
      matrix[x][y] = true;
      return true;
    }
  }

  matrix[x][y] = true;

  return false;
}

size_t find_connected_paths_in_matrix(vector<vector<bool>>& matrix,
                                      const size_t row_size,
                                      const size_t col_size) {
  size_t count{};

  for (size_t i{}; i != row_size; i++) {
    for (size_t j{}; j != col_size; j++) {
      // matrix[0][0] and matrix[row_size - 1][col_size - 1] cells should
      // already be set to true for a connected path to exist between them

      if (!matrix[i][j]) {
        matrix[i][j] = true;

        if (is_matrix_path_connected(matrix, 0, 0, row_size, col_size))
          count++;

        matrix[i][j] = false;
      }
    }
  }

  return count;
}

string MatrixPath(string* str_arr, const size_t str_arr_size) {
  if (!str_arr || str_arr_size < 1)
    return "not possible";

  vector<vector<bool>> matrix(str_arr_size, vector<bool>{});

  const size_t row_size{str_arr_size};
  const size_t col_size{str_arr[0].length()};

  for (size_t i{}; i != row_size; i++) {
    str_arr[i] = trim(str_arr[i]);

    if (col_size != str_arr[i].length())
      throw range_error("Column widths of specified matrix must be equal!");

    matrix[i].resize(str_arr[i].length());

    for (size_t j{}; j != str_arr[i].length(); j++)
      matrix[i][j] = ('0' != str_arr[i][j]);
  }

  if (!matrix[0][0] || !matrix[row_size - 1][col_size - 1])
    throw runtime_error(
        "There can never exist a connected path in specified matrix if its top "
        "leftmost (0,0) and/or rightmost (row_size - 1, col_size - 1) "
        "cells have false values!");

  if (is_matrix_path_connected(matrix, 0, 0, row_size, col_size))
    return "true";

  const size_t possible_connections_count{
      find_connected_paths_in_matrix(matrix, row_size, col_size)};

  if (!possible_connections_count)
    return "not possible";

  return to_string(possible_connections_count);
}

int main() {
  // string A[] = gets(stdin);
  // cout << MatrixPath(A, sizeof(A)/sizeof(*A));
  string B[] = {"11100", "10011", "10101", "10011"};
  cout << MatrixPath(B, sizeof(B) / sizeof(*B)) << '\n';  // expected output: 2
  string C[] = {"10000", "11011", "10101", "11001"};
  cout << MatrixPath(C, sizeof(C) / sizeof(*C)) << '\n';  // expected output: 1
  string D[] = {"1000001", "1001111", "1010101"};
  cout << MatrixPath(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "not possible"

  return 0;
}
