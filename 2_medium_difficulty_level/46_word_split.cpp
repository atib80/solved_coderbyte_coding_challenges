/*
Coderbyte coding challenge: Word Split

Using the C++ language, have the function WordSplit(strArr) read the array of strings stored in strArr, which will contain 2 elements: 
the first element will be a sequence of characters, and the second element will be a long string of comma-separated words, in alphabetical order, 
that represents a dictionary of some arbitrary length. For example: strArr can be: ["hellocat", "apple,bat,cat,goodbye,hello,yellow,why"]. 
Your goal is to determine if the first element in the input can be split into two words, where both words exist in the dictionary 
that is provided in the second input. In this example, the first element can be split into two words: 
hello and cat because both of those words are in the dictionary.

Your program should return the two words that exist in the dictionary separated by a comma. So for the example above, your program should return hello,cat. 
There will only be one correct way to split the first element of characters into two words. If there is no way to split string into two words 
that exist in the dictionary, return the string not possible. The first element itself will never exist in the dictionary as a real word.

Sample test cases:

Input:  "baseball", "a,all,b,ball,bas,base,cat,code,d,e,quit,z"
Output: "base,ball"

Input:  "abcgefd", "a,ab,abc,abcg,b,c,dog,e,efd,zzzz"
Output: "abcg,efd"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
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

std::vector<string> split(const string& source, const char* needle, const size_t max_count = string::npos)
{
	std::vector<string> parts{};			

	string needle_st{needle};

	const size_t source_len{source.length()};
	const size_t needle_len{needle_st.length()};

	if ((0u == source_len) || (0u == needle_len)) return parts;

	size_t number_of_parts{}, prev{};

	while (true)
	{
		const size_t current { source.find(needle_st, prev) };

		if (string::npos == current) break;

		number_of_parts++;

		if ((string::npos != max_count) && (parts.size() == max_count)) break;

		if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source_len) break;
	}

	if (prev < source_len)
	{
		if (string::npos == max_count) parts.emplace_back(source.substr(prev));

		else if ((string::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
	}

	return parts;
}

string WordSplit(string* str_arr, const size_t str_arr_size) {

  if (str_arr_size < 2u) return "not possible"; 

  const string tw { trim(str_arr[0]) };
  const size_t tw_len { tw.length() };
  const char tw_fc { tw.front() };
  const char tw_lc { tw.back() };

  str_arr[1] = trim(str_arr[1]);

  vector<string> words = split(str_arr[1], ",");

  unordered_map<string, size_t> first_word_dict{};
  unordered_map<string, size_t> second_word_dict{};

  for (const auto& w : words) {
  	const size_t w_len { w.length() };  	
  	if ( w_len >= tw_len ) continue;
  	if ( ( tw_fc == w.front() ) && ( tw.substr(0, w_len) == w ) ) first_word_dict.insert(make_pair(w, w_len));
  	if ( ( tw_lc == w.back() ) && ( tw.substr(tw_len - w_len) == w) ) second_word_dict.insert(make_pair(w, w_len));
  }
  
  for (const auto& first_dict_pair : first_word_dict) {

  	for (const auto& second_dict_pair : second_word_dict) {

  		if ( ( first_dict_pair.second + second_dict_pair.second ) != tw_len ) continue;

  		if ( ( first_dict_pair.first + second_dict_pair.first ) == tw ) 
  		    return string{first_dict_pair.first + "," + second_dict_pair.first};
  	}

  }

  return "not possible";            
}

int main() {   
    
  // string A[] = gets(stdin);
  // cout << WordSplit(A, sizeof(A)/sizeof(A[0]));
  string B[] = {"hellocat", "apple,bat,cat,goodbye,hello,yellow,why"};
  cout << WordSplit(B, sizeof(B)/sizeof(B[0])) << '\n'; // expected output: "hello,cat"
  string C[] = {"baseball", "a,all,b,ball,bas,base,cat,code,d,e,quit,z"};
  cout << WordSplit(C, sizeof(C)/sizeof(C[0])) << '\n'; // expected output: "base,ball"
  string D[] = {"abcgefd", "a,ab,abc,abcg,b,c,dog,e,efd,zzzz"};
  cout << WordSplit(D, sizeof(D)/sizeof(D[0])) << '\n'; // expected output: "abcg,efd"
  
  return 0;

}
