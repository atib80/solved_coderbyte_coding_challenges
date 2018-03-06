#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct tree_node {

  int val;
  tree_node* left;
  tree_node* right;

  tree_node(const int x) : val{x}, left{}, right{} {}

};

class Solution {
 public:
  vector<int> preorder_traversal(tree_node* root) {
    vector<int> output{};

    if (!root)
      return output;

    stack<tree_node*> preorder_nodes;
    preorder_nodes.emplace(root);

    while (!preorder_nodes.empty()) {
      const tree_node* node{preorder_nodes.top()};
      output.emplace_back(node->val);
      preorder_nodes.pop();

      if (node->right)
        preorder_nodes.emplace(node->right);
      if (node->left)
        preorder_nodes.emplace(node->left);
    }

    return output;
  }
  
};

int main() {
  
  tree_node root_node{1};
  tree_node tree_right_node{2};
  tree_node tree_right_node_left_child{3};
  root_node.right = &tree_right_node;
  tree_right_node.left = &tree_right_node_left_child;

  Solution solution{};
  const auto result = solution.preorder_traversal(&root_node);

  for (const auto value : result)
    cout << value << ' ';

  cout << '\n';

  return 0;
}
