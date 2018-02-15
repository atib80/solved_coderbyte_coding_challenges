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

#include <cctype>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

string OffLineMinimum(vector<string> str_arr) {
  multiset<long> numbers{};
  vector<long> extracted_numbers{};

  for (auto& item : str_arr) {
    item = trim(item);

    if ((item == "E") && (!numbers.empty())) {
      extracted_numbers.emplace_back(*begin(numbers));
      numbers.erase(begin(numbers));
      continue;
    }

    numbers.insert(stol(item));
  }

  ostringstream oss{};

  for (size_t i{}; i < extracted_numbers.size() - 1; i++) {
    oss << extracted_numbers[i] << ',';
  }

  oss << extracted_numbers.back();

  return oss.str();
}

int main() {
  // cout << OffLineMinimum(move(vector<string>{gets(stdin)}));
  cout << OffLineMinimum(move(
              vector<string>{"5", "4", "6", "E", "1", "7", "E", "E", "3", "2"}))
       << '\n';
  // expected output: 4,1,5
  cout << OffLineMinimum(move(vector<string>{"1", "2", "E", "E", "3"}))
       << '\n';  // expected output: 1,2
  cout << OffLineMinimum(
              move(vector<string>{"4", "E", "1", "E", "2", "E", "3", "E"}))
       << '\n';
  // expected output: 4,1,2,3

  return 0;
}
