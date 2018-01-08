/*
Coderbyte coding challenge: Histogram Area

Using the C++ language, have the function HistogramArea(arr) read the array of non-negative integers stored in arr 
which will represent the heights of bars on a graph (where each bar width is 1), and determine the largest area underneath the entire bar graph. 
For example: if arr is [2, 1, 3, 4, 1] then this looks like the following bar graph:
       _
     _| |
 _  |x|x|
| |_|x|x|_
| | |x|x| |

You can see in the above bar graph that the largest area underneath the graph is covered by the x's. 
The area of that space is equal to 6 because the entire width is 2 and the maximum height is 3, therefore 2 * 3 = 6. 
Your program should return 6. The array will always contain at least 1 element.

Sample test cases:

Input:  6, 3, 1, 4, 12, 4
Output: 12

Input:  5, 6, 7, 4, 1
Output: 16
*/

#include <iostream>
#include <string>

using namespace std;

size_t HistogramArea(const size_t* arr, const size_t arr_size) {

  size_t max_area{};

  for (size_t i{}; i != arr_size; i++) {

      size_t current_area{};
      size_t current_max_height{arr[i]};

    for (size_t j{}; j != arr_size; j++) {

      if (arr[j] < current_max_height) {
        if (current_area > max_area) max_area = current_area;        
        current_area = 0u;
        continue;
      }

      current_area += current_max_height;
    
    }    

    if (current_area > max_area) max_area = current_area; 

  }  

  return max_area; 

}

int main() {   
     
  // const size_t A[] = gets(stdin);
  // cout << HistogramArea(A, sizeof(A)/sizeof(*A));
  const size_t B[] = {2, 1, 3, 4, 1};
  cout << HistogramArea(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 6
  const size_t C[] = {6, 3, 1, 4, 12, 4};
  cout << HistogramArea(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 12
  const size_t D[] = {5, 6, 7, 4, 1};
  cout << HistogramArea(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 16
  const size_t E[] = {1, 2, 3, 4};
  cout << HistogramArea(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: 6
  const size_t F[] = {1,2,3,100};
  cout << HistogramArea(F, sizeof(F)/sizeof(*F)) << '\n'; // expected output: 100
  return 0;
}
