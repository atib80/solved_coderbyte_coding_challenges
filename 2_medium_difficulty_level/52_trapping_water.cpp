/*
Coderbyte coding challenge: Trapping Water

Using the C++ language, have the function TrappingWater(arr) take the array of non-negative integers stored in arr, and determine the largest amount of water 
that can be trapped. The numbers in the array represent the height of a building (where the width of each building is 1) and if you imagine it raining, 
water will be trapped between the two tallest buildings. For example: if arr is [3, 0, 0, 2, 0, 4] then this array of building heights looks like
the following picture if we draw it out:
               __
 __           |  |
|  |     __   |  |
|  |    |  |  |  |
|  |____|  |__|  |

               __
 __           |  |
|  |xxxxxxxxxx|  |
|  |xxxx|  |xx|  |
|  |xxxx|  |xx|  |



Now if you imagine it rains and water gets trapped in this picture, then it'll look like the following (the x's represent water):
This is the most water that can be trapped in this picture, and if you calculate the area you get 10, so your program should return 10.

Sample test cases:

Input:  1, 2, 1, 2
Output: 1

Input:  0, 2, 4, 0, 2, 1, 2, 6
Output: 11
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t TrappingWater(const int* arr, const size_t arr_size) { 

  size_t count{};
  size_t start{}, last{arr_size - 1};

  while (!arr[start]) start++; // ignore water levels with 0 height at the beginning of arr
  while (!arr[last]) last--;   // ignore water levels with 0 height at the end of arr

  vector<int> water_levels(arr + start, arr + last + 1);
  
  int first_max_water_level { water_levels[0] };
  
  int last_max_water_level { water_levels.back() };

  vector<int> current_water_levels{};

  for (size_t i{1u}; i <= last ; i++) {

  		if (water_levels[i] >= first_max_water_level) {  			

  			for (const int water_level : current_water_levels) count += first_max_water_level - water_level;

  			first_max_water_level = water_levels[i];

  			current_water_levels.clear();

  			if (i == last) break;

  			continue;

  		}

  		if ((i == last) && (first_max_water_level >= last_max_water_level)) {

  			first_max_water_level = last_max_water_level;

  			for (const int water_level : current_water_levels) count += first_max_water_level - water_level;

  			break;  		
  		} 

  		current_water_levels.emplace_back(water_levels[i]);
  }
   
  return count;
  
}

int main() { 
   
  // const int A[] = gets(stdin);
  // cout << TrappingWater(A, sizeof(A)/sizeof(*A));
  const int B[] = {3, 0, 0, 2, 0, 4};
  cout << TrappingWater(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 10
  const int C[] = {1, 2, 1, 2};
  cout << TrappingWater(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 1
  const int D[] = {0, 2, 4, 0, 2, 1, 2, 6};
  cout << TrappingWater(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 11
  
  return 0;    
}
