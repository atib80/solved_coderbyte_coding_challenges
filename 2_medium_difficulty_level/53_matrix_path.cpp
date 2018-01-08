/*
Coderbyte coding challenge: Matrix Path

Using the C++ language, have the function MatrixPath(strArr) take the strArr parameter being passed which will be a 2D matrix of 0 and 1's of some arbitrary size, 
and determine if a path of 1's exists from the top-left of the matrix to the bottom-right of the matrix while moving only in the directions: up, down, left, and right. 
If a path exists your program should return the string true, otherwise your program should return the number of locations in the matrix where if a single 0 is replaced 
with a 1, a path of 1's will be created successfully. If a path does not exist and you cannot create a path by changing a single location in the matrix from a 0 to a 1,
then your program should return the string not possible. For example: if strArr is ["11100", "10011", "10101", "10011"] then this looks like the following matrix:

1 1 1 0 0
1 0 0 1 1
1 0 1 0 1
1 0 0 1 1

For the input above, a path of 1's from the top-left to the bottom-right does not exist. But, we can change a 0 to a 1 in 2 places in the matrix, namely at locations: 
0,3] or [1,2]. So for this input your program should return 2. The top-left and bottom-right of the input matrix will always be 1's.

Sample test cases:


1 0 0 0 0
1 1 0 1 1
1 0 1 0 1
1 1 0 0 1

Input:  "10000", "11011", "10101", "11001"
Output: 1

Input:  "1000001", "1001111", "1010101"
Output: "not possible"
*/

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <stdexcept>

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

bool is_matrix_path_connected(vector<vector<bool>>& m, const size_t i, const size_t j, const size_t row_size, const size_t col_size) {

  if ((i == (row_size - 1)) && (j == (col_size - 1))) return true;

  m[i][j] = false; 
  
  // N direction
  if ((i > 0) && m[i - 1][j] && is_matrix_path_connected(m, i - 1, j, row_size, col_size)) return true;
  // E direction
  if ((j < (col_size - 1)) && m[i][j + 1] && is_matrix_path_connected(m, i, j + 1, row_size, col_size)) return true;
  // S direction
  if ((i < (row_size - 1)) && m[i + 1][j] && is_matrix_path_connected(m, i + 1, j, row_size, col_size)) return true;
  // W direction
  if ((j > 0) && m[i][j - 1] && is_matrix_path_connected(m, i, j - 1, row_size, col_size)) return true;

  return false;

}

size_t find_connected_paths_in_matrix(const vector<vector<bool>>& matrix, const size_t row_size, const size_t col_size) {

  size_t count{};

  for (size_t i{}; i != row_size; i++) {

    for (size_t j{}; j != col_size; j++) {

    	if (!i && !j) continue;

    	if (((row_size - 1) == i) && ((col_size - 1) == j)) continue;

      	if (!matrix[i][j]) {

        	vector<vector<bool>> m { matrix };

        	m[i][j] = true;

        	if (is_matrix_path_connected(m, 0u, 0u, row_size, col_size)) count++;

        }
    }
  
  }

  return count;

}

string MatrixPath(string* str_arr, const size_t str_arr_size) {

	if (!str_arr || str_arr_size < 1u) return string{"not possible"};  

  	vector<vector<bool>> matrix(str_arr_size, vector<bool>{});

  	const size_t row_size {str_arr_size};
  	const size_t col_size {str_arr[0].length()};

  	for (size_t i{}; i != row_size; i++) {

  		str_arr[i] = trim(str_arr[i]);

  		if (col_size != str_arr[i].length()) throw range_error("Column widths of specified matrix must be equal!");

  		matrix[i].resize(str_arr[i].length());

  		for (size_t j{}; j != str_arr[i].length(); j++) matrix[i][j] = ('0' != str_arr[i][j]);
  	} 

   if (!matrix[0][0] || !matrix[row_size - 1][col_size - 1]) 
   	throw runtime_error("There can never exist a connected path in specified matrix if its top leftmost (0,0) and/or boot rightmost (row_size - 1, col_size - 1) cells are false!");

   vector<vector<bool>> m { matrix };

   if (is_matrix_path_connected(m, 0u, 0u, row_size, col_size)) return string{"true"};

   const size_t possible_connections_count{ find_connected_paths_in_matrix(matrix, row_size, col_size) };

   if (!possible_connections_count) return string{"not possible"};
 
  return to_string(possible_connections_count);
}

int main() {
    
  // string A[] = gets(stdin);
  // cout << MatrixPath(A, sizeof(A)/sizeof(*A));
  string B[] = {"11100", "10011", "10101", "10011"};
  cout << MatrixPath(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 2
  string C[] = {"10000", "11011", "10101", "11001"};
  cout << MatrixPath(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 1
  string D[] = {"1000001", "1001111", "1010101"};
  cout << MatrixPath(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "not possible"

  return 0;    
}
