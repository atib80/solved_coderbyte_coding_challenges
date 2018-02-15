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
#include <vector>

using namespace std;

string ThirdGreatest(vector<string> words) {
  if (words.size() < 3)
    return "Not possible!";

  stable_sort(begin(words), end(words), [](const string& lw, const string& rw) {
    return (lw.length() > rw.length());
  });

  return words[2];
}

int main() {
  // cout << ThirdGreatest(move(vector<string>{gets(stdin)}));
  cout << ThirdGreatest(move(vector<string>{"hello", "world", "before", "all"}))
       << '\n';  // expected output: world
  cout << ThirdGreatest(move(vector<string>{"hello", "world", "after", "all"}))
       << '\n';  // expected output: after
  cout << ThirdGreatest(move(vector<string>{"coder", "byte", "code"}))
       << '\n';  // expected output: code
  cout << ThirdGreatest(move(vector<string>{"abc", "defg", "z", "hijk"}))
       << '\n';  // expected output: abc

  return 0;
}
