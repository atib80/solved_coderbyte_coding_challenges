/*
Coderbyte coding challenge: Closest Enemy

Using the C++ language, have the function ClosestEnemy(arr) take the array of numbers stored in arr and from the position in the array where a 1 is, 
return the number of spaces either left or right you must move to reach an enemy which is represented by a 2. For example: if arr is [0, 0, 1, 0, 0, 2, 0, 2] 
then your program should return 3 because the closest enemy (2) is 3 spaces away from the 1. The array will contain any number of 0's and 2's, but only a single 1. 
It may not contain any 2's at all as well, where in that case your program should return a 0.

Sample test cases:

Input:  1, 0, 0, 0, 2, 2, 2
Output: 4

Input:  2, 0, 0, 0, 2, 2, 1, 0
Output: 1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

size_t ClosestEnemy(const int* arr, const size_t arr_size) {

  size_t hero_pos { string::npos };

  if (find(arr, arr + arr_size, 1) == (arr + arr_size)) return 0;

  if (find(arr, arr + arr_size, 2) == (arr + arr_size)) return 0;

  size_t left_enemy_pos { string::npos };
  size_t right_enemy_pos { string::npos };

  for (size_t i{}; i != arr_size; i++) {

  	if ( (1 == arr[i]) && (string::npos == hero_pos) ) {
  		hero_pos = i;
  		continue;
  	}

  	if (2 == arr[i]) {

  		if (string::npos == hero_pos) {
  			left_enemy_pos = i;
  			continue;
  		}
  		
  		if ((string::npos == right_enemy_pos) && (string::npos != hero_pos)) { 
  			right_enemy_pos = i;
  			break;
  		}
  	}  	
  }

  size_t min_distance { string::npos != left_enemy_pos ? hero_pos - left_enemy_pos : string::npos };

  if ( ( right_enemy_pos - hero_pos ) < min_distance ) min_distance = right_enemy_pos - hero_pos;

  return min_distance;
  
}

int main() { 
  
  // const int A[] = gets(stdin);
  // cout << ClosestEnemy(A, sizeof(A)/sizeof(*A));
  const int B[] = { 0, 0, 1, 0, 0, 2, 0, 2 };
  cout << ClosestEnemy(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 3
  const int C[] = { 1, 0, 0, 0, 2, 2, 2 };
  cout << ClosestEnemy(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 4
  const int D[] = { 2, 0, 0, 0, 2, 2, 1, 0 };
  cout << ClosestEnemy(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 1
  return 0;
}
