/*
Coderbyte coding challenge: First Reverse

Using the C++ language, have the function FirstReverse(str) take the str parameter being passed and return the string in reversed order. 
For example: if the input string is "Hello World and Coders" then your program should return the string sredoC dna dlroW olleH.

Sample test cases:

Input:  "coderbyte"
Output: "etybredoc"

Input:  "I Love Code"
Output: "edoC evoL I"
*/

#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

string trim(const string& str) 
{
  const size_t str_len{str.length()};
  
  if (!str_len)
    return string{};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return string{};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str]))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string FirstReverse(string str) {

  str = trim(str);

  const size_t str_len { str.length() };

  if (str_len < 2u) return str;

  for (size_t i{}; i < str_len / 2; i++) {
  	swap(str[i], str[str_len - 1 - i]);
  }

  return str;            
}

string FirstReverse_v2(string str) {

  reverse(begin(str), end(str));

  return str;  
}

int main() { 
  
  // cout << FirstReverse(gets(stdin));
  cout << FirstReverse(move(string{"Hello World and Coders"})) << '\n'; // expected output: "sredoC dna dlroW olleH" 
  cout << FirstReverse(move(string{"coderbyte"})) << '\n';              // expected output: "etybredoc"
  cout << FirstReverse(move(string{"I Love Code"})) << '\n';            // expected output: "edoC evoL I"

  return 0;

}
