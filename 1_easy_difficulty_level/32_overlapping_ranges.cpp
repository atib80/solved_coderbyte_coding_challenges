/*
Coderbyte coding challenge: Overlapping Ranges

Using the C++ language, have the function OverlappingRanges(arr) take the array of numbers stored in arr which will contain 5 positive integers, 
the first two representing a range of numbers (a to b), the next 2 also representing another range of integers (c to d), and a final 5th element (x) 
which will also be a positive integer, and return the string true if both sets of ranges overlap by at least x numbers. 
For example: if arr is [4, 10, 2, 6, 3] then your program should return the string true. 
The first range of numbers are 4, 5, 6, 7, 8, 9, 10 and the second range of numbers are 2, 3, 4, 5, 6. 
The last element in the array is 3, and there are 3 numbers that overlap between both ranges: 4, 5, and 6. 
If both ranges do not overlap by at least x numbers, then your program should return the string false.

Sample test cases:

Input:  5,11,1,5,1
Output: "true"

Input:  1,8,2,4,4
Output: "false"
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string OverlappingRanges(vector<int> v) { 

  if (v.size() < 5) return string{"Not possible! Please give me at least 5 whole numbers."};

  const int a1{v[0]};
  const int b1{v[1]};

  const int a2{v[2]};
  const int b2{v[3]};

  const int x{v[4]};

  if ((a1 <= a2) && (b1 >= b2) && ((b2 - a2 + 1) >= x)) return string{"true"};

  if ((a1 <= a2) && (b1 <= b2) && (b1 >= a2) && ((b1 - a2 + 1) >= x)) return string{"true"};

  if ((a1 >= a2) && (b1 >= b2) && (a1 <= b2) && ((b2 - a1 + 1) >= x)) return string{"true"};

  return string{"false"};

}

int main() {   
  
  // cout << OverlappingRanges(move(vector<int>{gets(stdin)}));
  cout << OverlappingRanges(move(vector<int>{4, 10, 2, 6, 3})) << '\n'; // expected output: "true"
  cout << OverlappingRanges(move(vector<int>{5,11,1,5,1})) << '\n';     // expected output: "true"
  cout << OverlappingRanges(move(vector<int>{1,8,2,4,4})) << '\n';      // expected output: "false"
  return 0;    
}
