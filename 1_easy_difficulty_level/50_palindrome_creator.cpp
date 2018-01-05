/*
Coderbyte coding challenge: Palindrome Creator

Have the function PalindromeCreator(str) take the str parameter being passed and determine if it is possible to create a palindromic string of at least 3 characters
by removing 1 or 2 characters. For example: if str is "abjchba" then you can remove the characters jc to produce "abhba" which is a palindrome. 
For this example your program should return the two characters that were removed with no delimiter and in the order they appear in the string, so jc. 
If 1 or 2 characters cannot be removed to produce a palindrome, then return the string not possible. 
If the input string is already a palindrome, your program should return the string palindrome.

The input will only contain lowercase alphabetic characters. 
Your program should always attempt to create the longest palindromic substring by removing 1 or 2 characters (see second sample test case as an example). 
The 2 characters you remove do not have to be adjacent in the string.

Sample test cases:

Input:  "mmop"
Output: "not possible"

Input:  "kjjjhjjj"
Output: "k"
*/

#include <iostream>
#include <cctype>
#include <string>
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


bool is_palindrome(const string& str) {

	string reversed_str{str};
	reverse(begin(reversed_str), end(reversed_str));
	return (str == reversed_str);

}

string PalindromeCreator(string str) {

  str = trim(str);

  if (is_palindrome(str)) return string{"palindrome"};

  const size_t str_len { str.length() };  

  for (size_t i{}; i < str_len; i++) { 

    const string needle{str[i]};

    str.erase(i, 1u);

    if (is_palindrome(str)) return needle;

    str.insert(i, needle);

  }

  if (str_len < 5u) return string{"not possible"}; // if str's length is less than 5 then we are allowed to remove only 1 character from it at a time.

  for (size_t i{}; i < str_len - 1u; i++)	 {

  	for (size_t j{i + 1u}; j < str_len; j++) {

  		const string needle{str[i], str[j]};

      string palindromic_str{str};
  		palindromic_str.erase(i, 1u);
      palindromic_str.erase(j - 1, 1u);

  		if (is_palindrome(palindromic_str)) return needle;

  	}

  }

  return string{"not possible"}; 
            
}

int main() {

  // cout << PalindromeCreator(move(string{gets(stdin)}));
  cout << PalindromeCreator(move(string{"abjchba"})) << '\n';      // "jc"
  cout << PalindromeCreator(move(string{"mmop"})) << '\n';         // "not possible"
  cout << PalindromeCreator(move(string{"kjjjhjjj"})) << '\n';     // "k"
  cout << PalindromeCreator(move(string{"vhhgghhgghhk"})) << '\n'; // "vk"
  return 0;    
} 
