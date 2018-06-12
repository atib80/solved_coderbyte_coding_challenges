/*
Coderbyte coding challenge: Group Totals

Using the C++ language, have the function GroupTotals(strArr) read in the strArr
parameter containing key:value pairs where the key is a string and the value is
an integer. Your program should return a string with new key:value pairs
separated by a comma such that each key appears only once with the total values
summed up. For example: if strArr is ["B:-1", "A:1", "B:3", "A:5"] then your
program should return the string A:6,B:2.

Your final output string should return the keys in alphabetical order. Exclude
keys that have a value of 0 after being summed up.

Sample test cases:

Input:  "X:-1", "Y:1", "X:-4", "B:3", "X:5"
Output: "B:3,Y:1"

Input:  "Z:0", "A:-1"
Output: "A:-1"
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>
#include <string>

using namespace std;

string GroupTotals(const string* str_arr, const size_t str_arr_size) {
  map<string, int> group_totals{};

  for (size_t i{}; i < str_arr_size; i++) {
    const size_t sep_char_pos{str_arr[i].find(':')};
    const string key{str_arr[i].substr(0, sep_char_pos)};
    const int value{stoi(str_arr[i].substr(sep_char_pos + 1))};
    group_totals[move(key)] += value;
  }

  string output{};
  output.reserve(1024);
  char buffer[32];

  for (const pair<string, int>& total : group_totals) {
    if (!total.second)
      continue;
    sprintf(buffer, "%s:%d,", total.first.c_str(), total.second);
    output.append(buffer);
  }

  output.pop_back();

  return output;
}

int main() {
  // const string A[] = gets(stdin);
  // cout << GroupTotals(A, sizeof(A) / sizeof(*A)) << '\n';
  const string B[] = {"B:-1", "A:1", "B:3", "A:5"};
  cout << GroupTotals(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "A:6,B:2"
  const string C[] = {"X:-1", "Y:1", "X:-4", "B:3", "X:5"};
  cout << GroupTotals(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "B:3,Y:1"
  const string D[] = {"Z:0", "A:-1"};
  cout << GroupTotals(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "A:-1"

  return 0;
}
