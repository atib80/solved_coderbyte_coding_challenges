/*
Coderbyte coding challenge: Tree Constructor

Using the C++ language, have the function TreeConstructor(strArr) take the array
of strings stored in strArr, which will contain pairs of integers in the
following format: (i1,i2), where i1 represents a child node in a tree and the
second integer i2 signifies that it is the parent of i1. For example: if strArr
is ["(1,2)", "(2,4)", "(7,2)"], then this forms the following tree:

     [4]
   [2]
 [1][7]

which you can see forms a proper binary tree.
Your program should, in this case, return the string true because a valid binary
tree can be formed. If a proper binary tree cannot be formed with the integer
pairs, then return the string false. All of the integers within the tree will be
unique, which means there can only be one node in the tree with the given
integer value.

Sample test cases:

Input:  "(1,2)", "(2,4)", "(5,7)", "(7,2)", "(9,5)"
Output: "true"

Input:  "(1,2)", "(3,2)", "(2,12)", "(5,2)"
Output: "false"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

string TreeConstructor(string* str_arr, const size_t str_arr_size) {
  vector<pair<int, int>> child_parent_value_pairs{};

  for (size_t i{}; i < str_arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);
    str_arr[i].erase(begin(str_arr[i]));
    str_arr[i].erase(--end(str_arr[i]));
    const size_t comma_pos{str_arr[i].find(',')};
    if (string::npos == comma_pos)
      return "not possible";
    const int child_number{stoi(str_arr[i].substr(0, comma_pos))};
    const int parent_number{stoi(str_arr[i].substr(comma_pos + 1))};
    child_parent_value_pairs.emplace_back(
        make_pair(child_number, parent_number));
  }

  if (1 == child_parent_value_pairs.size() &&
      child_parent_value_pairs.front().first <
          child_parent_value_pairs.front().second)
    return "true";

  unordered_set<int> child_value_count{};
  unordered_map<int, size_t> parent_value_count{};
  unordered_map<int, vector<int>> parent_children_values{};

  sort(begin(child_parent_value_pairs), end(child_parent_value_pairs),
       [](const pair<int, int>& lp, const pair<int, int>& rp) {
         return lp.second < rp.second;
       });

  for (const auto& cp : child_parent_value_pairs) {
    if (child_value_count.count(cp.first))
      return "false";

    child_value_count.insert(cp.first);

    parent_value_count[cp.second]++;

    if (parent_value_count[cp.second] > 2)
      return "false";

    if (parent_children_values.find(cp.second) == end(parent_children_values))
      parent_children_values.insert(
          make_pair(cp.second, vector<int>{cp.first}));
    else
      parent_children_values[cp.second].emplace_back(cp.first);
  }

  for (const auto& cp_values : parent_children_values) {
    if (cp_values.second.size() > 2)
      return "false";

    if (2 == cp_values.second.size()) {
      if ((cp_values.second[0] < cp_values.first &&
           cp_values.second[1] < cp_values.first) ||
          (cp_values.second[0] > cp_values.first &&
           cp_values.second[1] > cp_values.first))
        return "false";
    }
  }

  return "true";
}

int main() {
  // string A[] = gets(stdin);
  // cout << TreeConstructor(A, sizeof(A)/sizeof(*A));
  string B[] = {"(1,2)", "(2,4)", "(7,2)"};
  cout << TreeConstructor(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "true"
  string C[] = {"(1,2)", "(2,4)", "(5,7)", "(7,2)", "(9,5)"};
  cout << TreeConstructor(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "true"
  string D[] = {"(1,2)", "(3,2)", "(2,12)", "(5,2)"};
  cout << TreeConstructor(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "false"
  string E[] = {"(10,20)"};
  cout << TreeConstructor(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "true"

  return 0;
}
