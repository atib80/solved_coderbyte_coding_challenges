/*
Coderbyte coding challenge: Longest Increasing Sequence

Using the C++ language, have the function LongestIncreasingSequence(arr) take the array of positive integers stored in arr 
and return the length of the longest increasing subsequence (LIS). A LIS is a subset of the original list where the numbers are in sorted order, 
from lowest to highest, and are in increasing order. The sequence does not need to be contiguous or unique, and there can be several different subsequences. 
For example: if arr is [4, 3, 5, 1, 6] then a possible LIS is [3, 5, 6], and another is [1, 6]. 
For this input, your program should return 3 because that is the length of the longest increasing subsequence.

Sample test cases:

Input:  9, 9, 4, 2
Output: 1

Input:  10, 22, 9, 33, 21, 50, 41, 60, 22, 68, 90
Output: 7
*/

#include <iostream>
#include <vector>

using namespace std;

size_t LongestIncreasingSequence(const int* numbers, const size_t numbers_size) { 

  vector<size_t> indices { 0u };

  for(size_t i{1u}; i < numbers_size; i++)
  {
      if(numbers[indices.back()] < numbers[i])
      {
          indices.emplace_back(i);
          continue;
      }

      size_t low{0u}, high{indices.size() - 1};
      
      while (low < high)
      {
          const size_t middle { (low + high) / 2 };
          if(numbers[indices[middle]] < numbers[i]) low = middle + 1;
          else high = middle;          
      }

      if (numbers[i] < numbers[indices[low]]) indices[low] = i;
      
  }

  return indices.size();
            
}

int main() { 

  // const int A[] = gets(stdin);
  // cout << LongestIncreasingSequence(A, sizeof(A)/sizeof(*A));  
  const int B[] = {4, 3, 5, 1, 6};
  cout << LongestIncreasingSequence(B, sizeof(B)/sizeof(*B)) << '\n';  // expected output: 3
  const int C[] = {9, 9, 4, 2};
  cout << LongestIncreasingSequence( C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 1
  const int D[] = {10, 22, 9, 33, 21, 50, 41, 60, 22, 68, 90};
  cout << LongestIncreasingSequence( D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 7
  const int E[] = {2, 4, 3, 5, 1, 7, 6, 9, 8};
  cout << LongestIncreasingSequence( E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: 5
  const int F[] = {10, 22, 9, 33, 21, 50, 41, 60};
  cout << LongestIncreasingSequence( F, sizeof(F)/sizeof(*F)) << '\n'; // expected output: 5
  const int G[] = {10, 12, 4, 6, 100, 2, 56, 34, 79};
  cout << LongestIncreasingSequence( G, sizeof(G)/sizeof(*G)) << '\n'; // expected output: 4
  const int H[] = {10, 12, 4, 6, 100, 2, 56, 34, 79, 45, 33, 12, 45, 67, 89};
  cout << LongestIncreasingSequence( H, sizeof(H)/sizeof(*H)) << '\n'; // expected output: 6  
  return 0;    
}
