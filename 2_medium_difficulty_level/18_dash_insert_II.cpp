/*
Coderbyte coding challenge: Dash Insert II

Using the C++ language, have the function DashInsertII(str) insert dashes ('-') between each two odd numbers and insert asterisks ('*') 
between each two even numbers in str. 
For example: if str is 4546793 the output should be 454*67-9-3. Don't count zero as an odd or even number.

Sample test cases:

Input:  "99946"
Output: "9-9-94*6"

Input:  "56647304"
Output: "56*6*47-304"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

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

string DashInsertII(string str) { 

  str = trim(str);

  ostringstream oss{};

  const size_t str_len { str.length() };

  if (str_len < 2u) return str;

  oss << str[0];

  size_t digit { static_cast<size_t>(str[0] - '0') };

  bool is_prev_digit_zero { digit == 0 ? true : false };

  bool is_prev_odd { digit % 2 == 1 ? true : false };

  for (size_t i{1u}; i < str_len; i++) {

    digit = static_cast<size_t>(str[i] - '0');

    if (!is_prev_digit_zero && digit) {

      if (is_prev_odd && (digit % 2 == 1)) {

         oss << '-' << str[i];
      
       } else if (!is_prev_odd && (digit % 2 == 0)) {

         oss << '*' << str[i];

       } else {

         oss << str[i];

       }   
  
    } else {

       oss << str[i];

    }    

    is_prev_digit_zero = digit == 0 ? true : false;
    is_prev_odd = digit % 2 == 1 ? true : false;

  }

  return trim(oss.str());
  
}

int main() { 
  
  // cout << DashInsertII(move(string{gets(stdin)}));
  cout << DashInsertII(move(string{"4546793"})) << '\n';  // expected output: "454*67-9-3"
  cout << DashInsertII(move(string{"99946"})) << '\n';    // expected output: "9-9-94*6"
  cout << DashInsertII(move(string{"56647304"})) << '\n'; // expected output: "56*6*47-304"

  return 0;    
}
