/*
Coderbyte coding challenge: Three Numbers

Using the C++ language, have the function ThreeNumbers(str) take the str
parameter being passed and determine if exactly three unique, single-digit
integers occur within each word in the string. The integers can appear anywhere
in the word, but they cannot be all adjacent to each other. If every word
contains exactly 3 unique integers somewhere within it, then return the string
true, otherwise return the string false. For example: if str is "2hell6o3
wor6l7d2" then your program should return "true" but if the string is "hell268o
w6or2l4d" then your program should return "false" because all the integers are
adjacent to each other in the first word.

Sample test cases:

Input:  "2a3b5 w1o2rl3d g1gg92"
Output: "true"

Input:  "21aa3a ggg4g4g6ggg"
Output: "false"
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

  output.erase(find_if(rbegin(output), rend(output),
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

string ThreeNumbers(string str) {
  str = trim(str);

  const vector<string> words{split(str, " ")};

  for (const auto& word : words) {
    if (word.length() < 4)
      return "false";

    const auto digit_count = count_if(begin(word), end(word),
                                      [](const int ch) { return isdigit(ch); });

    if (3 != digit_count)
      return "false";

    const size_t first_digit_pos{word.find_first_of("0123456789")};
    const size_t last_digit_pos{word.find_last_of("0123456789")};

    unordered_set<char> unique_digits{};
    vector<size_t> digit_positions{};

    unique_digits.insert(word[first_digit_pos]);
    digit_positions.emplace_back(first_digit_pos);

    unique_digits.insert(word[last_digit_pos]);
    digit_positions.emplace_back(last_digit_pos);

    for (size_t i{first_digit_pos + 1}; i < last_digit_pos; i++) {
      if (isdigit(word[i])) {
        unique_digits.insert(word[i]);
        digit_positions.emplace_back(i);
        break;
      }
    }

    if (3 != unique_digits.size())
      return "false";

    sort(begin(digit_positions), end(digit_positions));

    if ((digit_positions[1] - digit_positions[0] == 1) &&
        (digit_positions[2] - digit_positions[1] == 1) &&
        (digit_positions[2] - digit_positions[0] == 2))
      return "false";
  }

  return "true";
}

int main() {
  // cout << ThreeNumbers(move(string{gets(stdin)}));
  cout << ThreeNumbers(move(string{"2hell6o3 wor6l7d2"}))
       << '\n';  // expected output: "true"
  cout << ThreeNumbers(move(string{"hell268o w6or2l4d"}))
       << '\n';  // expected output: "false"
  cout << ThreeNumbers(move(string{"2a3b5 w1o2rl3d g1gg92"}))
       << '\n';  // expected output: "true"
  cout << ThreeNumbers(move(string{"21aa3a ggg4g4g6ggg"}))
       << '\n';  // expected output: "false"
  return 0;
}
