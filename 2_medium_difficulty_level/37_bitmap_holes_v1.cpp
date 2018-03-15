/*
Coderbyte coding challenge: Bitmap Holes
(iterative solution using std::queue<T>)

Using the C++ language, have the function BitmapHoles(strArr) take the array of
strings stored in strArr, which will be a 2D matrix of 0 and 1's, and determine
how many holes, or contiguous regions of 0's, exist in the matrix. A contiguous
region is one where there is a connected group of 0's going in one or more of
four directions: up, down, left, or right. For example: if strArr is ["10111",
"10101", "11101", "11111"], then this looks like the following matrix:

1 0 0 1 1
1 0 1 0 1
0 0 1 0 1
1 1 1 1 1

For the input above, your program should return 2 because there are two separate
contiguous regions of 0's, which create "holes" in the matrix. You can assume
the input will not be empty.

Sample test cases:

Input:  "01111", "01101", "00011", "11110"
Output: 3

Input:  "1011", "0010"
Output: 2
*/

#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void find_and_mark_neighboring_holes(const size_t origin_x,
                                     const size_t origin_y,
                                     vector<vector<int>>& bitmap,
                                     const int mark_value = -1) {
  queue<pair<size_t, size_t>> q{{make_pair(origin_x, origin_y)}};

  while (!q.empty()) {
    const size_t x{q.front().first};
    const size_t y{q.front().second};

    q.pop();

    bitmap[x][y] = mark_value;

    if (x > 0 && !bitmap[x - 1][y])
      q.emplace(make_pair(x - 1, y));

    if (x < bitmap.size() - 1 && !bitmap[x + 1][y])
      q.emplace(make_pair(x + 1, y));

    if (y > 0 && !bitmap[x][y - 1])
      q.emplace(make_pair(x, y - 1));

    if (y < bitmap[x].size() - 1 && !bitmap[x][y + 1])
      q.emplace(make_pair(x, y + 1));
  }
}

void print_bitmap_contents(const vector<vector<int>>& bitmap,
                           const size_t row_size,
                           const size_t column_size) {
  printf("\n");

  for (size_t i{}; i < column_size; i++)
    printf("---");

  for (size_t i{}; i < row_size; i++) {
    printf("\n|");

    for (size_t j{}; j < column_size; j++) {
      printf("%2d|", bitmap[i][j]);
    }
  }

  printf("\n");

  for (size_t i{}; i < column_size; i++)
    printf("---");

  printf("\n");
}

string BitmapHoles(const string* str_arr, const size_t row_size) {
  const size_t column_size{str_arr[0].length()};

  vector<vector<int>> bitmap(row_size, vector<int>{});

  for (size_t i{}; i < row_size; i++)
    bitmap[i].resize(str_arr[i].length());

  for (size_t i{}; i < row_size; i++) {
    for (size_t j{}; j < str_arr[i].length(); j++) {
      if ('1' == str_arr[i][j])
        bitmap[i][j] = 1;
    }
  }

  // print_bitmap_contents(bitmap, row_size, column_size);

  int current_hole_id{-1};
  size_t holes_count{};

  for (size_t i{}; i < row_size; i++) {
    for (size_t j{}; j < column_size; j++) {
      if (!bitmap[i][j]) {
        find_and_mark_neighboring_holes(i, j, bitmap, current_hole_id);
        holes_count++;
        current_hole_id--;
      }
    }
  }

  // print_bitmap_contents(bitmap, row_size, column_size);

  return to_string(holes_count);
}

int main() {
  // const string A[] = gets(stdin);
  // cout << BitmapHoles(A, sizeof(A)/sizeof(*A));
  const string B[] = {"10111", "10101", "11101", "11111"};
  cout << BitmapHoles(B, sizeof(B) / sizeof(*B)) << '\n';  // expected output: 2
  const string C[] = {"01111", "01101", "00011", "11110"};
  cout << BitmapHoles(C, sizeof(C) / sizeof(*C)) << '\n';  // expected output: 3
  const string D[] = {"1011", "0010"};
  cout << BitmapHoles(D, sizeof(D) / sizeof(*D)) << '\n';  // expected output: 2
  return 0;
}
