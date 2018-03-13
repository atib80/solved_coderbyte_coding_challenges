/*
Coderbyte coding challenge: Distinct List

Using the C++ language, have the function DistinctList(arr) take the array of
numbers stored in arr and determine the total number of duplicate entries. For
example if the input is [1, 2, 2, 2, 3] then your program should output 2
because there are two duplicates of one of the elements.

Sample test cases:

Input:  0,-2,-2,5,5,5
Output: 3

Input:  100,2,101,4
Output: 0
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int DistinctList_v1(int* arr, const size_t arr_size) {
  unordered_set<int> visited_arr_elements(arr, arr + arr_size);

  return arr_size - visited_arr_elements.size();
}

int DistinctList_v2(int* arr, const size_t arr_size) {
  int* const new_arr_last = unique(arr, arr + arr_size);

  return static_cast<ptrdiff_t>(arr + arr_size - new_arr_last);
}

int main() {
  // const int A[] = gets(stdin);
  // cout << DistinctList_v2(A, sizeof(A)/sizeof(*A));
  int B[] = {1, 2, 2, 2, 3};
  cout << DistinctList_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 2
  int C[] = {0, -2, -2, 5, 5, 5};
  cout << DistinctList_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 3
  int D[] = {100, 2, 101, 4};
  cout << DistinctList_v2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 0

  return 0;
}
