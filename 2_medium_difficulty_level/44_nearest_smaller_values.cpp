/*
Coderbyte coding challenge: Nearest Smaller Values

Using the C++ language, have the function NearestSmallValues(arr) take the array
of integers stored in arr, and for each element in the list, search all the
previous values for the nearest element that is smaller than the current element
and create a new list from these numbers. If there is no element before a
certain position that is smaller, input a -1. For example: if arr is [5, 2, 8,
3, 9, 12] then the nearest smaller values list is [-1, -1, 2, 2, 3, 9]. The
logic is as follows:

For 5, there is no smaller previous value so the list so far is [-1]. For 2,
there is also no smaller previous value, so the list is now [-1, -1]. For 8, the
nearest smaller value is 2 so the list is now [-1, -1, 2]. For 3, the nearest
smaller value is also 2, so the list is now [-1, -1, 2, 2]. This goes on to
produce the answer above. Your program should take this final list and return
the elements as a string separated by a space: -1 -1 2 2 3 9

Sample test cases:

Input:  5, 3, 1, 9, 7, 3, 4, 1
Output: "-1 -1 -1 1 1 1 3 1"

Input:  2, 4, 5, 1, 7
Output: "-1 2 4 -1 1"
*/

#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;

string NearestSmallerValues(const int* arr, const size_t arr_size) {
  if (!arr || arr_size < 2)
    return "-1";

  ostringstream oss{};

  oss << "-1 ";

  set<int> nearest_lower_values{};

  for (size_t i{1}; i < arr_size; i++) {
    if (arr[i] >= arr[i - 1])
      nearest_lower_values.insert(arr[i - 1]);

    else if (nearest_lower_values.empty()) {
      nearest_lower_values.insert(arr[i]);
      oss << "-1 ";
      continue;
    }

    if (arr[i] < *begin(nearest_lower_values)) {
      nearest_lower_values.clear();
      nearest_lower_values.insert(arr[i]);
      oss << "-1 ";
      continue;
    }

    auto start = begin(nearest_lower_values);
    auto last = end(nearest_lower_values);
    int nearest_neighbor{*start};
    ++start;

    while (start != last && *start <= arr[i]) {
      nearest_neighbor = *start;
      ++start;
    }

    oss << nearest_neighbor << ' ';
  }

  string ret_val{oss.str()};
  ret_val.erase(ret_val.length() - 1, 1);
  return ret_val;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << NearestSmallerValues(A, sizeof(A)/sizeof(*A));
  const int B[] = {5, 2, 8, 3, 9, 12};
  cout << NearestSmallerValues(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "-1, -1, 2, 2, 3, 9"
  const int C[] = {5, 3, 1, 9, 7, 3, 4, 1};
  cout << NearestSmallerValues(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "-1 -1 -1 1 1 1 3 1"
  const int D[] = {2, 4, 5, 1, 7};
  cout << NearestSmallerValues(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "-1 2 4 -1 1"
  const int E[] = {1, 1, 1, 2, 2};
  cout << NearestSmallerValues(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "-1 1 1 1 2"
  const int F[] = {0, 0, 0, 1, 2};
  cout << NearestSmallerValues(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "-1 0 0 0 1"

  return 0;
}
