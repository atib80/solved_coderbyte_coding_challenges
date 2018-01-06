/*
Coderbyte coding challenge: Moving Median

Using the C++ language, have the function MovingMedian(arr) read the array of numbers stored in arr which will contain a sliding window size, 
N, as the first element in the array and the rest will be a list of numbers. 
Your program should return the Moving Median for each element based on the element and its N-1 predecessors, where N is the sliding window size. 
The final output should be a string with the moving median corresponding to each entry in the original array separated by commas.

Note that for the first few elements (until the window size is reached), the median is computed on a smaller number of entries. 
For example: if arr is [3, 1, 3, 5, 10, 6, 4, 3, 1] then your program should output "1,2,3,5,6,6,4,3"

Sample test cases:

Input:  5, 2, 4, 6
Output: "2,3,4"

Input:  3, 0, 0, -2, 0, 2, 0, -2
Output: "0,0,0,0,0,0,0"
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string MovingMedian(vector<long> numbers) { 

  const size_t numbers_size { numbers.size() };

  const size_t window_size { static_cast<size_t>(numbers[0]) };

  vector<long> window{};
  long median;
  string answer{};
  answer.reserve(2 * (numbers_size - 1));

  for(size_t i{1u}; i != numbers_size; i++) 
  {
        
      window.clear();

      for(size_t j{}; ((j < window_size) && (j < i)); j++)
      {
          window.emplace_back(numbers[i - j]);
      }

      stable_sort(begin(window), end(window));

      const size_t ws { window.size() };

      if (ws % 2 == 1) median = window [ws / 2];
      else median = ( window[ws / 2 - 1] + window[ws / 2] ) / 2;

      answer += to_string(median);
      answer.push_back(',');

  }

  answer.erase(--end(answer));
  
  answer.shrink_to_fit();
  
  return answer;
}

int main() { 
 
  cout << MovingMedian(move(vector<long>{gets(stdin)}));
  // cout << MovingMedian(move(vector<long>{3, 1, 3, 5, 10, 6, 4, 3, 1})) << '\n'; // expected output: "1,2,3,5,6,6,4,3" 
  // cout << MovingMedian(move(vector<long>{5, 2, 4, 6})) << '\n';                 // expected output: "2,3,4"
  // cout << MovingMedian(move(vector<long>{3, 0, 0, -2, 0, 2, 0, -2})) << '\n';   // expected output: "0,0,0,0,0,0,0"
  
  return 0;    
}
