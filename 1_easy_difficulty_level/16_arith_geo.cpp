/*
Coderbyte coding challenge: Arith Geo
Using the C++ language, have the function ArithGeo(arr) take the array of numbers stored in arr and return the string "Arithmetic" 
if the sequence follows an arithmetic pattern or return "Geometric" if it follows a geometric pattern. If the sequence doesn't follow either pattern return -1. 
An arithmetic sequence is one where the difference between each of the numbers is consistent, where as in a geometric sequence, 
each term after the first is multiplied by some constant or common ratio. Arithmetic example: [2, 4, 6, 8] and Geometric example: [2, 6, 18, 54]. 
Negative numbers may be entered as parameters, 0 will not be entered, and no array will contain all the same elements.

Sample test cases:

Input:  5,10,15
Output: "Arithmetic"

Input:  2,4,16,24
Output: "-1"
*/

#include <iostream>
#include <string>

using namespace std;

string ArithGeo(const int* arr, const size_t arr_size) { 

  if (arr_size < 2u) return string{"-1"};

  const int diff { arr[1] - arr[0] };

  const int factor { arr[1] /  arr[0] };

  bool is_arithmetic{true};

  for (size_t i{1u}; i != arr_size; i++) {

  		if (diff != ( arr[i] - arr[i - 1] ) ) { 
  			is_arithmetic = false;
  			break;
  		}
  }

  if (is_arithmetic) return string{"Arithmetic"};

   bool is_geometric{true};

  for (size_t i{1u}; i != arr_size; i++) {

  		if (factor != ( arr[i] / arr[i - 1] ) ) { 
  			is_geometric = false;
  			break;
  		}
  }

  if (is_geometric) return string{"Geometric"};
  
  return string{"-1"}; 
            
}

int main() { 
     
  const int A[] = gets(stdin);
  cout << ArithGeo(A, sizeof(A)/sizeof(*A));
  // const int B[] = {2, 4, 6, 8};
  // cout << ArithGeo(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "Arithmetic"
  // const int C[] = {2, 6, 18, 54};
  // cout << ArithGeo(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "Geometric"
  // const int D[] = {5,10,15};
  // cout << ArithGeo(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "Arithmetic"
  // const int E[] = {2,4,16,24};
  // cout << ArithGeo(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: "-1"
  return 0;    
} 
