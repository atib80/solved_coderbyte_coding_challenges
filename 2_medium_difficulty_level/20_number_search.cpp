/*
Coderbyte coding challenge: Number Search

Using the C++ language, have the function NumberSearch(str) take the str
parameter, search for all the numbers in the string, add them together, then
return that final number divided by the total amount of letters in the string.
For example: if str is "Hello6 9World 2, Nic8e D7ay!" the output should be 2.
First if you add up all the numbers, 6 + 9 + 2 + 8 + 7 you get 32. Then there
are 17 letters in the string. 32 / 17 = 1.882, and the final answer should be
rounded to the nearest whole number, so the answer is 2. Only single digit
numbers separated by characters will be used throughout the whole string (So
this won't ever be the case: hello44444 world). Each string will also have at
least one letter.

Sample test cases:

Input:  "H3ello9-9"
Output: 4

Input:  "One Number*1*"
Output: 0
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

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

string NumberSearch_v1(string str) {
  str = trim(str);

  int sum{};
  int letter_count{};

  for (const char ch : str) {
    if (isdigit(ch))
      sum += ch - '0';
    else if (isalpha(ch))
      letter_count++;
  }

  if (!sum) {
    if (!letter_count)
      return "NaN";
    return "0";
  }

  if (!letter_count)
    return "Infinity";

  return to_string(
      static_cast<long>(round(static_cast<float>(sum) / letter_count)));
}

string NumberSearch_v2(string str) {
  str = trim(str);

  int sum{};
  int letter_count{};

  for_each(begin(str), end(str), [&](const char ch) {
    if (isdigit(ch))
      sum += ch - '0';
    else if (isalpha(ch))
      letter_count++;
  });

  if (!sum) {
    if (!letter_count)
      return "NaN";
    return "0";
  }

  if (!letter_count)
    return "Infinity";

  return to_string(
      static_cast<long>(round(static_cast<float>(sum) / letter_count)));
}

int main() {
  // cout << NumberSearch_v2(move(string{gets(stdin)}));
  cout << NumberSearch_v2(move(string{"Hello6 9World 2, Nic8e D7ay!"}))
       << '\n';  // expected output: 2
  cout << NumberSearch_v2(move(string{"H3ello9-9"}))
       << '\n';  // expected output: 4
  cout << NumberSearch_v2(move(string{"One Number*1*"}))
       << '\n';  // expected output: 0
  return 0;
}
