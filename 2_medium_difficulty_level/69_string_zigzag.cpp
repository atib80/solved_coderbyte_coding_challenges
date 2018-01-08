/*
Coderbyte coding challenge: String Zigzag

Using the C++ language, have the function StringZigzag(strArr) read the array of strings stored in strArr, which will contain two elements, 
the first some sort of string and the second element will be a number ranging from 1 to 6. 
The number represents how many rows to print the string on so that it forms a zig-zag pattern. 
For example: if strArr is ["coderbyte", "3"] then this word will look like the following if you print it in a zig-zag pattern with 3 rows:

Your program should return the word formed by combining the characters as you iterate through each row, 
so for this example your program should return the string creoebtdy.

Sample test cases:

Input:  "cat", "5"
Output: "cat"

Input:  "kaamvjjfl", "4"
Output: "kjajfavlm"
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
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

string StringZigzag(string* str_arr, const size_t str_arr_size) {

  if (str_arr_size < 2u) return "not possible"; 

  const string sentence { trim(str_arr[0]) };
  const size_t row_count { stoul(trim(str_arr[1])) };

  if (1u == row_count) return sentence;

  const char first_char { sentence[0] };

  if (all_of(begin(sentence), end(sentence), [&first_char](const char ch) { return (ch == first_char); } )) return sentence;

  vector<vector<char>> zigzag(row_count, vector<char>{});  

  string result{};

  int increment{1};

  for (size_t i{}, row{}; i < sentence.length(); i++, row += increment) {

  	zigzag[row].emplace_back(sentence[i]);
  	if (i && !row) increment = -increment;  	
  	else if ((row_count - 1) == row) increment = -increment;
  }

  for (size_t i{}; i != zigzag.size(); i++) {
  	for (size_t j{}; j != zigzag[i].size(); j++) {
  		if (!zigzag[i][j]) break;
  		result.push_back(zigzag[i][j]);
  	}
  }

  return result;
}

int main() { 
   
  // string A[] = gets(stdin);
  // cout << StringZigzag(A, sizeof(A)/sizeof(*A));
  string B[] = {"coderbyte", "3"};
  cout << StringZigzag(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "creoebtdy"
  string C[] = {"cat", "5"};
  cout << StringZigzag(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "cat"
  string D[] = {"kaamvjjfl", "4"};
  cout << StringZigzag(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "kjajfavlm"
  string E[] = {"abcdefghijklm", "2"};
  cout << StringZigzag(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: "acegikmbdfhjl"
  string F[] = {"aeettym", "1"};
  cout << StringZigzag(F, sizeof(F)/sizeof(*F)) << '\n'; // expected output: "aeettym"
  string G[] = {"aaaaaaaaaaaaaaaaaaaa", "4"};
  cout << StringZigzag(G, sizeof(G)/sizeof(*G)) << '\n'; // expected output: "aaaaaaaaaaaaaaaaaaaa"
  string H[] = {"ababababababa", "2"};
  cout << StringZigzag(H, sizeof(H)/sizeof(*H)) << '\n'; // expected output: "aaaaaaabbbbbb"

  return 0;    
}
