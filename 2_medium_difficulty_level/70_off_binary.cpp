/*
Coderbyte coding challenge: Off Binary

Using the C++ language, have the function OffBinary(strArr) read the array of strings stored in strArr, which will contain two elements, 
the first will be a positive decimal number and the second element will be a binary number. Your goal is to determine how many digits in the binary number
need to be changed to represent the decimal number correctly (either 0 change to 1 or vice versa). For example: if strArr is ["56", "011000"] 
then your program should return 1 because only 1 digit needs to change in the binary number (the first zero needs to become a 1) to correctly represent 56 in binary.

Sample test cases:

Input:  "5624", "0010111111001"
Output: 2

Input:  "44", "111111"
Output: 3
*/

#include <iostream>
#include <cctype>
#include <string>

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

string dec2bin(long long decimal_number, bool pad_binary_number_string_with_leading_zeroes = false) {	

  const size_t base_capacity_size{64u};
  size_t index{63u};
  string result_number(base_capacity_size, '0');

  const bool is_negative { decimal_number < 0 ? true : false };

  if (is_negative) {
    decimal_number = ~decimal_number;
    decimal_number++;
    result_number = move(string(base_capacity_size, '1'));
  }  

	while (decimal_number) {
		if (!is_negative && (decimal_number % 2 == 1)) result_number[index] = '1';
    else if (is_negative && (decimal_number % 2 == 0)) result_number[index] = '0';    
		if (!index) break;
		index--;
		decimal_number /= 2;
	}	

	if (!is_negative && !pad_binary_number_string_with_leading_zeroes) {
		// decimal_number = 53
		// "00000000|00000000|00000000|00000000|00000000|00000000|00000000|00110101" : 58 '0' (out of 64) 
		// characters need to be removed from the beginning of result_number string

		const size_t first_non_zero_digit_pos { result_number.find('1', 0u) };

		if (string::npos == first_non_zero_digit_pos) return "0";

		result_number = result_number.substr(first_non_zero_digit_pos);

	}

	result_number.shrink_to_fit();
  
	return result_number;
}

string OffBinary(string* str_arr, const size_t str_arr_size) {

  if (str_arr_size < 2u) return "not possible";

  const int dec_num { stoi(trim(str_arr[0])) };
  
  string dec_num_bin_str { dec2bin(dec_num) };

  const size_t dec_num_bin_str_len { dec_num_bin_str.length() };
  
  string bin_str { trim(str_arr[1]) };

  const size_t bin_str_len { bin_str.length() };

  if (dec_num_bin_str_len > bin_str_len) {

  	const size_t number_of_bin_digits_to_erase(dec_num_bin_str_len - bin_str_len);

  	dec_num_bin_str.erase(0u, number_of_bin_digits_to_erase);

  } else if (dec_num_bin_str_len < bin_str_len) {

  	const size_t number_of_bin_digits_to_erase(bin_str_len - dec_num_bin_str_len);

  	bin_str.erase(0u, number_of_bin_digits_to_erase);

  }

  if (dec_num_bin_str_len != bin_str_len) return "not possible";

  if (dec_num_bin_str == bin_str) return "0";

  size_t number_of_bin_digits_to_flip{};

  for (size_t i{}; i < bin_str_len; i++) {

  	if (dec_num_bin_str[i] != bin_str[i]) number_of_bin_digits_to_flip++;

  }

  return to_string(number_of_bin_digits_to_flip); 
}

int main() { 
     
  // string A[] = gets(stdin);  
  // cout << OffBinary(A, sizeof(A)/sizeof(*A));
  string B[] = {"56", "011000"};  
  cout << OffBinary(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 1
  string C[] = {"5624", "0010111111001"};  
  cout << OffBinary(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 2
  string D[] = {"44", "111111"};  
  cout << OffBinary(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 3

  return 0;  
} 
