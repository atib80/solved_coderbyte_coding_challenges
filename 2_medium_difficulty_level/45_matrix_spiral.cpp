/*
Coderbyte coding challenge: Matrix Spiral

Using the C++ language, have the function MatrixSpiral(strArr) read the array of
strings stored in strArr which will represent a 2D N matrix, and your program
should return the elements after printing them in a clockwise, spiral order. You
should return the newly formed list of elements as a string with the numbers
separated by commas. For example: if strArr is "[1, 2, 3]", "[4, 5, 6]", "[7, 8,
9]" then this looks like the following 2D matrix:

1 2 3
4 5 6
7 8 9

So your program should return the elements of this matrix in a clockwise, spiral
order which is: 1,2,3,6,9,8,7,4,5

Sample test cases:

Input:  "[1, 2]", "[10, 14]"
Output: "1,2,14,10"

Input: "[4, 5, 6, 5]", "[1, 1, 2, 2]", "[5, 4, 2, 9]"
Output: "4,5,6,5,2,9,2,4,5,1,1,2"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
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

string MatrixSpiral(string* str_arr, const size_t str_arr_size) {
  if (!str_arr_size || !str_arr)
    return string{};

  ostringstream oss{};

  if (1 == str_arr_size) {
    *str_arr = trim(*str_arr);
    str_arr->erase(begin(*str_arr));
    str_arr->erase(--end(*str_arr));

    vector<string> elements_str{split(*str_arr, ", ")};

    for (size_t i{}; i < elements_str.size() - 1; i++)
      oss << elements_str[i] << ',';

    oss << elements_str[elements_str.size() - 1];

    return oss.str();
  }

  vector<vector<int>> matrix(str_arr_size, vector<int>{});

  size_t prev_column_dim{string::npos};

  for (size_t i{}; i < str_arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);
    str_arr[i].erase(begin(str_arr[i]));
    str_arr[i].erase(--end(str_arr[i]));

    vector<string> elements_str{split(str_arr[i], ", ")};

    // we check if the separate rows of the matix have differing column sizes
    if (string::npos == prev_column_dim)
      prev_column_dim = elements_str.size();
    else if (elements_str.size() != prev_column_dim)
      return "not possible";

    matrix[i].resize(elements_str.size());

    for (size_t j{}; j < elements_str.size(); j++)
      matrix[i][j] = stoi(elements_str[j]);
  }

  int min_x{}, max_x{static_cast<int>(str_arr_size - 1)};
  int min_y{}, max_y{static_cast<int>(matrix[0].size() - 1)};

  const size_t max_cells{str_arr_size * matrix[0].size()};

  // starting point is the upper-left corner of 'matrix' (min_x, min_y)
  int x{}, y{};

  size_t cells_visited{};

  while (true) {
    while (y <= max_y && cells_visited < max_cells) {
      oss << matrix[x][y] << ',';
      cells_visited++;
      y++;
    }

    if (cells_visited >= max_cells)
      break;

    min_x++;  // we increase min_x by 1 so that we don't accidentally wind up
              // visiting the previously visited top row again
    x = min_x;
    y = max_y;

    while (x <= max_x && cells_visited < max_cells) {
      oss << matrix[x][y] << ',';
      cells_visited++;
      x++;
    }

    if (cells_visited >= max_cells)
      break;

    max_y--;  // we decrease max_y by 1 so that we don't accidentally wind up
              // visiting the previously visited right column again
    y = max_y;
    x = max_x;

    while (y >= min_y && cells_visited < max_cells) {
      oss << matrix[x][y] << ',';
      cells_visited++;
      y--;
    }

    if (cells_visited >= max_cells)
      break;

    max_x--;  // we decrease max_x by 1 so that we don't accidentally wind up
              // visiting the previously visited bottom row again
    x = max_x;
    y = min_y;

    while (x >= min_x && cells_visited < max_cells) {
      oss << matrix[x][y] << ',';
      cells_visited++;
      x--;
    }

    if (cells_visited >= max_cells)
      break;

    min_y++;  // we increase min_y by 1 so that we don't accidentally wind up
              // visiting the previously visited left column again
    y = min_y;
    x = min_x;
  }

  string result{oss.str()};
  result.erase(result.length() - 1, 1);
  return result;
}

int main() {
  // string A[] = gets(stdin);
  // cout << MatrixSpiral(A, sizeof(A)/sizeof(*A));
  string B[] = {"[1, 2, 3]", "[4, 5, 6]", "[7, 8, 9]"};
  cout << MatrixSpiral(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "1,2,3,6,9,8,7,4,5"
  string C[] = {"[1, 2]", "[10, 14]"};
  cout << MatrixSpiral(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "1,2,14,10"
  string D[] = {"[4, 5, 6, 5]", "[1, 1, 2, 2]", "[5, 4, 2, 9]"};
  cout << MatrixSpiral(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "4,5,6,5,2,9,2,4,5,1,1,2"

  return 0;
}
