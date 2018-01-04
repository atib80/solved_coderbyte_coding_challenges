/*
Coderbyte coding challenge: Letter Capitalize

Using the C++ language, have the function LetterCapitalize(str) take the str parameter being passed and capitalize the first letter of each word. 
Words will be separated by only one space.

Sample test cases:

Input:  "hello world"
Output: "Hello World"

Input:  "i ran there"
Output: "I Ran There"
*/

#include <iostream>
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

string LetterCapitalize(string str) {

    str = trim(str);
    
    bool is_space_char{true};
    
    for (auto& ch : str) {
        
        if (ch == ' ') {
            is_space_char = true;
            continue;
        }
        
        if (is_space_char) {
            ch = static_cast<char>(toupper(ch));
            is_space_char = false;
        }
    }
 
  return str; 
            
}

int main() {

  // cout << LetterCapitalize(move(string{gets(stdin)}));
  cout << LetterCapitalize(move(string{"hello world"})) << '\n'; // expected output: "Hello World"
  cout << LetterCapitalize(move(string{"i ran there"})) << '\n'; // expected output: "I Ran There"  
  return 0;    
}
