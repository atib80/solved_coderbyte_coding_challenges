/*
Coderbyte coding challenge: Alphabet Soup

Using the C++ language, have the function AlphabetSoup(str) take the str string
parameter being passed and return the string with the letters in alphabetical
order (ie. hello becomes ehllo). Assume numbers and punctuation symbols will not
be included in the string.

Sample test cases:

Input:  "coderbyte"
Output: "bcdeeorty"

Input:  "hooplah"
Output: "ahhloop"
*/

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

string AlphabetSoup_v1(string str) {
  sort(begin(str), end(str));
  return str;
}

int compare(const void* lc, const void* rc) {
  return *static_cast<const char*>(lc) - *static_cast<const char*>(rc);
}

string AlphabetSoup_v2(string str) {
  if (str.empty())
    return {};
  qsort(&str[0], str.length(), sizeof(str.front()), compare);
  return str;
}

// simple bubblesort implementation
string AlphabetSoup_v3(string str) {
  const size_t str_len{str.length()};
  if (str_len < 2U)
    return str;

  bool did_swap_elements{true};
  for (size_t i{1U}; did_swap_elements && i < str_len; ++i) {
    did_swap_elements = false;
    for (size_t j{}; j < str_len - i; j++) {
      if (str[j] > str[j + 1]) {
        swap(str[j], str[j + 1]);
        did_swap_elements = true;
      }
    }
  }

  return str;
}

int main() {
  // cout << AlphabetSoup_v2(gets(stdin));
  cout << AlphabetSoup_v3("hello") << '\n';      // expected output: ehllo
  cout << AlphabetSoup_v3("coderbyte") << '\n';  // expected output: bcdeeorty
  cout << AlphabetSoup_v3("hooplah") << '\n';    // expected output: ahhloop

  return 0;
}
