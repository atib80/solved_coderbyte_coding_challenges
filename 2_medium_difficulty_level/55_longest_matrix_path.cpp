/*
Coderbyte coding challenge: Longest Matrix Path

Using the C++ language, have the function LongestMatrixPath(strArr) take the array of strings stored in strArr, 
which will be an NxM matrix of positive single-digit integers, and find the longest increasing path composed of distinct integers. 
When moving through the matrix, you can only go up, down, left, and right. 
For example: if strArr is ["345", "326", "221"], then this looks like the following matrix:

3 4 5
3 2 6
2 2 1

For the input above, the longest increasing path goes from: 3 -> 4 -> 5 -> 6. 
Your program should return the number of connections in the longest path, so therefore for this input your program should return 3. 
There may not necessarily always be a longest path within the matrix.

Sample test cases:

Input:  "12256", "56219", "43215"
Output: 5

Input:  "67", "21", "45"
Output: 3
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <set>

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

size_t find_max_path_distance(const size_t x, const size_t y, const size_t row_size, const size_t column_size, 
	const vector<vector<char>>& matrix, set<size_t>& found_max_distances, size_t distance = 0) {

	if ((x > 0) && (matrix[x][y] < matrix[x - 1][y])) {
		find_max_path_distance(x - 1, y, row_size, column_size, matrix, found_max_distances, distance + 1);
	}

	if ((x < (row_size - 1)) && (matrix[x][y] < matrix[x + 1][y])) {
		find_max_path_distance(x + 1, y, row_size, column_size, matrix, found_max_distances, distance + 1);
	}

	if ((y > 0) && (matrix[x][y] < matrix[x][y - 1])) {
		find_max_path_distance(x,  y - 1, row_size, column_size, matrix, found_max_distances, distance + 1);
	}

	if ((y < (column_size - 1)) && (matrix[x][y] < matrix[x][y + 1])) {
		find_max_path_distance(x, y + 1, row_size, column_size, matrix, found_max_distances, distance + 1);
	}
	
	found_max_distances.insert(distance);

	return *(--end(found_max_distances));
}


string LongestMatrixPath(string* str_arr, const size_t str_arr_size) { 

  const size_t row_size {str_arr_size};
  const size_t column_size { str_arr[0].length() };

  for (size_t i{}; i != row_size; i++) str_arr[i] = trim(str_arr[i]);

  vector<vector<char>> matrix(row_size, vector<char>{});
  
  for (auto& r : matrix) r.resize(column_size);

  for (size_t i{}; i != row_size; i++) {

  	for (size_t j{}; j != column_size; j++) {

  		matrix[i][j] = str_arr[i][j];

  	}

  }

  set<size_t> max_distances{};

  for (size_t i{}; i != row_size; i++) {
  	
  	for (size_t j{}; j != column_size; j++) {

      set<size_t> found_max_distances{};
  	
  		const size_t current_max_distance { find_max_path_distance(i, j, row_size, column_size, matrix, found_max_distances) };

  		max_distances.insert(current_max_distance);

	   }
  
  }
  
  return to_string(*(--end(max_distances)));
  
}

int main() { 
   
  // string A[] = gets(stdin);
  // cout << LongestMatrixPath(A, sizeof(A)/sizeof(*A));
  string B[] = {"345", "326", "221"};
  cout << LongestMatrixPath(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 3
  string C[] = {"12256", "56219", "43215"};
  cout << LongestMatrixPath(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 5
  string D[] = {"67", "21", "45"};
  cout << LongestMatrixPath(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 3

  return 0;
}
