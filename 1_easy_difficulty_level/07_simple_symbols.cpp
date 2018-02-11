/*
Coderbyte coding challenge: Simple Symbols

Using the C++ language, have the function SimpleSymbols(str) take the str parameter being passed and determine if it is an acceptable sequence 
by either returning the string true or false. The str parameter will be composed of + and = symbols with several letters between them (ie. ++d+===+c++==a) 
and for the string to be true each letter must be surrounded by a + symbol. So the string to the left would be false. 
The string will not be empty and will have at least one letter.

Sample test cases:

Input:  "+d+=3=+s+"
Output: "true"

Input:  "f++d+"
Output: "false"
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string trim(const string& str)
{
  
  const size_t str_len{str.length()};

  if (0u == str.length()) return string{};

  size_t begin_str{};
  size_t end_str{str_len - 1};  

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

string SimpleSymbols(string str) {
    
  str = trim(str);
   
  for (auto& ch : str) ch = static_cast<char>(tolower(ch));
    
  if ((str[0] >= 'a') && (str[0] <= 'z')) return "false";

  if ((str[str.length() - 1] >= 'a') && (str[str.length() - 1] <= 'z')) return "false";

  for (size_t i{}; i < str.length() - 2; i++) {

      if (str[i] == '+') {

          if ((str[i+1] >= 'a') && (str[i+1] <= 'z')) {

              if (str[i+2] == '+') continue;              

              else return "false";
          }

        } else if (str[i] == '=') {

          if ((str[i+1] >= 'a') && (str[i+1] <= 'z')) return "false";

        }
    
    }
  
    return "true";
}

int main() { 
  
  // cout << SimpleSymbols(move(string{gets(stdin)}));
  cout << SimpleSymbols(move(string{"++d+===+c++==a"})) << '\n'; // expected output: "false"
  cout << SimpleSymbols(move(string{"+d+=3=+s+"})) << '\n';      // expected output: "true"
  cout << SimpleSymbols(move(string{"f++d+"})) << '\n';          // expected output: "false"

  return 0;      
}
