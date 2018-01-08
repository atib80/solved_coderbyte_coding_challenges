/*
Coderbyte coding challenge: Simple Password

Using the C++ language, have the function SimplePassword(str) take the str parameter being passed and determine if it passes as a valid password that follows 
the list of constraints:

1. It must have a capital letter.
2. It must contain at least one number.
3. It must contain a punctuation mark.
4. It cannot have the word "password" in the string.
5. It must be longer than 7 characters and shorter than 31 characters.

If all the above constraints are met within the string, the your program should return the string true, otherwise your program should return the string false. 
For example: if str is "apple!M7" then your program should return "true".

Sample test cases:

Input:  "passWord123!!!!"
Output: "false"

Input:  "turkey90AAA="
Output: "true"
*/

#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
#include <locale>

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

size_t strstri(const string& src, const string& needle, const std::locale& loc = std::locale{})
{

	string src_lc{ src };
	string needle_lc{ needle };

	transform(begin(src), end(src), begin(src_lc), [&](const char ch) {
		return tolower(ch, loc);
	});

	transform(begin(needle), end(needle), begin(needle_lc), [&](const char ch) {
		return tolower(ch, loc);
	});
	
	return src_lc.find(needle_lc);
}

string SimplePassword(string str) { 

  str = trim(str);
  const size_t str_len { str.length() };
  
  if (str_len < 7 || str_len > 31) return string{"false"}; 
  
  if (strstri(str, "password") != string::npos) return string{"false"}; 
  
  if (!any_of(begin(str), end(str), [](const char ch) { return isupper(ch); })) return string{"false"};

  if (!any_of(begin(str), end(str), [](const char ch) { return isdigit(ch); })) return string{"false"};

  if (!any_of(begin(str), end(str), [](const char ch) { return ispunct(ch); })) return string{"false"};

  return string{"true"};            
}

int main() { 
  
  // cout << SimplePassword(move(string{gets(stdin)}));
  cout << SimplePassword(move(string{"apple!M7"})) << '\n';                  // expected output: "true"
  cout << SimplePassword(move(string{"passWord123!!!!"})) << '\n';           // expected output: "false"
  cout << SimplePassword(move(string{"turkey90AAA="})) << '\n';              // expected output: "true"
  cout << SimplePassword(move(string{"!!!!!!+++++++++AMAMAM9"})) << '\n';    // expected output: "true"

  return 0;

} 
