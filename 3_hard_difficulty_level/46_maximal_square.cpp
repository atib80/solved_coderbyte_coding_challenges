/*
Coderbyte coding challenge: Maximal Square

Using the C++ language, have the function MaximalSquare(strArr) take the strArr parameter being passed which will be a 2D matrix of 0 and 1's, 
and determine the area of the largest square submatrix that contains all 1's. 
A square submatrix is one of equal width and height, and your program should return the area of the largest submatrix that contains only 1's. 
For example: if strArr is ["10100", "10111", "11111", "10010"] then this looks like the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

For the input above, you can see the bolded 1's create the largest square submatrix of size 2x2, so your program should return the area which is 4. 
You can assume the input will not be empty.

Sample test cases:

Input:  "0111", "1111", "1111", "1111"
Output: 9

Input:  "0111", "1101", "0111"
Output: 1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string maximal_square(const string* str_arr, const size_t str_array_size) {

	const size_t row_size{ str_array_size };
	const size_t column_size{ str_arr[0].length() };

	for (size_t i{}; i < (str_array_size - 1); i++) {
		if (str_arr[i].length() != str_arr[i + 1].length()) return string{ "not possible" };
	}

	size_t max_square_size { min(row_size, column_size) };

	while (max_square_size != 0) {

		const string ones(max_square_size, '1');
		
		size_t count{};

		size_t prev_col_index { string::npos };

		for (size_t j{}; (j + max_square_size) <= column_size; j++) {

			for (size_t i{}; (i + max_square_size) <= row_size; i++) {

				for (size_t k{}; k < max_square_size; k++) {

					const size_t col_index = str_arr[i + k].find(ones, j);

					if (string::npos == col_index) {
						prev_col_index = string::npos;
						count = 0;
						break;
					}

					if (string::npos == prev_col_index) {
						prev_col_index = col_index;
						j = col_index;
						count++;
						if (1u == max_square_size) return "1";
						continue;
					}

					if (col_index != prev_col_index) {
						prev_col_index = string::npos;
						count = 0;
						break;
					}

					count++;
					
					if (count == max_square_size) return to_string(max_square_size * max_square_size);

				}

			}
		}

		max_square_size--;
	}

	return string { "0" };

}

int main() {

	// const string matrix[] = gets(stdin);
	// cout << maximal_square(matrix, sizeof(matrix)/sizeof(matrix[0]));
	const string matrix1[] = { "10100", "10111", "11111", "10010" };
	cout << maximal_square(matrix1, sizeof(matrix1) / sizeof(matrix1[0])) << '\n'; // expected output: "4"
	const string matrix2[] = { "0111", "1111", "1111", "1111" };
	cout << maximal_square(matrix2, sizeof(matrix2) / sizeof(matrix2[0])) << '\n'; // expected output: "9"
	const string matrix3[] = { "0111", "1101", "0111" };
	cout << maximal_square(matrix3, sizeof(matrix3) / sizeof(matrix3[0])) << '\n'; // expected output: "1"

	return 0;

}
