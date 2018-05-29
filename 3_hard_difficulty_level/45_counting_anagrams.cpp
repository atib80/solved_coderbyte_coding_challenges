/*
Coderbyte coding challenge: Counting Anagrams

Using the C++ language, have the function CountingAnagrams(str) take the str
parameter and determine how many anagrams exist in the string. An anagram is a
new word that is produced from rearranging the characters in a different word,
for example: cars and arcs are anagrams. Your program should determine how many
anagrams exist in a given string and return the total number. For example: if
str is "cars are very cool so are arcs and my os" then your program should
return 2 because "cars" and "arcs" form 1 anagram and "so" and "os" form a 2nd
anagram. The word "are" occurs twice in the string but it isn't an anagram
because it is the same word just repeated. The string will contain only spaces
and lowercase letters, no punctuation, numbers, or uppercase letters.

Sample test cases:

Input:  "aa aa odg dog gdo"
Output: 2

Input:  "a c b c run urn urn"
Output: 1
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.length()};

  if (!source_len)
    return parts;

  if (!needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if (string::npos != max_count && parts.size() == max_count)
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

size_t count_number_of_anagrams_in_str(string sentence) {
  size_t number_of_anagrams{};

  const vector<string> words{split(sentence, " ")};
  const size_t number_of_words{words.size()};

  unordered_set<size_t> ignore_indices{};

  for (size_t i{}; i < number_of_words; i++) {
    if (ignore_indices.count(i))
      continue;

    const string& word{words[i]};
    const size_t word_len{word.length()};
    ignore_indices.insert(i);

    unordered_set<string> found_anagram_words{};

    for (size_t j{}; j < number_of_words; j++) {
      if (ignore_indices.count(j) || word_len != words[j].length() ||
          word == words[j] || found_anagram_words.count(words[j]))
        continue;

      if (is_permutation(begin(words[j]), end(words[j]), begin(word))) {
        number_of_anagrams++;
        found_anagram_words.insert(words[j]);
        ignore_indices.insert(j);
      }
    }
  }

  return number_of_anagrams;
}

string CountingAnagrams(string sentence) {
  sentence = trim(sentence);

  return to_string(count_number_of_anagrams_in_str(move(sentence)));
}

int main() {
  // cout << CountingAnagrams(move(string{ gets(stdin) }));
  cout << CountingAnagrams(string{"cars are very cool so are arcs and my os"})
       << '\n';  // expected output: "2"
  cout << CountingAnagrams(string{"aa aa odg dog gdo"})
       << '\n';  // expected output: "2"
  cout << CountingAnagrams(string{"a c b c run urn urn"})
       << '\n';  // expected output: "1"

  return 0;
}
