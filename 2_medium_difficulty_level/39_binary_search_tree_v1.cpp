/*
Coderbyte coding challenge: Binary Search Tree

Using the C++ language, have the function BinarySearchTreeLCA(strArr) take the
array of strings stored in strArr, which will contain 3 elements: the first
element will be a binary search tree with all unique values in a preorder
traversal array, the second and third elements will be two different values, and
your goal is to find the lowest common ancestor of these two values.

For example: if strArr is ["[10, 5, 1, 7, 40, 50]", "1", "7"] then this tree
looks like the following:

     [10]
   [5]  [40]
 [1][7]   [50]


For the input above, your program should return 5 because that is the value of
the node that is the LCA of the two nodes with values 1 and 7. You can assume
the two nodes you are searching for in the tree will exist somewhere in the
tree.

Sample test cases:

Input:  "[10, 5, 1, 7, 40, 50]", "5", "10"
Output: 10

Input:  "[3, 2, 1, 12, 4, 5, 13]", "5", "13"
Output: 12
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
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

struct node {
  int number;
  node* left{};
  node* right{};
  node* parent{};

  node(const int n, node* p = nullptr) : number{n}, parent{p} {}

  ~node() {
    if (left) {
      delete left;
    }

    if (right) {
      delete right;
    }
  }

  node* insert(const int n) {
    if (n < number) {
      if (left)
        return left->insert(n);
      else {
        left = new node(n, this);
        return left;
      }

    } else {
      if (right)
        return right->insert(n);
      else {
        right = new node(n, this);
        return right;
      }
    }
  }
};

int BinarySearchTreeLCA_v1(string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 3)
    return -1;

  for (size_t i{}; i < str_arr_size; i++)
    str_arr[i] = trim(str_arr[i]);

  str_arr[0].erase(begin(str_arr[0]));

  str_arr[0].erase(--end(str_arr[0]));

  vector<string> numbers_str{split(str_arr[0], ",")};

  vector<int> numbers(numbers_str.size());

  for (size_t i{}; i < numbers_str.size(); i++)
    numbers[i] = stoi(numbers_str[i]);

  const int number1{stoi(str_arr[1])};
  const int number2{stoi(str_arr[2])};

  node bst{numbers[0]};
  node *node_number1{&bst}, *node_number2{&bst};

  for (size_t i{1}; i < numbers.size(); i++) {
    node* node{bst.insert(numbers[i])};

    if (number1 == numbers[i])
      node_number1 = node;

    else if (number2 == numbers[i])
      node_number2 = node;
  }

  unordered_set<int> ancestors;

  for (node* node{node_number1}; node; node = node->parent) {
    ancestors.insert(node->number);
  }

  for (node* node{node_number2}; node; node = node->parent) {
    if (ancestors.count(node->number))
      return node->number;
  }

  return -1;
}

int main() {
  // string A[] = gets(stdin);
  // cout << BinarySearchTreeLCA_v1(A, sizeof(A)/sizeof(*A));
  string B[] = {"[10, 5, 1, 7, 40, 50]", "1", "7"};
  cout << BinarySearchTreeLCA_v1(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 5
  string C[] = {"[10, 5, 1, 7, 40, 50]", "5", "10"};
  cout << BinarySearchTreeLCA_v1(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 10
  string D[] = {"[3, 2, 1, 12, 4, 5, 13]", "5", "13"};
  cout << BinarySearchTreeLCA_v1(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 12
  return 0;
}