/*
Coderbyte coding challenge: Wave Sorting

Using the C++ language, have the function WaveSorting(arr) take the array of
positive integers stored in arr and return the string true if the numbers can be
arranged in a wave pattern: a1 > a2 < a3 > a4 < a5 > ..., otherwise return the
string false. For example, if arr is: [0, 1, 2, 4, 1, 4], then a possible wave
ordering of the numbers is: [2, 0, 4, 1, 4, 1]. So for this input your program
should return the string true. The input array will always contain at least 2
elements. More examples are given below as sample test cases.

Sample test cases:

Input:  0, 1, 2, 4, 1, 1, 1
Output: "false"

Input:  0, 4, 22, 4, 14, 4, 2
Output: "true"
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using namespace std;

string WaveSorting_v1(int* arr, const size_t arr_size) {
  sort(arr, arr + arr_size);
  unordered_map<int, size_t> number_freq{{arr[0], 1}};
  int last_counted_num{arr[0]};
  size_t balance{1};

  for (size_t i{1}; i < arr_size; ++i) {
    number_freq[arr[i]]++;

    if (0U == balance) {
      last_counted_num = arr[i];
      balance++;

    } else if (last_counted_num == arr[i])
      balance++;
    else
      balance--;
  }

  if (0U == balance)
    return "true";

  return number_freq[last_counted_num] > arr_size / 2 ? "false" : "true";
}

string WaveSorting_v2(int* arr, const size_t arr_size) {
  unordered_set<int> unique_numbers{arr[0]};
  int balance{};
  int sign_factor{1};
  int last_counted_number{arr[0]};

  for (size_t i{1}; i < arr_size; ++i) {
    if (0U == unique_numbers.count(arr[i]))
      unique_numbers.emplace(arr[i]);
    else if (last_counted_number == arr[i])
      balance += sign_factor;
    else {
      sign_factor = -sign_factor;
      balance += sign_factor;
    }

    last_counted_number = arr[i];
  }

  return 0 == balance ? "true" : "false";
}

int main() {
  // int arr[] = gets(stdin);
  // cout << WaveSorting_v2(arr, sizeof(arr)/sizeof(*arr));
  int b[]{0, 1, 2, 4, 1, 4};
  cout << WaveSorting_v2(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: "true"
  int c[]{0, 1, 2, 4, 1, 1, 1};
  cout << WaveSorting_v2(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: "false"
  int d[]{0, 4, 22, 4, 14, 4, 2};
  cout << WaveSorting_v2(d, sizeof(d) / sizeof(*d))
       << '\n';  // expected output: "true"

  return 0;
}
