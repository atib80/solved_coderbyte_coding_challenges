/*
Coderbyte coding challenge: Off Line Minimum

Using the C++ language, have the function OffLineMinimum(strArr) take the strArr
parameter being passed which will be an array of integers ranging from 1...n and
the letter "E" and return the correct subset based on the following rules. The
input will be in the following format: ["I","I","E","I",...,"E",...,"I"] where
the I's stand for integers and the E means take out the smallest integer
currently in the whole set. When finished, your program should return that new
set with integers separated by commas. For example: if strArr is
["5","4","6","E","1","7","E","E","3","2"] then your program should return 4,1,5.

Sample test cases:

Input:  "1","2","E","E","3"
Output: "1,2"

Input:  "4","E","1","E","2","E","3","E"
Output: "4,1,2,3"
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string OffLineMinimum_v1(vector<string> str_arr) {
  multiset<int64_t> numbers{};
  ostringstream oss{};

  for (auto& item : str_arr) {
    if (item == "E") {
      if (!numbers.empty()) {
        oss << *begin(numbers) << ',';
        numbers.erase(cbegin(numbers));
      }
    } else
      numbers.insert(stoll(item));
  }

  string output{oss.str()};
  output.erase(--cend(output));
  return output;
}

string OffLineMinimum_v2(vector<string> str_arr) {
  vector<int64_t> numbers{};
  ostringstream oss{};

  for (auto& item : str_arr) {
    if (item == "E") {
      if (!numbers.empty()) {
        make_heap(begin(numbers), end(numbers), greater<int64_t>{});
        pop_heap(begin(numbers), end(numbers), greater<int64_t>{});
        oss << numbers.back() << ',';
        numbers.pop_back();
      }
    } else {
      numbers.emplace_back(stoll(item));
      push_heap(begin(numbers), end(numbers), greater<int64_t>{});
    }
  }

  string output{oss.str()};
  output.erase(--cend(output));
  return output;
}

string OffLineMinimum_v3(vector<string> str_arr) {
  priority_queue<int64_t, vector<int64_t>, greater<int64_t>> numbers{};
  ostringstream oss{};

  for (auto& item : str_arr) {
    if (item == "E") {
      if (!numbers.empty()) {
        oss << numbers.top() << ',';
        numbers.pop();
      }
    } else
      numbers.emplace(stoll(item));
  }

  string output{oss.str()};
  output.erase(--cend(output));
  return output;
}

int main() {
  // cout << OffLineMinimum_v1(gets(stdin));
  cout << OffLineMinimum_v1({"5", "4", "6", "E", "1", "7", "E", "E", "3", "2"})
       << '\n';
  // expected output: 4,1,5
  cout << OffLineMinimum_v1({"1", "2", "E", "E", "3"})
       << '\n';  // expected output: 1,2
  cout << OffLineMinimum_v1({"4", "E", "1", "E", "2", "E", "3", "E"}) << '\n';
  // expected output: 4,1,2,3

  return 0;
}
