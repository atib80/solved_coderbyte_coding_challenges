/*
Coderbyte coding challenge: Maximal Rectangle

Using the C++ language, have the function MaximalRectangle(strArr) take the
strArr parameter being passed which will be a 2D matrix of 0 and 1's, and
determine the area of the largest rectangular submatrix that contains all 1's.
For example: if strArr is ["10100", "10111", "11111", "10010"] then this looks
like the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

For the input above, you can see the bolded 1's create the largest rectangular
submatrix of size 2x3, so your program should return the area which is 6. You
can assume the input will not be empty.

Sample test cases:

Input:  "1011", "0011", "0111", "1111"
Output: 8

Input:  "101", "111", "001"
Output: 3
*/

#include <algorithm>
#include <cctype>
#include <iostream>
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

bool find_maximal_rectangle_in_matrix(const vector<vector<int>>& matrix,
                                      const size_t width,
                                      const size_t height) {
  const size_t matrix_height{matrix.size()};
  const size_t matrix_width{matrix[0].size()};

  for (size_t y{}; y + height <= matrix_height; y++) {
    for (size_t x{}; x + width <= matrix_width; x++) {
      bool is_rectangle_found{true};

      for (size_t i{y}; i < y + height; i++) {
        for (size_t j{x}; j < x + width; j++) {
          if (!matrix[i][j]) {
            is_rectangle_found = false;
            break;
          }
        }

        if (!is_rectangle_found)
          break;
      }

      if (is_rectangle_found)
        return true;
    }
  }

  return false;
}

bool check_if_matrix_has_one_elements(const vector<vector<int>>& matrix) {
  for (const auto& row : matrix) {
    if (any_of(begin(row), end(row),
               [](const int value) { return (1 == value); }))
      return true;
  }

  return false;
}

vector<vector<int>> create_matrix_from_input_string_array(
    string* str_arr,
    const size_t str_arr_size) {
  for (size_t i{}; i < str_arr_size; i++)
    str_arr[i] = trim(str_arr[i]);

  const size_t width{str_arr[0].length()};
  const size_t height{str_arr_size};

  vector<vector<int>> matrix(height, vector<int>(width));

  for (size_t i{}; i < height; i++) {
    for (size_t j{}; j < width; j++)
      matrix[i][j] = ('0' != str_arr[i][j] ? 1 : 0);
  }

  return matrix;
}

string MaximalRectangle(string* str_arr, const size_t str_arr_size) {
  const auto matrix =
      create_matrix_from_input_string_array(str_arr, str_arr_size);

  if (matrix.empty())
    return "not possible";

  if (!check_if_matrix_has_one_elements(matrix))
    return "0";

  size_t width{matrix[0].size()};
  size_t height{matrix.size()};
  size_t max_area{1};

  vector<pair<size_t, size_t>> width_height_pairs{};

  for (size_t i{width}; i >= 1; i--) {
    for (size_t j{height}; j >= 1; j--)
      width_height_pairs.emplace_back(make_pair(i, j));
  }

  for (size_t i{}; i < width_height_pairs.size() - 1; i++) {
    width = width_height_pairs[i].first;
    height = width_height_pairs[i].second;

    if (find_maximal_rectangle_in_matrix(matrix, width, height)) {
      if ((width * height) > max_area)
        max_area = width * height;
    }
  }

  return to_string(max_area);
}

int main() {
  // string A[] = gets(stdin);
  // cout << MaximalRectangle(A, sizeof(A)/sizeof(*A));
  string B[] = {"10100", "10111", "11111", "10010"};
  cout << MaximalRectangle(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 6
  string C[] = {"1011", "0011", "0111", "1111"};
  cout << MaximalRectangle(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 8
  string D[] = {"101", "111", "001"};
  cout << MaximalRectangle(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 3

  return 0;
}
