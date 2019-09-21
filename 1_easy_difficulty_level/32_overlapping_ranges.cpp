/*
Coderbyte coding challenge: Overlapping Ranges

Using the C++ language, have the function OverlappingRanges(arr) take the array
of numbers stored in arr which will contain 5 positive integers, the first two
representing a range of numbers (a to b), the next 2 also representing another
range of integers (c to d), and a final 5th element (x) which will also be a
positive integer, and return the string true if both sets of ranges overlap by
at least x numbers. For example: if arr is [4, 10, 2, 6, 3] then your program
should return the string true. The first range of numbers are 4, 5, 6, 7, 8, 9,
10 and the second range of numbers are 2, 3, 4, 5, 6. The last element in the
array is 3, and there are 3 numbers that overlap between both ranges: 4, 5,
and 6. If both ranges do not overlap by at least x numbers, then your program
should return the string false.

Sample test cases:

Input:  5,11,1,5,1
Output: "true"

Input:  1,8,2,4,4
Output: "false"
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string OverlappingRanges_v1(vector<int64_t> v) {
  if (v.size() < 5U)
    return "Please give me at least 5 whole numbers!";

  const int64_t A1{v[0]};
  const int64_t B1{v[1]};

  const int64_t A2{v[2]};
  const int64_t B2{v[3]};

  const int64_t x{v[4]};

  if (A1 <= A2 && B1 >= B2 && B2 - A2 + 1 >= x)
    return "true";

  if (A1 <= A2 && B1 <= B2 && B1 >= A2 && B1 - A2 + 1 >= x)
    return "true";

  if (A1 >= A2 && B1 >= B2 && A1 <= B2 && B2 - A1 + 1 >= x)
    return "true";

  return "false";
}

string OverlappingRanges_v2(vector<int64_t> v) {
  if (v.size() < 5U)
    return "Please give me at least 5 whole numbers!";

  vector<pair<int64_t, int>> intervals{
      {v[0], 1}, {v[1], -1}, {v[2], 1}, {v[3], -1}};
  sort(begin(intervals), end(intervals),
       [](const auto& lp, const auto& rp) { return lp.first < rp.first; });

  if (0 == intervals[0].second + intervals[1].second) {
    if (intervals[1].first == intervals[2].first && 1 == v[4])
      return "true";
    return "false";
  }

  if (intervals[2].first - intervals[1].first + 1 >= v[4])
    return "true";

  return "false";
}

int main() {
  // cout << OverlappingRanges_v2(gets(stdin));
  cout << OverlappingRanges_v2({4, 10, 2, 6, 3})
       << '\n';  // expected output: "true"
  cout << OverlappingRanges_v2({5, 11, 1, 5, 1})
       << '\n';  // expected output: "true"
  cout << OverlappingRanges_v2({1, 8, 2, 4, 4})
       << '\n';  // expected output: "false"

  return 0;
}
