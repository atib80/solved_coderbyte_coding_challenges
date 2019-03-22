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
  if (str.empty()) return {};
  qsort(&str[0], str.length(), sizeof(str.front()), compare);
  return str;
}

int main() {
  // cout << AlphabetSoup_v2(gets(stdin));
  cout << AlphabetSoup_v2("hello")
       << '\n';  // expected output: ehllo
  cout << AlphabetSoup_v2("coderbyte")
       << '\n';  // expected output: bcdeeorty
  cout << AlphabetSoup_v2("hooplah")
       << '\n';  // expected output: ahhloop

  return 0;
}
