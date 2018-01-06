/*
Coderbyte coding challenge: Simple Mode

Using the C++ language, have the function SimpleMode(arr) take the array of numbers stored in arr and return the number that appears most frequently (the mode). 
For example: if arr contains [10, 4, 5, 2, 4] the output should be 4. 
If there is more than one mode return the one that appeared in the array first (ie. [5, 10, 10, 6, 5] should return 5 because it appeared first). 
If there is no mode return -1. The array will not be empty.

Sample test cases:

Input:  5,5,2,2,1
Output: 5

Input:  3,4,1,6,10
Output: -1
*/

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

int SimpleMode(const int* arr, const size_t arr_size) {
  
  vector<pair<int, int>> mode_freq{};

  set<int> modes{};

  for (size_t i{}; i != arr_size; i++) {

    if (modes.find(arr[i]) != end(modes)) continue;

    const int mode_count = count(arr, arr + arr_size, arr[i]);

    mode_freq.emplace_back(make_pair(arr[i], mode_count));

  }

  stable_sort(begin(mode_freq), end(mode_freq), [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return (lhs.second > rhs.second);
  });

  if (mode_freq[0].second > 1) return mode_freq[0].first;

  return -1;             
}

int main() { 
   
  // const int A[] = gets(stdin);
  // cout << SimpleMode(A, sizeof(A)/sizeof(*A));
  const int B[] = {10, 4, 5, 2, 4};
  cout << SimpleMode(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 4
  const int C[] = {5, 10, 10, 6, 5};
  cout << SimpleMode(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 5
  const int D[] = {5,5,2,2,1};
  cout << SimpleMode(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 5
  const int E[] = {3,4,1,6,10};
  cout << SimpleMode(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: -1
  return 0;
}
