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
#include <vector>

using namespace std;

vector<vector<int>> generate_pascal_triangle_rows(
    const size_t pascal_row_number) {
  vector<vector<int>> pascal_triangle{};

  if (!pascal_row_number) {
    pascal_triangle.emplace_back(vector<int>{1});
    return pascal_triangle;
  }

  if (1 == pascal_row_number) {
    pascal_triangle.emplace_back(vector<int>{1});
    pascal_triangle.emplace_back(vector<int>{1, 1});
    return pascal_triangle;
  }

  if (2 == pascal_row_number) {
    pascal_triangle.emplace_back(vector<int>{1});
    pascal_triangle.emplace_back(vector<int>{1, 1});
    pascal_triangle.emplace_back(vector<int>{1, 2, 1});
    return pascal_triangle;
  }

  pascal_triangle.emplace_back(vector<int>{1});
  pascal_triangle.emplace_back(vector<int>{1, 1});
  pascal_triangle.emplace_back(vector<int>{1, 2, 1});

  vector<int> prev_pascal_triangle_numbers{1, 2, 1};
  vector<int> next_pascal_triangle_numbers{};

  for (size_t i{3}; i <= pascal_row_number; i++) {
    next_pascal_triangle_numbers.emplace_back(1);

    for (size_t j{}; j != prev_pascal_triangle_numbers.size() - 1; j++)
      next_pascal_triangle_numbers.emplace_back(
          prev_pascal_triangle_numbers[j] +
          prev_pascal_triangle_numbers[j + 1]);

    next_pascal_triangle_numbers.emplace_back(1);

    pascal_triangle.emplace_back(next_pascal_triangle_numbers);

    prev_pascal_triangle_numbers.clear();

    swap(prev_pascal_triangle_numbers, next_pascal_triangle_numbers);
  }

  return pascal_triangle;
}

int PascalsTriangle(const int* arr, const size_t arr_size) {
  vector<int> prev_pascal_triangle_numbers{1, 2, 1};
  vector<int> next_pascal_triangle_numbers{};

  size_t iter_count{};

  while (iter_count < 1000) {
    next_pascal_triangle_numbers.emplace_back(1);

    for (size_t i{}; i != prev_pascal_triangle_numbers.size() - 1; i++)
      next_pascal_triangle_numbers.emplace_back(
          prev_pascal_triangle_numbers[i] +
          prev_pascal_triangle_numbers[i + 1]);

    next_pascal_triangle_numbers.emplace_back(1);

    if (arr_size <= next_pascal_triangle_numbers.size()) {
      bool is_found_partial_match{true};

      for (size_t i{}; i < arr_size; i++) {
        if (arr[i] != next_pascal_triangle_numbers[i]) {
          is_found_partial_match = false;
          break;
        }
      }

      if (is_found_partial_match) {
        if (arr_size == next_pascal_triangle_numbers.size())
          return -1;

        return next_pascal_triangle_numbers[arr_size];
      }
    }

    prev_pascal_triangle_numbers.clear();

    swap(prev_pascal_triangle_numbers, next_pascal_triangle_numbers);

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
