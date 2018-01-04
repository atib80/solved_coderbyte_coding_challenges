/*
Coderbyte coding challenge: Number Addition

Using the C++ language, have the function NumberSearch(str) take the str parameter, search for all the numbers in the string, 
add them together, then return that final number. For example: if str is "88Hello 3World!" the output should be 91. 
You will have to differentiate between single digit numbers and multiple digit numbers like in the example above. 
So "55Hello" and "5Hello 5" should return two different answers. Each string will contain at least one letter or symbol.

Sample test cases:

Input:  "75Number9"
Output: 84

Input:  "10 2One Number*1*"
Output: 13
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

string NumberAddition(string str) {

  str = trim(str);

  const size_t str_len { str.length() };
  size_t sum{}, pos{};
  
  while (pos < str_len) {

  	const size_t start_digit { str.find_first_of("0123456789", pos) };

  	if (string::npos == start_digit) return to_string(sum);
  	
  	const size_t end_digit { str.find_first_not_of("0123456789", start_digit + 1) };

  	if (string::npos == end_digit) {

  		sum += stoul(str.substr(start_digit));

  		return to_string(sum);
  	}

  	sum += stoul(str.substr(start_digit, end_digit - start_digit));

  	pos = end_digit;

  }

  return to_string(sum);
            
}

int main() { 
  
  cout << NumberAddition(move(string{gets(stdin)}));  
  // cout << NumberAddition(move(string{"88Hello 3World!"})) << '\n';	  // expected output: 91
  // cout << NumberAddition(move(string{"55Hello"})) << '\n';           // expected output: 55
  // cout << NumberAddition(move(string{"5Hello 5"})) << '\n';          // expected output: 10
  // cout << NumberAddition(move(string{"75Number9"})) << '\n';         // expected output: 84
  // cout << NumberAddition(move(string{"10 2One Number*1*"})) << '\n'; // expected output: 13  
  return 0;    
}
