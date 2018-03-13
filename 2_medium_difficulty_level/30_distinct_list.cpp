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

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int DistinctList(const int* arr, const size_t arr_size) {
  int duplicate_count{};

  unordered_set<int> visited_arr_elements{};

  for (size_t i{}; i < arr_size; i++) {
    if (visited_arr_elements.find(arr[i]) != end(visited_arr_elements)) {
      duplicate_count++;
      continue;
    }

    visited_arr_elements.insert(arr[i]);
  }

  return duplicate_count;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << DistinctList(A, sizeof(A)/sizeof(*A));
  const int B[] = {1, 2, 2, 2, 3};
  cout << DistinctList(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 2
  const int C[] = {0, -2, -2, 5, 5, 5};
  cout << DistinctList(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 3
  const int D[] = {100, 2, 101, 4};
  cout << DistinctList(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 0

  return 0;
}
