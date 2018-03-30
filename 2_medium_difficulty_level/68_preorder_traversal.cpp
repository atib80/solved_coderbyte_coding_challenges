/*
Coderbyte coding challenge: Preorder Traversal
(iterative solution implemented by using STL queue and stack)

Using the C++ language, have the function PreorderTraversal(strArr) take the
array of strings stored in strArr, which will represent a binary tree with
integer values in a format similar to how a binary heap is implemented with NULL
nodes at any level represented with a #. Your goal is to return the pre-order
traversal of the tree with the elements separated by a space. For example: if
strArr is ["5", "2", "6", "1", "9", "#", "8", "#", "#", "#", "#", "4", "#"] then
this tree looks like the following tree:

For the input above, your program should return the string 5 2 1 9 6 8 4 because
that is the pre-order traversal of the tree. Sample Test Cases

Input:  {"4", "1", "5", "2", "#", "#", "#"}
Output: "4 1 2 5"

Input:  {"2", "6", "#"}
Output: "2 6"
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
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

string print_out_btree_contents_using_preorder_traversal(
    const vector<string>& binary_tree) {
  queue<size_t> q({0});
  stack<size_t> s{};
  ostringstream oss{};

  while (!q.empty()) {
    size_t index{q.front()};
    q.pop();

    if (index >= binary_tree.size() || "#" == binary_tree[index]) {
      if (!s.empty()) {
        q.emplace(s.top());
        s.pop();
      }
      continue;
    }

    oss << binary_tree[index] << ' ';

    index *= 2;
    q.emplace(index + 1);
    s.emplace(index + 2);
  }

  string output{oss.str()};
  output.erase(--end(output));

  return output;
}

string PreorderTraversal(string* str_arr, const size_t str_arr_size) {
  vector<string> items(str_arr, str_arr + str_arr_size);

  if (static_cast<size_t>(log2(str_arr_size + 1)) !=
      static_cast<size_t>(log2(str_arr_size)) + 1) {
    for (size_t i{}; i < (1u << static_cast<size_t>(log2(str_arr_size))) - 1;
         i++) {
      if ("#" == items[i])
        items.insert(begin(items) + 2 * i + 1, {"#", "#"});
    }
  }

  return print_out_btree_contents_using_preorder_traversal(items);
}

int main() {
  // string A[] = gets(stdin);
  // cout << PreorderTraversal(A, sizeof(A)/sizeof(*A));
  string B[] = {"5", "2", "6", "1", "9", "#", "8",
                "#", "#", "#", "#", "4", "#"};
  cout << '"' << PreorderTraversal(B, sizeof(B) / sizeof(*B)) << '"'
       << '\n';  // expected output: "5 2 1 9 6 8 4"
  string C[] = {"4", "1", "5", "2", "#", "#", "#"};
  cout << '"' << PreorderTraversal(C, sizeof(C) / sizeof(*C)) << '"'
       << '\n';  // expected output: "4 1 2 5"
  string D[] = {"2", "6", "#"};
  cout << '"' << PreorderTraversal(D, sizeof(D) / sizeof(*D)) << '"'
       << '\n';  // expected output: "2 6"
  string E[] = {"5"};
  cout << '"' << PreorderTraversal(E, sizeof(E) / sizeof(*E)) << '"'
       << '\n';  // expected output: "5"

  return 0;
}
