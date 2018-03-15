/*
Coderbyte coding challenge: Symmetric Tree

Using the C++ language, have the function SymmetricTree(strArr) take the array
of strings stored in strArr, which will represent a binary tree, and determine
if the tree is symmetric (a mirror image of itself). The array will be
implemented similar to how a binary heap is implemented, except the tree may not
be complete and NULL nodes on any level of the tree will be represented with a
#. For example: if strArr is ["1", "2", "2", "3", "#", "#", "3"] then this tree
looks like the following:

     [1]
  [2]   [2]
[3][#] [#][3]

For the input above, your program should return the string true because the
binary tree is symmetric.

Sample test cases:

Input:  "4", "3", "4"
Output: "false"

Input:  "10", "2", "2", "#", "1", "1", "#"
Output: "true"
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

string SymmetricTree_v1(const string* str_arr, const size_t str_arr_size) {
  for (size_t i{1}; i < str_arr_size; i = 2 * i + 1) {
    for (size_t j{i}, k{2 * i}; j < k; j++, k--) {
      if (str_arr[j] != str_arr[k])
        return "false";
    }
  }

  return "true";
}

string SymmetricTree_v2(const string* str_arr, const size_t str_arr_size) {
  size_t current_level{1};

  while (current_level < str_arr_size) {
    queue<string> q{};
    stack<string> s{};

    for (size_t i{current_level}; i < min(2 * current_level + 1, str_arr_size);
         i++) {
      q.emplace(str_arr[i]);
      s.emplace(str_arr[i]);
    }

    while (!q.empty() && !s.empty()) {
      if (q.front() != s.top())
        return "false";
      q.pop();
      s.pop();
    }

    current_level = 2 * current_level + 1;
  }

  return "true";
}

int main() {
  // const string A[] = gets(stdin);
  // cout << SymmetricTree_v2(A, sizeof(A)/sizeof(*A));
  const string B[] = {"1", "2", "2", "3", "#", "#", "3"};
  cout << SymmetricTree_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "true"
  const string C[] = {"10", "2", "2", "#", "1", "1", "#"};
  cout << SymmetricTree_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "true"
  const string D[] = {"4", "3", "4"};
  cout << SymmetricTree_v2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "false"

  return 0;
}
