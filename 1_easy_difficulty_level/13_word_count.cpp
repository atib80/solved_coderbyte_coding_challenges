/*
Coderbyte coding challenge: Word Count

Using the C++ language, have the function WordCount(str) take the str string parameter being passed and return the number of words the string contains 
(e.g. "Never eat shredded wheat or cake" would return 6). Words will be separated by single spaces.

Sample test cases:

Input:  "Hello World"
Output: 2

Input:  "one 22 three"
Output: 3
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str)
{
    const size_t str_len{ str.length() };

    if (!str_len)
        return string{};

    size_t first{}, last{ str_len - 1 };

    for (; first <= last; ++first) {
        if (!isspace(str[first]))
            break;
    }

    if (first > last)
        return string{};

    for (; last > first; --last) {
        if (!isspace(str[last]))
            break;
    }

    return str.substr(first, last - first + 1);
}

vector<string> split(const string& source,
    const char* needle,
    size_t const max_count = string::npos)
{
    vector<string> parts{};

    string needle_st{ needle };

    const size_t source_len{ source.length() };

    const size_t needle_len{ needle_st.size() };

    if (!source_len)
        return parts;

    if (!needle_len) {
        const size_t upper_limit{ max_count < source_len ? max_count : source_len };
        for (size_t i{}; i < upper_limit; i++)
            parts.emplace_back(1, source[i]);
        return parts;
    }

    size_t number_of_parts{}, prev{};

    while (true) {
        const size_t current{ source.find(needle_st, prev) };

        if (string::npos == current)
            break;

        number_of_parts++;

        if ((string::npos != max_count) && (parts.size() == max_count))
            break;

        if ((current - prev) > 0)
            parts.emplace_back(source.substr(prev, current - prev));

        prev = current + needle_len;

        if (prev >= source_len)
            break;
    }

    if (prev < source_len) {
        if (string::npos == max_count)
            parts.emplace_back(source.substr(prev));

        else if ((string::npos != max_count) && (parts.size() < max_count))
            parts.emplace_back(source.substr(prev));
    }

    return parts;
}

string word_count(string str) {

  str = trim(str);

  const vector<string> words = split(str, " ");

  return to_string(words.size()); 
            
}

int main() { 
  // cout << word_count(move(string{gets(stdin)}));
  cout << word_count(move(string{"Never eat shredded wheat or cake"})) << '\n'; // expected output: 6 
  cout << word_count(move(string{"Hello World"})) << '\n';            // expected output: 2
  cout << word_count(move(string{"one 22 three"})) << '\n';             // expected output: 3
  cout << word_count(move(string{"Coderbyte"})) << '\n';                // expected output: 1
  cout << word_count(move(string{"h333llLo"})) << '\n';                 // expected output: 1
  cout << word_count(move(string{"Yo0"})) << '\n';                // expected output: 1
  cout << word_count(move(string{"commacomma!"})) << '\n';            // expected output: 1
  cout << word_count(move(string{"aq"})) << '\n';               // expected output: 1
  
  return 0;    
} 
