/*
Coderbyte coding challenge: Binary Reversal

Using the C++ language, have the function BinaryReversal(str) take the str parameter being passed, 
which will be a positive integer, take its binary representation, reverse that string of bits, 
and then finally return the new reversed string in decimal form. 
For example: if str is "47" then the binary version of this integer is 00101111. 
Your program should reverse this binary string which then becomes: 11110100 and then finally return the decimal version of this string, which is 244.

Sample test cases:

Input:  "213"
Output: "171"

Input:  "4567"
Output: "60296"
*/

#include <iostream>
#include <string>
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

string convert_to_bin_string(int number) {

	string bin_str{};

	size_t i{};

	while (number) {
		if (number % 2 == 1) bin_str.push_back('1');
		else bin_str.push_back('0');		
		number /= 2;
		i++;
	}

	reverse(begin(bin_str), end(bin_str));

	if ((i % 8) != 0) bin_str.insert(0, move(string( (i / 8 + 1) * 8 - i, '0' )));
    
	return bin_str;
}

string BinaryReversal(string str) {

  const int number{stoi(str)};
  
  if (!number) return "0";

  string bin_str{convert_to_bin_string(number)};

  reverse(begin(bin_str), end(bin_str));

  return to_string(stoi(bin_str, nullptr, 2));

}

int main() { 
  
  // cout << BinaryReversal(move(string{gets(stdin)}));
  cout << BinaryReversal(move(string{"47"})) << '\n';   // expected output: "244"
  cout << BinaryReversal(move(string{"213"})) << '\n';  // expected output: "171"
  cout << BinaryReversal(move(string{"4567"})) << '\n'; // expected output: "60296"
  
  return 0;    
}
