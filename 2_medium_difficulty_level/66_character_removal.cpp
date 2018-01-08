/*
Coderbyte coding challenge: Character Removal

Using the C++ language, have the function CharacterRemoval(strArr[]) read the array of strings stored in strArr, which will contain 2 elements: 
the first element will be a sequence of characters representing a word, and the second element will be a long string of comma-separated words, 
in alphabetical order, that represents a dictionary of some arbitrary length. For example: strArr can be: ["worlcde", "apple,bat,cat,goodbye,hello,yellow,why,world"]. 
Your goal is to determine the minimum number of characters, if any, can be removed from the word so that it matches one of the words from the dictionary. 
In this case, your program should return 2 because once you remove the characters "c" and "e" you are left with "world" and that exists within the dictionary. 
If the word cannot be found no matter what characters are removed, return -1.

Sample test cases:

Input:  "baseball", "a,all,b,ball,bas,base,cat,code,d,e,quit,z"
Output: 4

Input:  "apbpleeeef", "a,ab,abc,abcg,b,c,dog,e,efd,zzzz"
Output: 8
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
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

vector<string> split(const string& source, const char* needle, size_t const max_count = string::npos)
{
  vector<string> parts{}; 

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len)) return parts;

  size_t number_of_parts{}, prev{};

  while (true)
  {
    const size_t current = source.find(needle_st, prev);

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

size_t find_min_number_of_character_differences(const string& target_word, const unordered_map<char, int>& target_word_char_freq, const string& dict_word) {

	if (target_word.find(dict_word) != string::npos) {
		return (target_word.length() - dict_word.length());
	}


	unordered_set<char> dict_word_processed_chars{};

	size_t prev_ch_pos{string::npos}, current_ch_pos;

	for (const char ch : dict_word) {

		if (string::npos == prev_ch_pos) { 
			prev_ch_pos = target_word.find(ch);
			if (string::npos == prev_ch_pos) return string::npos;
		} else {
			current_ch_pos = target_word.find(ch, prev_ch_pos + 1);
			if (string::npos == current_ch_pos) return string::npos;
			prev_ch_pos = current_ch_pos;
		}
		
		if (dict_word_processed_chars.find(ch) == end(dict_word_processed_chars)) {
			
			const auto ch_count = count(begin(dict_word), end(dict_word), ch);
			
			if (target_word_char_freq.find(ch) == end(target_word_char_freq)) return string::npos;
			
			else if (target_word_char_freq.find(ch)->second < ch_count) return string::npos;
			
			dict_word_processed_chars.insert(ch);
		
		}
	}

	return (target_word.length() - dict_word.length());
}

string CharacterRemoval(string* str_arr, const size_t str_arr_size) { 

   if (2u != str_arr_size) return "-1";

   const string target_word { trim(str_arr[0]) };

   vector<string> dict_words = split(str_arr[1], ",");

   for (string& dict_word : dict_words) dict_word = trim(dict_word);

   unordered_map<char, int> target_word_char_freq{};

	for (const char ch : target_word) {
		
		if (target_word_char_freq.find(ch) == end(target_word_char_freq)) {
			
			const auto ch_count = count(begin(target_word), end(target_word), ch);

			target_word_char_freq.insert(make_pair(ch, ch_count));

		}
	}

   set<size_t> minimum_characters_to_remove{};	

   for (const string& dict_word : dict_words) {

   	const size_t diff { find_min_number_of_character_differences(target_word, target_word_char_freq, dict_word) };

   	if (string::npos != diff) minimum_characters_to_remove.insert(diff);

   }

   if (minimum_characters_to_remove.empty()) return "-1";

   return to_string(*begin(minimum_characters_to_remove));      
}

int main() { 
   
  // string A[] = gets(stdin);
  // cout << CharacterRemoval(A, sizeof(A)/sizeof(*A));
  string B[] = {"worlcde", "apple,bat,cat,goodbye,hello,yellow,why,world"};
  cout << CharacterRemoval(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "2"
  string C[] = {"baseball", "a,all,b,ball,bas,base,cat,code,d,e,quit,z"};
  cout << CharacterRemoval(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "4"
  string D[] = {"apbpleeeef", "a,ab,abc,abcg,b,c,dog,e,efd,zzzz"};
  cout << CharacterRemoval(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "8"
  string E[] = {"wrdlmaeo", "a,b,c,d,ap,apple,bar,bat,cat,hello,y,yellow,w,wo,world,worr"};
  cout << CharacterRemoval(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: "6"

  return 0;    

}
