/*
Coderbyte coding challenge: Triangle Row

Using the C++ language, have the function TriangleRow(num) take num which will
be a positive integer representing some row from Pascal's triangle. Pascal's
triangle starts with a [1] at the 0th row of the triangle. Then the first row is
[1, 1] and the second row is [1, 2, 1]. The next row begins with 1 and ends with
1, and the inside of the row is determined by adding the k-1 and kth elements
from the previous row. The next row in the triangle would then be [1, 3, 3, 1],
and so on. The input will be some positive integer and your goal is to return
the sum of that row. For example: if num is 4 then your program should return
the sum of 1 + 4 + 6 + 4 + 1 which is 16.

1.       1
2.      1 1
3.     1 2 1
4.    1 3 3 1
5.   1 4 6 4 1
6.  1 5 10 10 5 1
7. 1 6 15 20 15 6 1

Sample test cases:

Input:  1
Output: 2

Input:  2
Output: 4
*/

#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int TriangleRow(int num) {
  num = abs(num);

  if (num <= 2) {
    switch (num) {
      case 0:
        return 1;

      case 1:
        return 2;

      case 2:
        return 4;
    }
  }

  vector<int> prev_pascal_triangle{1, 2, 1};

  vector<int> next_pascal_triangle{1};

  for (int i{3}; i <= num; i++) {
    for (size_t j{}; j < prev_pascal_triangle.size() - 1; j++)
      next_pascal_triangle.emplace_back(prev_pascal_triangle[j] +
                                        prev_pascal_triangle[j + 1]);

    next_pascal_triangle.emplace_back(1);

    prev_pascal_triangle = {1};  // prev_pascal_triangle.assign({1});

    swap(prev_pascal_triangle, next_pascal_triangle);
  }

  return accumulate(begin(prev_pascal_triangle), end(prev_pascal_triangle), 0);
}

int main() {
  // cout << TriangleRow(gets(stdin));
  cout << TriangleRow(4) << '\n';  // expected output: 16
  cout << TriangleRow(1) << '\n';  // expected output: 2
  cout << TriangleRow(2) << '\n';  // expected output: 4
  cout << TriangleRow(3) << '\n';  // expected output: 8

  return 0;
}
