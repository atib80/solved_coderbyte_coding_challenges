/*
Coderbyte coding challenge: Longest Matrix Path
(recursive solution)

Using the C++ language, have the function LongestMatrixPath(strArr) take the
array of strings stored in strArr, which will be an NxM matrix of positive
single-digit integers, and find the longest increasing path composed of distinct
integers. When moving through the matrix, you can only go up, down, left, and
right. For example: if strArr is ["345", "326", "221"], then this looks like the
following matrix:

3 4 5
3 2 6
2 2 1

For the input above, the longest increasing path goes from: 3 -> 4 -> 5 -> 6.
Your program should return the number of connections in the longest path, so
therefore for this input your program should return 3. There may not necessarily
always be a longest path within the matrix.

Sample test cases:

Input:  "12256", "56219", "43215"
Output: 5

Input:  "67", "21", "45"
Output: 3
*/

#include <algorithm>
#include <cctype>
#include <iostream>
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

void find_max_path_distance(const vector<vector<char>>& matrix,
                            const size_t x,
                            const size_t y,
                            const char max_value,
                            size_t& longest_increasing_path,
                            const size_t distance = 0) {
  if (max_value - matrix[x][y] + distance <= longest_increasing_path)
    return;

  if (x > 0 && matrix[x][y] < matrix[x - 1][y]) {
    find_max_path_distance(matrix, x - 1, y, max_value, longest_increasing_path,
                           distance + 1);
  }

  if (x < matrix.size() - 1 && matrix[x][y] < matrix[x + 1][y]) {
    find_max_path_distance(matrix, x + 1, y, max_value, longest_increasing_path,
                           distance + 1);
  }

  if (y > 0 && matrix[x][y] < matrix[x][y - 1]) {
    find_max_path_distance(matrix, x, y - 1, max_value, longest_increasing_path,
                           distance + 1);
  }

  if (y < matrix[x].size() - 1 && matrix[x][y] < matrix[x][y + 1]) {
    find_max_path_distance(matrix, x, y + 1, max_value, longest_increasing_path,
                           distance + 1);
  }

  if (distance > longest_increasing_path)
    longest_increasing_path = distance;
}

string LongestMatrixPath(string* str_arr, const size_t str_arr_size) {
  const size_t row_size{str_arr_size};
  const size_t column_size{str_arr[0].length()};

  for (size_t i{}; i < row_size; i++)
    str_arr[i] = trim(str_arr[i]);

  vector<vector<char>> matrix(row_size, vector<char>(column_size));

  char max_value{matrix[0][0]};

  for (size_t i{}; i < row_size; i++) {
    for (size_t j{}; j < column_size; j++) {
      matrix[i][j] = str_arr[i][j];
      if (matrix[i][j] > max_value)
        max_value = matrix[i][j];
    }
  }

  size_t longest_increasing_path{};

  for (size_t i{}; i < row_size; i++) {
    for (size_t j{}; j < column_size; j++) {
      find_max_path_distance(matrix, i, j, max_value, longest_increasing_path);
    }
  }

  return to_string(longest_increasing_path);
}

int main() {
  // string A[] = gets(stdin);
  // cout << LongestMatrixPath(A, sizeof(A)/sizeof(*A));
  string B[] = {"345", "326", "221"};
  cout << LongestMatrixPath(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 3
  string C[] = {"12256", "56219", "43215"};
  cout << LongestMatrixPath(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 5
  string D[] = {"67", "21", "45"};
  cout << LongestMatrixPath(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 3
  string E[] = {"111", "111", "111"};
  cout << LongestMatrixPath(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 0

  return 0;
}
