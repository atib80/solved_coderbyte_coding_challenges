/*
Coderbyte coding challenge: Even Pairs

Using the C++ language, have the function EvenPairs(str) take the str parameter being passed and determine if a pair of adjacent even numbers exists 
anywhere in the string. If a pair exists, return the string true, otherwise return false. For example: if str is "f178svg3k19k46" then there are two even numbers 
at the end of the string, "46" so your program should return the string true. Another example: if str is "7r5gg812" then the pair is "812" (8 and 12) 
so your program should return the string true.

Sample test cases:

Input:  "3gy41d216"
Output: "true"

Input:  "f09r27i8e67"
Output: "false"
*/

#include <iostream>
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

string EvenPairs(string str) {

  str = trim(str);

  if (str.length() < 2u) return "false";

  size_t start{};

  while (true) {

  	start = str.find_first_of("0123456789", start);

  	if (string::npos == start) return "false";

  	const size_t last { str.find_first_not_of("0123456789", start + 1) };

  	if (string::npos == last) {

  		string num_str { str.substr(start) };

  		while ('0' == num_str[0]) {

  			num_str.erase(begin(num_str));
 		}

  		const int number { stoi(num_str) };

  		if ((num_str.length() > 1u) && (number % 2 == 0)) return "true";

  		return "false";
  	
  	} else {

  		string num_str { str.substr(start, last - start) };

  		while ('0' == num_str[0]) {

  				num_str.erase(begin(num_str));
 		}


  		const int number { stoi(num_str) };

  		if ((num_str.length() > 1u) && (number % 2 == 0)) return "true";
  	}

  	start = last;

  }
 
  return "false";
}

int main() { 
  
  // cout << EvenPairs(move(string{gets(stdin)}));
  cout << EvenPairs(move(string{"f178svg3k19k46"})) << '\n'; // expected output: "true"
  cout << EvenPairs(move(string{"7r5gg812"})) << '\n';       // expected output: "true" 
  cout << EvenPairs(move(string{"3gy41d216"})) << '\n';      // expected output: "true"
  cout << EvenPairs(move(string{"f09r27i8e67"})) << '\n';    // expected output: "false"  
  
  return 0;
}
