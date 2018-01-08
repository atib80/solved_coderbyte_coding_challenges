/*
Coderbyte coding challenge: Largest Row Column (medium - hard difficulty level)

Using the C++ language, have the function LargestRowColumn(strArr) read the strArr parameter being passed which will be a 2D matrix of some arbitrary size filled with 
positive integers. Your goal is to determine the largest number that can be found by adding up three digits in the matrix that are within the same path, 
where being on the same path means starting from one of the elements and then moving either up, down, left, or right onto the next element without reusing elements. 
One caveat though, and that is when you calculate the sum of three digits, you should split the sum into two digits and treat the new digits as a row/column position 
in the matrix. So your goal is actually to find the sum of three digits that sums to the largest position in the matrix without going out of the bounds. 
For example: if strArr is ["345", "326", "221"] then this looks like the following matrix:

3 4 5
3 2 6
2 2 1

The solution to this problem is to sum the bolded elements, 4 + 2 + 6, which equals 12. Then you take the solution, 12, and split it into two digits: 
1 and 2 which represents row 1, column 2 in the matrix. This is the largest position you can get in the matrix by adding up 3 digits so your program should return 12. 
If you for example added up 4 + 5 + 6 in the matrix you would get 15 which is larger than 12, but row 1, column 5 is out of bounds. 
It's also not possible with the current matrix to sum to any of the following numbers: 20, 21, 22. If you find a sum that is only a single digit, 
you can treat that as row 0, column N where N is your sum.

Sample test cases:

Input:  "234", "999", "999"
Output: 22

Input:  "11111", "22222"
Output: 4
*/

#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
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

inline size_t distance(const pair<size_t, size_t>& x, const pair<size_t, size_t>& y) {

	const size_t d { ( x.first < y.first ? y.first - x.first : x.first - y.first) + ( x.second < y.second ? y.second - x.second : x.second - y.second) };
	return d;
}

int find_highest_valid_pair_of_indices_in_matrix(const vector<vector<int>>& matrix, const size_t row_size, const size_t col_size) {  	

  	const int max_row_size { static_cast<int>(row_size - 1) };
  	const int max_col_size { static_cast<int>(col_size - 1) };

  	const size_t max_row_increment { row_size > 2 ? 2 : row_size - 1 };
  	const size_t max_col_increment { col_size > 2 ? 2 : col_size - 1 };

  	int current_max_sum{};  	

  	for (size_t i{}; (i + max_row_increment) < row_size; i++) {

    	for (size_t j{}; (j + max_col_increment) < col_size; j++) {

    		vector<pair<size_t, size_t>> coordinate_pairs{}; 		

    		for (size_t x{i}; x <= (i + max_row_increment); x++) {
    		
    			for (size_t y{j}; y <= (j + max_col_increment); y++) {

    				coordinate_pairs.emplace_back(make_pair(x, y));

    			}
    		}    	
		
       	sort(begin(coordinate_pairs), end(coordinate_pairs), [](const pair<size_t, size_t>& lc, const pair<size_t, size_t>& rc) {
       		return ((lc.first < rc.first) && (lc.second < rc.second));
       	});
       	       	 	

       	do {      		

       		if ( (distance(coordinate_pairs[0], coordinate_pairs[1]) == 1u) &&
       		     (distance(coordinate_pairs[1], coordinate_pairs[2]) == 1u) &&
       		     (distance(coordinate_pairs[0], coordinate_pairs[2]) == 2u) ) {

       			const int sum { matrix[coordinate_pairs[0].first][coordinate_pairs[0].second] 
       					 	+ matrix[coordinate_pairs[1].first][coordinate_pairs[1].second] 
       					 	+ matrix[coordinate_pairs[2].first][coordinate_pairs[2].second] };

       			if ((sum < 10) && (sum <= static_cast<int>(max_col_size)) && (sum > current_max_sum)) {
	        		current_max_sum = sum;

        		} else {

        			if ((sum / 10 <= max_row_size) && (sum % 10 <= max_col_size)) {

        				if (sum > current_max_sum) current_max_sum = sum;
	       			}

        		}

        }       			       			


       	} while (next_permutation(begin(coordinate_pairs), end(coordinate_pairs)));          	
    
  	}

  }   

  return current_max_sum;

}

string LargestRowColumn(string* str_arr, const size_t str_arr_size) {

	if (!str_arr || str_arr_size < 1u) return string{"not possible"};

	vector<vector<int>> matrix ( str_arr_size, vector<int>{} );

	str_arr[0] = trim(str_arr[0]);

  	const size_t row_size { str_arr_size };
  	const size_t col_size { str_arr[0].length() };

  	for (size_t i{}; i != row_size; i++) {

  		str_arr[i] = trim(str_arr[i]);

  		if (col_size != str_arr[i].length()) throw range_error("Column widths of specified matrix must be equal!");

  		matrix[i].resize(str_arr[i].length());

  		for (size_t j{}; j != str_arr[i].length(); j++) {
  			if (str_arr[i][j] < '0' || str_arr[i][j] > '9') throw range_error("Matrix must consist of numeric digit values only!");
  			matrix[i][j] = static_cast<int>(str_arr[i][j] - '0');
  		}
  	}

   return to_string(find_highest_valid_pair_of_indices_in_matrix(matrix, row_size, col_size));        
}

int main() { 
   
  // string A[] = gets(stdin);
  // cout << LargestRowColumn(A, sizeof(A)/sizeof(*A));
  string B[] = {"345", "326", "221"};
  cout << LargestRowColumn(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 12
  string C[] = {"234", "999", "999"};
  cout << LargestRowColumn(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 22
  string D[] = {"11111", "22222"};
  cout << LargestRowColumn(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 4
  string E[] = {"11111", "27222"};
  cout << LargestRowColumn(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: 11
  string F[] = {"11111", "22922"};
  cout << LargestRowColumn(F, sizeof(F)/sizeof(*F)) << '\n'; // expected output: 13
  string G[] = {"14567", "89123", "56711", "23456"};
  cout << LargestRowColumn(G, sizeof(G)/sizeof(*G)) << '\n'; // expected output: 23
  
  return 0;    
}
