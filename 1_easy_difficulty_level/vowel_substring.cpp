#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/*
 * Description:
 * Given a string 's' and a whole number 'k' find the first substring of length
 k that contains the most vowels (number of vowels <= k). If you cannot find any
 substring of length k that contains at least 1 vowel return the string "Not
 found!"

 *
 * Complete the 'findSubstring' function below.
 *
 *
 * The function is expected to return a string.
 * The function accepts the following parameters:
 *  1. string s
 *  2. int k
 */

static int allowed_vowels[256]{};

static int _ = []() {
  allowed_vowels['a'] = allowed_vowels['e'] = allowed_vowels['i'] = allowed_vowels['o'] = allowed_vowels['u'] = 1;
  return 0;
}();

string findSubstring(const string& s, size_t k) {

  size_t start_pos{string::npos};

  k = min(k, s.length());

  size_t max_vowel_count =
      count_if(cbegin(s), cbegin(s) + k, [&](const char ch) {
        return 1 == allowed_vowels[static_cast<size_t>(ch)];
      });
  size_t vowel_count{max_vowel_count}, offset{1};

  if (0U != max_vowel_count)
    start_pos = 0U;
  else
    offset = k;

  if (k == max_vowel_count)
    return s.substr(0, k);

  for (size_t i{offset}; i + k <= s.length(); ++i) {
    vowel_count -= allowed_vowels[static_cast<size_t>(s[i - 1])];
    vowel_count += allowed_vowels[static_cast<size_t>(s[i + k - 1])];

    if (vowel_count > max_vowel_count) {
      if (k == vowel_count)
        return s.substr(i, k);
      max_vowel_count = vowel_count;
      start_pos = i;
    }
  }

  if (string::npos != start_pos)
    return s.substr(start_pos, k);

  return "Not found!";
}

int main() {
  cout << findSubstring("caberqiitefg", 5) << '\n';  // expected output: "erqii"
  cout << findSubstring("aeiouia", 3) << '\n';       // expected output: "aei"
  cout << findSubstring("qwdftr", 2) << '\n';  // expected output: "Not found!"

  return 0;
}
