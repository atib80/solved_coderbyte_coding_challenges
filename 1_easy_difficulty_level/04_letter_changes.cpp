/*
Coderbyte coding challenge: Letter Changes

Using the C++ language, have the function LetterChanges(str) take the str parameter being passed and modify it using the following algorithm. 
Replace every letter in the string with the letter following it in the alphabet (ie. c becomes d, z becomes a). 
Then capitalize every vowel in this new string (a, e, i, o, u) and finally return this modified string.

Sample test cases:

Input:  "hello*3"
Output: "Ifmmp*3"

Input:  "fun times!"
Output: "gvO Ujnft!"
*/

#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>
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

string LetterChanges(string str) {

  str = trim(str);

  const unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
  
  for (auto& ch : str) {
      if (((ch >= 'a') && (ch < 'z')) || ((ch >= 'A') && (ch < 'Z'))) { 
          ch += 1;
      }
      else if (ch == 'z') { 
          ch = 'a';
      }
      else if (ch == 'Z') { 
          ch = 'A';
      }
  }
  
  string final_str{str};
  
  transform(begin(str), end(str), begin(final_str), [&](const char ch) {
      if (vowels.find(ch) != end(vowels)) return static_cast<char>(toupper(ch));
      return ch;
  });
   
  return final_str; 
            
}

int main() { 
  
  cout << LetterChanges(move(string{gets(stdin)}));
  // cout << LetterChanges(move(string{"hello*3"})) << '\n';    // expected output: "Ifmmp*3"
  // cout << LetterChanges(move(string{"fun times!"})) << '\n'; // expected output: "gvO Ujnft!"
  return 0;    
}
