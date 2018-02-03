/*
Coderbyte coding challenge: Pascals Triangle

Using the C++ language, have the function PascalsTriangle(arr) take arr which
will be a partial row from Pascal's triangle. Pascal's triangle starts with a
[1] at the first row of the triangle. Then the second row is [1,1] and the third
row is [1,2,1]. The next row begins with 1 and ends with 1, and the inside of
the row is determined by adding the k-1 and kth elements from the previous row.
The next row in the triangle would then be [1,3,3,1], and so on.
The input, arr will be some almost completed row from the triangle, for example
[1,4,6,4] and your program should return the next element in that row. In this
example your program should return 1. Another example: if arr is [1,5,10] your
program should return 10. If the whole row is entered as input and there is no
next number, your program should return -1. The input array will contain at
least 2 elements and array inputs such as [1] and [1,1] will not occur as
inputs.

Sample test cases:

Input:  1,3
Output: 3

Input:  1,5,10,10
Output: 5
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<int> generate_next_pascal_triangle_row(
    const pair<bool, int>& reset_state_to_specific_row = pair<bool, int>{false,
                                                                         0}) {
  static int current_row_index{-1};
  static vector<int> current_row{1};

  if (reset_state_to_specific_row.first) {
    current_row_index = reset_state_to_specific_row.second;

    if (!current_row_index) {
      current_row = {1};
      return current_row;
    }

    if (1 == current_row_index) {
      current_row = {1, 1};
      return current_row;
    }

    if (2 == current_row_index) {
      current_row = {1, 2, 1};
      return current_row;
    }

    current_row = {1, 2, 1};

    for (int i{3}; i <= current_row_index; i++) {
      current_row.emplace(begin(current_row), 1);

      for (size_t j{1}; j < current_row.size() - 1; j++) {
        current_row[j] = current_row[j] + current_row[j + 1];
      }
    }

    return current_row;
  }

  current_row_index++;

  if (!current_row_index) {
    return current_row;
  }

  if (1 == current_row_index) {
    current_row = {1, 1};
    return current_row;
  }

  if (2 == current_row_index) {
    current_row = {1, 2, 1};
    return current_row;
  }

  current_row.emplace(begin(current_row), 1);

  for (size_t i{1}, j{1}; i < current_row.size() - 1; i++, j++) {
    current_row[j] = current_row[i] + current_row[i + 1];
  }

  return current_row;
}

vector<vector<int>> generate_pascal_triangle_rows(
    const size_t pascal_row_number) {
  static vector<vector<int>> current_pascal_triangle{1};
  static size_t current_pascal_row_number{};

  if (pascal_row_number == current_pascal_row_number)
    return current_pascal_triangle;

  current_pascal_triangle.clear();
  current_pascal_row_number = pascal_row_number;

  if (!pascal_row_number) {
    current_pascal_triangle.emplace_back(vector<int>{1});
    return current_pascal_triangle;
  }

  if (1 == pascal_row_number) {
    current_pascal_triangle.emplace_back(vector<int>{1});
    current_pascal_triangle.emplace_back(vector<int>{1, 1});
    return current_pascal_triangle;
  }

  if (2 == pascal_row_number) {
    current_pascal_triangle.emplace_back(vector<int>{1});
    current_pascal_triangle.emplace_back(vector<int>{1, 1});
    current_pascal_triangle.emplace_back(vector<int>{1, 2, 1});
    return current_pascal_triangle;
  }

  current_pascal_triangle.emplace_back(vector<int>{1});
  current_pascal_triangle.emplace_back(vector<int>{1, 1});
  current_pascal_triangle.emplace_back(vector<int>{1, 2, 1});

  vector<int> prev_pascal_triangle_numbers{1, 2, 1};
  vector<int> next_pascal_triangle_numbers{};

  for (size_t i{3}; i <= pascal_row_number; i++) {
    next_pascal_triangle_numbers.emplace_back(1);

    for (size_t j{}; j != prev_pascal_triangle_numbers.size() - 1; j++)
      next_pascal_triangle_numbers.emplace_back(
          prev_pascal_triangle_numbers[j] +
          prev_pascal_triangle_numbers[j + 1]);

    next_pascal_triangle_numbers.emplace_back(1);

    current_pascal_triangle.emplace_back(next_pascal_triangle_numbers);

    prev_pascal_triangle_numbers.clear();

    swap(prev_pascal_triangle_numbers, next_pascal_triangle_numbers);
  }

  return current_pascal_triangle;
}

int PascalsTriangle(const int* arr, const size_t arr_size) {
  generate_next_pascal_triangle_row({true, 2});

  size_t iter_count{};

  while (iter_count < 1000) {
    const vector<int> next_pascal_triangle_row{
        generate_next_pascal_triangle_row()};

    if (arr_size <= next_pascal_triangle_row.size()) {
      bool is_found_partial_match{true};

      for (size_t i{}; i < arr_size; i++) {
        if (arr[i] != next_pascal_triangle_row[i]) {
          is_found_partial_match = false;
          break;
        }
      }

      if (is_found_partial_match) {
        if (arr_size == next_pascal_triangle_row.size())
          return -1;

        return next_pascal_triangle_row[arr_size];
      }
    }

    iter_count++;
  }

  return -1;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << PascalsTriangle(A, sizeof(A)/sizeof(*A));
  const int B[] = {1, 4, 6, 4};
  cout << PascalsTriangle(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 1
  const int C[] = {1, 5, 10};
  cout << PascalsTriangle(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 10
  const int D[] = {1, 3};
  cout << PascalsTriangle(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 3
  const int E[] = {1, 5, 10, 10};
  cout << PascalsTriangle(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 5
  const int F[] = {1, 4, 6, 4, 1};
  cout << PascalsTriangle(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: -1

  return 0;
}
