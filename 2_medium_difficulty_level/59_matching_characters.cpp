/*
Coderbyte coding challenge: Matching Characters

Using the C++ language, have the function MatchingCharacters(str) take the str parameter being passed and determine the largest number of unique characters 
that exists between a pair of matching letters anywhere in the string. For example: if str is "ahyjakh" then there are only two pairs of matching letters, 
the two a's and the two h's. Between the pair of a's there are 3 unique characters: h, y, and j. Between the h's there are 4 unique characters: y, j, a, and k. 
So for this example your program should return 4.

Another example: if str is "ghececgkaem" then your program should return 5 because the most unique characters exists within the farthest pair of e characters. 
The input string may not contain any character pairs, and in that case your program should just return 0. 
The input will only consist of lowercase alphabetic characters.

Sample test cases:

Input:  "mmmerme"
Output: 3

Input:  "abccdefghi"
Output: 0
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

pair<size_t, size_t> find_max_distance_between_pairs_of_characters(const string& str, const char ch) {

	const size_t first_pos { str.find(ch) };

	if (string::npos == first_pos) return make_pair(string::npos, string::npos);

	const size_t last_pos { str.rfind(ch) };

	if (first_pos == last_pos) return make_pair(string::npos, string::npos);

	return make_pair(first_pos, last_pos);
}

string MatchingCharacters(string str) {

	unordered_set<char> characters_already_processed{};
	vector<pair<char, size_t>> unique_character_count{};

	for (const char ch : str) {

		if (characters_already_processed.find(ch) != end(characters_already_processed)) continue;

		characters_already_processed.insert(ch);

		const pair<size_t, size_t> max_character_distance { find_max_distance_between_pairs_of_characters(str, ch) };

		if (string::npos == max_character_distance.first) continue;

		if ((max_character_distance.second - max_character_distance.first) == 1u) continue;

		unordered_set<char> unique_characters{};
		
		size_t unique_ch_count{};

		for (size_t i{max_character_distance.first + 1u}; i < max_character_distance.second; i++) {

			if (unique_characters.find(str[i]) == end(unique_characters)) {
				unique_characters.insert(str[i]);
				unique_ch_count++;
			}			

		}

		unique_character_count.emplace_back(make_pair(ch, unique_ch_count));		

	}

	sort(begin(unique_character_count), end(unique_character_count), [&](const pair<char, size_t>& lp, const pair<char, size_t>& rp) {
		return (lp.second > rp.second);
	});

	if (unique_character_count.empty()) return "0";
 
  	return to_string(unique_character_count[0].second); 

}

int main() { 
  
  // cout << MatchingCharacters(gets(stdin));
  cout << MatchingCharacters(move(string{"ahyjakh"})) << '\n';     // expected output: 4
  cout << MatchingCharacters(move(string{"ghececgkaem"})) << '\n'; // expected output: 5
  cout << MatchingCharacters(move(string{"mmmerme"})) << '\n';     // expected output: 3
  cout << MatchingCharacters(move(string{"abccdefghi"})) << '\n';  // expected output: 0  
  return 0;    
}
