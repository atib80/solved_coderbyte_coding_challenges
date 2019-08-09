/*
Coderbyte coding challenge: Vowel Count

Using the C++ language, have the function VowelCount(str) take the str string
parameter being passed and return the number of vowels the string contains (ie.
"All cows eat grass and moo" would return 8). Do not count y as a vowel for this
challenge.

Sample test cases:

Input:  "hello"
Output: 2

Input:  "coderbyte"
Output: 3
*/

#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (0U == str_len)
    return {};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return {};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str]))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string int2str(long long number) {
  static char buffer[16]{};
  const bool is_negative{number < 0};

  size_t index{};

  while (number) {
    buffer[index++] = '0' + number % 10;
    number /= 10;
  }

  if (is_negative)
    buffer[index++] = '-';

  std::reverse(buffer, buffer + index);
  return string{buffer, buffer + index};
}

string vowel_count_v1(string str) {
  const unordered_set<char> vowels{'A', 'E', 'I', 'O', 'U',
                                   'a', 'e', 'i', 'o', 'u'};

  str = trim(str);
  size_t v_count{};

  for (const auto ch : str) {
    if (vowels.find(ch) != cend(vowels))
      v_count++;
  }

  return int2str(v_count);
}

template <size_t BUFFER_LENGTH>
class vowel_indices {
  int vowels[BUFFER_LENGTH];

 public:
  constexpr vowel_indices() : vowels{} {
    for (const char index : "aeiouAEIOU")
      vowels[static_cast<size_t>(index)] = 1;
  }

  int operator[](const size_t index) const {
    if (index < BUFFER_LENGTH)
      return vowels[index];
    static char buffer[128]{};
    snprintf(buffer, 128, "index's value must be between 0 and %lu!",
             BUFFER_LENGTH);
    throw out_of_range{buffer};
  }
};

static constexpr vowel_indices<128> char_dict{};

string vowel_count_v2(string str) {
  str = trim(str);
  size_t v_count{};

  for (const auto ch : str) {
    if (char_dict[ch])
      v_count++;
  }

  return int2str(v_count);
}

int main() {
  // cout << vowel_count_v2(gets(stdin));
  cout << vowel_count_v2("All cows eat grass and moo")
       << '\n';                                 // expected output: 8
  cout << vowel_count_v2("hello") << '\n';      // expected output: 2
  cout << vowel_count_v2("coderbyte") << '\n';  // expected output: 3
  cout << vowel_count_v2(
              "Today is a perfect day for taking a long walk and finding a "
              "good spot for swimming.")
       << '\n';  // expected output: 23

  return 0;
}
