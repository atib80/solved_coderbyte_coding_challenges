/*
Coderbyte coding challenge: Symmetric Tree

Using the C++ language, have the function SymmetricTree(strArr) take the array of strings stored in strArr, which will represent a binary tree, 
and determine if the tree is symmetric (a mirror image of itself). The array will be implemented similar to how a binary heap is implemented, 
except the tree may not be complete and NULL nodes on any level of the tree will be represented with a #. 
For example: if strArr is ["1", "2", "2", "3", "#", "#", "3"] then this tree looks like the following:

     [1]
  [2]   [2] 
[3][#] [#][3]

For the input above, your program should return the string true because the binary tree is symmetric.

Sample test cases:

Input:  "4", "3", "4"
Output: "false"

Input:  "10", "2", "2", "#", "1", "1", "#"
Output: "true"
*/

#include <iostream>
#include <string>

using namespace std;

string SymmetricTree(const string* str_arr, const size_t str_arr_size) {

  for (size_t i{1u}; i < str_arr_size; i = 2 * i + 1) {

  	for (size_t j{i}, k{2 * i}; j < k; j++, k--) {

  		if (str_arr[j] != str_arr[k]) return "false";
  	}

  }

  return "true"; 
            
}

int main() {   
    
  // const string A[] = gets(stdin);  
  // cout << SymmetricTree(A, sizeof(A)/sizeof(*A));
  const string B[] = {"1", "2", "2", "3", "#", "#", "3"};  
  cout << SymmetricTree(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "true"
  const string C[] = {"10", "2", "2", "#", "1", "1", "#"};  
  cout << SymmetricTree(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "true"
  const string D[] = {"4", "3", "4"};  
  cout << SymmetricTree(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "false"

  return 0;    
}
