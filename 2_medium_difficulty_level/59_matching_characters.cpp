/*
Coderbyte coding challenge: Matching Characters

Using the C++ language, have the function MatchingCharacters(str) take the str
parameter being passed and determine the largest number of unique characters
that exists between a pair of matching letters anywhere in the string. For
example: if str is "ahyjakh" then there are only two pairs of matching letters,
the two a's and the two h's. Between the pair of a's there are 3 unique
characters: h, y, and j. Between the h's there are 4 unique characters: y, j, a,
and k. So for this example your program should return 4.

Another example: if str is "ghececgkaem" then your program should return 5
because the most unique characters exists within the farthest pair of e
characters. The input string may not contain any character pairs, and in that
case your program should just return 0. The input will only consist of lowercase
alphabetic characters.

Sample test cases:

Input:  "mmmerme"
Output: 3

Input:  "abccdefghi"
Output: 0
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

pair<size_t, size_t> find_first_and_last_position_of_specified_char(
    const string& str,
    const char ch) {
  return {str.find(ch), str.rfind(ch)};
}

string MatchingCharacters(string str) {
  unordered_set<char> already_visited{};
  size_t max_unique_character_count{};

  for (const char ch : str) {
    if (already_visited.count(ch))
      continue;

    already_visited.insert(ch);

    const pair<size_t, size_t> max_character_distance{
        find_first_and_last_position_of_specified_char(str, ch)};

    if (max_character_distance.second - max_character_distance.first <= 1)
      continue;

    unordered_set<char> unique_characters{};

    size_t unique_ch_count{};

    for (size_t i{max_character_distance.first + 1};
         i < max_character_distance.second; i++) {
      if (!unique_characters.count(str[i])) {
        unique_characters.insert(str[i]);
        unique_ch_count++;
      }
    }

    if (unique_ch_count > max_unique_character_count)
      max_unique_character_count = unique_ch_count;
  }

  return to_string(max_unique_character_count);
}

int main() {
  // cout << MatchingCharacters(gets(stdin));
  cout << MatchingCharacters(move(string{"ahyjakh"}))
       << '\n';  // expected output: 4
  cout << MatchingCharacters(move(string{"ghececgkaem"}))
       << '\n';  // expected output: 5
  cout << MatchingCharacters(move(string{"mmmerme"}))
       << '\n';  // expected output: 3
  cout << MatchingCharacters(move(string{"abccdefghi"}))
       << '\n';  // expected output: 0
  return 0;
}
