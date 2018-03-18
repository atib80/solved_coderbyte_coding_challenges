/*
Coderbyte coding challenge: Binary Tree LCA
(iterative solution using queue<node<string*>>)

Using the C++ language, have the function BinaryTreeLCA(strArr) take the array
of strings stored in strArr, which will contain 3 elements: the first element
will be a binary tree with all unique values in a format similar to how a binary
heap is implemented with NULL nodes at any level represented with a #, the
second and third elements will be two different values, and your goal is to find
the lowest common ancestor of these two values. For example: if strArr is ["[12,
5, 9, 6, 2, 0, 8, #, #, 7, 4, #, #, #, #]", "6", "4"] then this tree looks like
the following:

     [12]
  [5]    [9]
[6][2]  [0][8]
  [7][4]


For the input above, your program should return 5 because that is the value of
the node that is the LCA of the two nodes with values 6 and 4. You can assume
the two nodes you are searching for in the tree will exist somewhere in the
tree.

Sample test cases:

Input:  "[5, 2, 6, 1, #, 8, #]", "2", "6"
Output: 5

Input:  "[5, 2, 6, 1, #, 8, 12, #, #, #, #, #, #, 3, #]", "3", "12"
Output: 12
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
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

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.length()};

  if (!source_len)
    return parts;

  if (!needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if ((string::npos != max_count) && (parts.size() == max_count))
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

template <typename T>
struct node {
  T data;
  node<T>* left;
  node<T>* right;
  node<T>* parent;

  node(const T& d,
       node<T>* p = nullptr,
       node<T>* l = nullptr,
       node<T>* r = nullptr)
      : data{d}, parent{p}, left{l}, right{r} {}

  ~node() {
    if (left)
      delete left;
    if (right)
      delete right;
  }
};

bool construct_binary_heap_tree(const vector<string>& data,
                                node<string>* root_node) {
  if (data.empty() || "#" == data[0])
    return false;

  queue<node<string>*> q{{root_node}};

  const size_t data_len{data.size()};
  size_t index{};

  while (!q.empty()) {
    node<string>* parent{q.front()};
    q.pop();

    if (!parent) {
      index++;
      continue;
    }

    index++;

    if (index >= data_len)
      return true;

    if ("#" != data[index]) {
      node<string>* left{new node<string>(data[index], parent)};
      parent->left = left;
      q.emplace(left);

    } else
      q.emplace(nullptr);

    index++;

    if (index >= data_len)
      return true;

    if ("#" != data[index]) {
      node<string>* right{new node<string>(data[index], parent)};
      parent->right = right;
      q.emplace(right);

    } else
      q.emplace(nullptr);
  }

  return true;
}

string find_lca(const node<string>* root, const string& n1, const string& n2) {
  if (!root)
    return "not possible";

  const node<string>*left_lca{}, *right_lca{};

  queue<const node<string>*> q{{root}};

  while (!q.empty()) {
    const node<string>* current{q.front()};
    q.pop();

    if (!left_lca && current->data == n1)
      left_lca = current;
    else if (!right_lca && current->data == n2)
      right_lca = current;

    if (left_lca && right_lca)
      break;

    if (current->left)
      q.emplace(current->left);
    if (current->right)
      q.emplace(current->right);
  }

  if (left_lca && !right_lca)
    return left_lca->data;
  if (!left_lca && right_lca)
    return right_lca->data;

  unordered_set<string> ancestor_node_values{};

  for (const node<string>* tree_node{left_lca}; tree_node;
       tree_node = tree_node->parent) {
    ancestor_node_values.insert(tree_node->data);
  }

  for (const node<string>* tree_node{right_lca}; tree_node;
       tree_node = tree_node->parent) {
    if (ancestor_node_values.find(tree_node->data) != end(ancestor_node_values))
      return tree_node->data;
  }

  return "not possible";
}

string BinaryTreeLCA(string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 3)
    return "-1";

  for (size_t i{}; i < str_arr_size; i++)
    str_arr[i] = trim(str_arr[i]);

  str_arr[0].erase(begin(str_arr[0]));

  str_arr[0].erase(--end(str_arr[0]));

  vector<string> numbers_str{split(str_arr[0], ", ")};

  node<string> heap_btree(numbers_str[0]);

  if (!construct_binary_heap_tree(numbers_str, &heap_btree))
    return "not possible";

  const string lca{find_lca(&heap_btree, str_arr[1], str_arr[2])};

  return lca;
}

int main() {
  // string A[] = gets(stdin);
  // cout << BinaryTreeLCA(A, sizeof(A)/sizeof(*A));
  string B[] = {"[12, 5, 9, 6, 2, 0, 8, #, #, 7, 4, #, #, #, #]", "6", "4"};
  cout << BinaryTreeLCA(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "5"
  string C[] = {"[5, 2, 6, 1, #, 8, #]", "2", "6"};
  cout << BinaryTreeLCA(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "5"
  string D[] = {"[5, 2, 6, 1, #, 8, 12, #, #, #, #, #, #, 3, #]", "3", "12"};
  cout << BinaryTreeLCA(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "12"
  string E[] = {"[5, 2, 6, 1, #, 8, 12, #, #, #, #, #, #, 3, #]", "3", "8"};
  cout << BinaryTreeLCA(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "6"

  return 0;
}
