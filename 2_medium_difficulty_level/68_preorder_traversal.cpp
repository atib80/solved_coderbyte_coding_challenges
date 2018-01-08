/*
Coderbyte coding challenge: Preorder Traversal

Using the C++ language, have the function PreorderTraversal(strArr) take the array of strings stored in strArr, which will represent a binary tree with integer values 
in a format similar to how a binary heap is implemented with NULL nodes at any level represented with a #. 
Your goal is to return the pre-order traversal of the tree with the elements separated by a space. 
For example: if strArr is ["5", "2", "6", "1", "9", "#", "8", "#", "#", "#", "#", "4", "#"] then this tree looks like the following tree:

For the input above, your program should return the string 5 2 1 9 6 8 4 because that is the pre-order traversal of the tree.
Sample Test Cases

Input:  {"4", "1", "5", "2", "#", "#", "#"}
Output: "4 1 2 5"

Input:  {"2", "6", "#"}
Output: "2 6"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

string trim(const string& str)
{
  size_t begin_str{};
  size_t end_str{str.size() - 1};

  if (0u == str.length()) return string{};

  for (; begin_str <= end_str; ++begin_str)
  {
    if (!isspace(str[begin_str])) break;
  }

  if (begin_str > end_str) return string{};

  for (; end_str > begin_str; --end_str)
  {
    if (!isspace(str[end_str])) break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

void list_out_contents_using_preorder_traversal(const vector<string>& binary_tree, size_t i, ostringstream& res) {

	if (i >= binary_tree.size()) return;

	if (binary_tree[i] == "#") return;	

	res << binary_tree[i] << ' ';

	if (((2 * i + 1) >= binary_tree.size()) && (binary_tree[i - 1] == "#")) i--;	
	
	list_out_contents_using_preorder_traversal(binary_tree, 2 * i + 1, res);

	list_out_contents_using_preorder_traversal(binary_tree, 2 * i + 2, res);

}

string PreorderTraversal(string* str_arr, const size_t str_arr_size) {

  vector<string> items(str_arr, str_arr + str_arr_size);

  for (auto& i : items) i = trim(i);

  ostringstream ross{};

  list_out_contents_using_preorder_traversal(items, 0u, ross);

  string result { ross.str() }; 

  result.erase(--end(result));        

  return result;
}

int main() { 
   
    
  // string A[] = gets(stdin);
  // cout << PreorderTraversal(A, sizeof(A)/sizeof(*A));
  string B[] = {"5", "2", "6", "1", "9", "#", "8", "#", "#", "#", "#", "4", "#"};
  cout << '"' << PreorderTraversal(B, sizeof(B)/sizeof(*B)) << '"' << '\n'; // expected output: "5 2 1 9 6 8 4"
  string C[] = {"4", "1", "5", "2", "#", "#", "#"};
  cout << '"' << PreorderTraversal(C, sizeof(C)/sizeof(*C)) << '"' << '\n'; // expected output: "4 1 2 5"
  string D[] = {"2", "6", "#"};
  cout << '"' << PreorderTraversal(D, sizeof(D)/sizeof(*D)) << '"' << '\n'; // expected output: "2 6"
  string E[] = {"5"};
  cout << '"' << PreorderTraversal(E, sizeof(E)/sizeof(*E)) << '"' << '\n'; // expected output: "5"

  return 0;

}
