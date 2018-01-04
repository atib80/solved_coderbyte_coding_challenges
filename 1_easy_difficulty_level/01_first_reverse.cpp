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

#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

string FirstReverse(string str) {

  const size_t str_len { str.length() };

  if (str_len < 2u) return str;

  for (size_t i{}; i != str_len / 2; i++) {
  	swap(str[i], str[str_len - 1 - i]);
  }

  // we can also make use of the handy std::reverse(BidirIt first, BidirIt last) template function from the <algorithm> header.
  // reverse(begin(str), end(str));
  
  return str; 
            
}

int main() { 
  
  // cout << FirstReverse(gets(stdin));
  cout << FirstReverse(move(string{"Apple juice"})) << '\n';
  cout << FirstReverse(move(string{"Racercar"})) << '\n';
  cout << FirstReverse(move(string{"never odd or even"})) << '\n';

  return 0;

}