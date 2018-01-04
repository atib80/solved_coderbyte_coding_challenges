/*
Coderbyte coding challenge: AB Check

Using the C++ language, have the function ABCheck(str) take the str parameter being passed and return the string true if the characters a and b are separated 
by exactly 3 places anywhere in the string at least once (ie. "lane borrowed" would result in true because there is exactly three characters between a and b). 
Otherwise return the string false.

Sample test cases:

Input:  "after badly"
Output: "false"

Input:  "Laura sobs"
Output: "true"
*/

#include <iostream>
#include <string>
#include <vector>
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

string ABCheck(string str) {

  vector<int> a_positions{};
  vector<int> b_positions{};

  str = trim(str);

  const int str_len{static_cast<int>(str.length())};

  for (int i{}; i < str_len; i++) {
  	
  	if ('a' == str[i]) a_positions.emplace_back(i); 
  	else if ('b' == str[i]) b_positions.emplace_back(i); 	

  }

  for (const int a_pos : a_positions) {

  	for (const int b_pos : b_positions) {

  		if ((b_pos - a_pos) == 4) return string{"true"};

  		if (a_pos < (b_pos - 4)) break;  		

  	}

  }

  for (const int b_pos : b_positions) {

  	for (const int a_pos : a_positions) {

  		if ((a_pos - b_pos) == 4) return string{"true"};

  		if (b_pos < (a_pos - 4)) break; 		

  	}

  }

  return string{"false"}; 
            
}

int main() { 
  
  // cout << ABCheck(move(string{gets(stdin)}));
  cout << ABCheck(move(string{"lane borrowed"})) << '\n'; // expected output: "true"
  cout << ABCheck(move(string{"after badly"})) << '\n';   // expected output: "false"
  cout << ABCheck(move(string{"Laura sobs"})) << '\n';    // expected output: "true"
  return 0;    
}
