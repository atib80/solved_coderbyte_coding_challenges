/*
Coderbyte coding challenge: Binary Search Tree

Using the C++ language, have the function BinarySearchTreeLCA(strArr) take the array of strings stored in strArr, which will contain 3 elements: 
the first element will be a binary search tree with all unique values in a preorder traversal array, the second and third elements will be two different values, 
and your goal is to find the lowest common ancestor of these two values. 

For example: if strArr is ["[10, 5, 1, 7, 40, 50]", "1", "7"] then this tree looks like the following:

     [10]
   [5]  [40] 
 [1][7]   [50]


For the input above, your program should return 5 because that is the value of the node that is the LCA of the two nodes with values 1 and 7. 
You can assume the two nodes you are searching for in the tree will exist somewhere in the tree.

Sample test cases:

Input:  "[10, 5, 1, 7, 40, 50]", "5", "10"
Output: 10

Input:  "[3, 2, 1, 12, 4, 5, 13]", "5", "13"
Output: 12
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include <algorithm>

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

vector<string> split(const string& source, const char* needle, size_t const max_count = string::npos)
{
  vector<string> parts{}; 

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len)) return parts;

  size_t number_of_parts{}, prev{};

  while (true)
  {
    const size_t current = source.find(needle_st, prev);

    if (string::npos == current) break;

    number_of_parts++;

    if ((string::npos != max_count) && (parts.size() == max_count)) break;

    if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len) break;
  } 

  if (prev < source_len)
  {
    if (string::npos == max_count) parts.emplace_back(source.substr(prev));

    else if ((string::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
  }

  return parts;
}

struct node
{
    int number;
    node *left{};
    node *right{};
    node *parent{};
    
    node(const int n, node* p = nullptr) : number{n}, parent{p} { }
    
    ~node()
    {
        if (left) {
          delete left;
        }

        if (right) {
          delete right;
        }    
    }

    node* insert(const int n)
    {
        if (n < number)
        {
            if (left) return left->insert(n);            
            else {

                left = new node(n, this);
                return left;
            }
        
        } else {

            if (right) return right->insert(n);
            else
            {
                right = new node(n, this);
                return right;
            }
        }
    }
};

int BinarySearchTreeLCA(string* str_arr, const size_t str_arr_size) {

  if (str_arr_size < 3u) return -1;

  for (size_t i{}; i != str_arr_size; i++) str_arr[i] = trim(str_arr[i]);

  str_arr[0].erase(begin(str_arr[0]));

  str_arr[0].erase(--end(str_arr[0]));

  vector<string> numbers_str { split(str_arr[0], ",") };

  for (auto& number_str : numbers_str) number_str = trim(number_str);

  vector<int> numbers(numbers_str.size());

  for (size_t i{}; i != numbers_str.size(); i++) numbers[i] = stoi(numbers_str[i]);

  const int number1 { stoi(str_arr[1]) };
  const int number2 { stoi(str_arr[2]) };

  node bst { numbers[0] };
  node *node_n1{&bst}, *node_n2{&bst};

  for (size_t i{1u}; i != numbers.size(); i++)
  {
      node* node { bst.insert(numbers[i]) };
      
      if (number1 == numbers[i]) node_n1 = node;      
      
      else if(number2 == numbers[i]) node_n2 = node;
      
  }

  set<int> ancestors;
  
  for (node* node{node_n1}; node != nullptr; node = node->parent) {
  
      ancestors.insert(node->number);
  }

  for (node* node{node_n2}; node != nullptr; node = node->parent) {
  
      if (ancestors.count(node->number)) return node->number;
      
  }

  return -1;            
}

int main() { 
   
  // string A[] = gets(stdin);
  // cout << BinarySearchTreeLCA(A, sizeof(A)/sizeof(*A));
  string B[] = {"[10, 5, 1, 7, 40, 50]", "1", "7"};
  cout << BinarySearchTreeLCA(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 5
  string C[] = {"[10, 5, 1, 7, 40, 50]", "5", "10"};
  cout << BinarySearchTreeLCA(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 10
  string D[] = {"[3, 2, 1, 12, 4, 5, 13]", "5", "13"};
  cout << BinarySearchTreeLCA(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 12
  return 0;    
}
