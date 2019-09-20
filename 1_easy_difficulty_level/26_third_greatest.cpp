/*
Coderbyte coding challenge: Third Greatest

Using the C++ language, have the function ThirdGreatest(strArr) take the array
of strings stored in strArr and return the third largest word within it. So for
example: if strArr is ["hello", "world", "before", "all"] your output should be
world because "before" is 6 letters long, and "hello" and "world" are both 5,
but the output should be world because it appeared as the last 5 letter word in
the array. If strArr was ["hello", "world", "after", "all"] the output should be
after because the first three words are all 5 letters long, so return the last
one. The array will have at least three strings and each string will only
contain letters.

Sample test cases:

Input:  "coder","byte","code"
Output: "code"

Input:  "abc","defg","z","hijk"
Output: "abc"
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string ThirdGreatest_v1(vector<string> words) {
  if (words.size() < 3U)
    return "not possible";

  stable_sort(begin(words), end(words), [](const string& lw, const string& rw) {
    return lw.length() > rw.length();
  });

  return move(words[2]);
}

string ThirdGreatest_v2(vector<string> words) {
  const size_t words_len{words.size()};

  if (words_len < 3U)
    return "not possible";

  size_t max_word_len{words.front().length()};
  size_t first_longest_word_index{};

  for (size_t i{1U}; i < words_len; ++i) {
    if (words[i].length() > max_word_len) {
      max_word_len = words[i].length();
      first_longest_word_index = i;
    }
  }

  words[first_longest_word_index].clear();

  max_word_len = 0U;
  size_t second_longest_word_index{};

  for (size_t i{}; i < words_len; ++i) {
    if (words[i].length() > max_word_len) {
      max_word_len = words[i].length();
      second_longest_word_index = i;
    }
  }

  words[second_longest_word_index].clear();

  max_word_len = 0U;
  size_t third_longest_word_index{};

  for (size_t i{}; i < words_len; ++i) {
    if (words[i].length() > max_word_len) {
      max_word_len = words[i].length();
      third_longest_word_index = i;
    }
  }

  return move(words[third_longest_word_index]);
}

int main() {
  // cout << ThirdGreatest_v2(gets(stdin));
  cout << ThirdGreatest_v2({"hello", "world", "before", "all"})
       << '\n';  // expected output: world
  cout << ThirdGreatest_v2({"hello", "world", "after", "all"})
       << '\n';  // expected output: after
  cout << ThirdGreatest_v2({"coder", "byte", "code"})
       << '\n';  // expected output: code
  cout << ThirdGreatest_v2({"abc", "defg", "z", "hijk"})
       << '\n';  // expected output: abc

  return 0;
}
