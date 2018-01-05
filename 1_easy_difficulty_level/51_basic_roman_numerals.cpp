/*
Coderbyte coding challenge: Basic Roman Numerals

Using the C++ language, have the function BasicRomanNumerals(str) read str which will be a string of Roman numerals. 
The numerals being used are: I for 1, V for 5, X for 10, L for 50, C for 100, D for 500 and M for 1000. 
In Roman numerals, to create a number like 11 you simply add a 1 after the 10, so you get XI. 
But to create a number like 19, you use the subtraction notation which is to add an I before an X or V (or add an X before an L or C). 
So 19 in Roman numerals is XIX.

The goal of your program is to return the decimal equivalent of the Roman numeral given. 
For example: if str is "XXIV" your program should return 24.

Sample test cases:

Input:  "IV"
Output: 4

Input:  "XLVI"
Output: 46
*/

#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>

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

string BasicRomanNumerals(string str) {

  str = trim(str);

  size_t number{};

  const size_t str_len { str.length() };

  for (char& ch : str) ch = static_cast<char>(toupper(ch));

  const unordered_map<string, size_t> rn { {"M", 1000u}, {"D", 500u}, {"C", 100u}, {"L", 50u}, {"X", 10u}, {"V", 5u}, {"I", 1u}, 
                                                 {"IV", 4u}, {"IX", 9u}, {"XL", 40u}, {"XC", 90u} };
  for (size_t i{}; i < str_len; i++) {

    const size_t len { i < (str_len - 1) ? 2u : 1u };
    
    string key { str.substr(i, len) };

    if (rn.find(key) != end(rn)) {
      number += rn.find(key)->second; // number += (*rn.find(key)).second;
      i++;
      continue;
    }

    key.erase(1u, 1u);

    if (rn.find(key) != end(rn)) {
      number += rn.find(key)->second; // number += (*rn.find(key)).second;
    }

  } 

  return to_string(number);

}

int main() { 
  
  // cout << BasicRomanNumerals(move(string{gets(stdin)}));
  cout << BasicRomanNumerals(move(string{"XI"})) << '\n';    // expected output: 11
  cout << BasicRomanNumerals(move(string{"XIX"})) << '\n';   // expected output: 19
  cout << BasicRomanNumerals(move(string{"XXIV"})) << '\n';  // expected output: 24
  cout << BasicRomanNumerals(move(string{"IV"})) << '\n';    // expected output: 4
  cout << BasicRomanNumerals(move(string{"XLVI"})) << '\n';  // expected output: 46

  return 0;
    
}
