/*
Coderbyte coding challenge: Kaprekars Constant

Using the C++ language, have the function KaprekarsConstant(num) take the num parameter being passed which will be a 4-digit number with at least two distinct digits. 
Your program should perform the following routine on the number: 
Arrange the digits in descending order and in ascending order (adding zeroes to fit it to a 4-digit number), and subtract the smaller number from the bigger number. 
Then repeat the previous step. Performing this routine will always cause you to reach a fixed number: 6174. 
Then performing the routine on 6174 will always give you 6174 (7641 - 1467 = 6174). 
Your program should return the number of times this routine must be performed until 6174 is reached. 
For example: if num is 3524 your program should return 3 because of the following steps: (1) 5432 - 2345 = 3087, (2) 8730 - 0378 = 8352, (3) 8532 - 2358 = 6174.

Sample test cases:

Input:  2111
Output: 5

Input:  9831
Output: 7
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 3524
// 1. iteration: 5432 - 2345 = 3087
// 2. iteration: 8730 - 0378 = 8352
// 3. iteration: 8532 - 2358 = 6174

size_t KaprekarsConstant(int num) { 
	
	size_t iter_count{};

	// 7. step: check if new difference of lhs_num and rhs_num is equal to 6174. If it is, then we return iter_count
	while (num != 6174) {

		string number_str{to_string(num)};

		const size_t number_str_len { number_str.length() };

		if (number_str_len < 4) {
			number_str.insert(begin(number_str), 4 - number_str_len, '0');
		}

		// 1. step: convert num (int) to number_str (string) and sort its digits in descending order. (1. 3524 -> 5432)
		sort(begin(number_str), end(number_str), [](const char lc, const char rc) {
			return (lc > rc);
		});

		// 2. step: convert number_str (string, all of its 4 digits sorted in descending order) to lhs_num (int)

		const int lhs_num = stoi(number_str);

		// 3. step: reverse the order of digits in number_str

		reverse(begin(number_str), end(number_str));

		// 4. step: convert number_str (string, all of its 4 digits sorted in ascending order) to rhs_num (int)

		const int rhs_num = stoi(number_str);

		// 5. step: calculate different of lhs_num and rhs_num

		num = lhs_num - rhs_num;

		// 6. step: increment iter_count by 1

		iter_count++;
	
	}

  return iter_count; 
            
}

int main() { 
  
  // cout << KaprekarsConstant(gets(stdin));
  cout << KaprekarsConstant(3524) << '\n'; // expected output: 3
  cout << KaprekarsConstant(2111) << '\n'; // expected output: 5
  cout << KaprekarsConstant(9831) << '\n'; // expected output: 7

  return 0;    
}
