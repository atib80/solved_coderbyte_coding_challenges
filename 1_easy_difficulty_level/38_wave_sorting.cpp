/*
Coderbyte coding challenge: Wave Sorting

Using the C++ language, have the function WaveSorting(arr) take the array of positive integers stored in arr 
and return the string true if the numbers can be arranged in a wave pattern: a1 > a2 < a3 > a4 < a5 > ..., 
otherwise return the string false. For example, if arr is: [0, 1, 2, 4, 1, 4], then a possible wave ordering of the numbers is: [2, 0, 4, 1, 4, 1]. 
So for this input your program should return the string true. 
The input array will always contain at least 2 elements. More examples are given below as sample test cases.

Sample test cases:

Input:  0, 1, 2, 4, 1, 1, 1
Output: "false"

Input:  0, 4, 22, 4, 14, 4, 2
Output: "true"
*/

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

string WaveSorting(int* arr, const size_t arr_size) { 
       
    sort(arr, arr + arr_size);

    map<int, size_t> number_freq{};
    number_freq.insert(make_pair(arr[0], 1u));
    int last_counted_num { arr[0] };
    size_t balance { 1u };

    for (size_t i{1u}; i < arr_size; i++) {

    	if (number_freq.find(arr[i]) == end(number_freq)) number_freq.insert(make_pair(arr[i], 1u));
    	else number_freq[arr[i]]++;

        if (!balance) { 
        	last_counted_num = arr[i]; 
        	balance++;

        } 
        else if (last_counted_num == arr[i]) balance++;        
        else balance--;
    }

    if (!balance) return "true";

    if (number_freq[last_counted_num] > arr_size / 2) return "false";

    return "true";

}

int main() { 
     
  // int arr[] = gets(stdin);
  // cout << WaveSorting(arr, sizeof(arr)/sizeof(*arr));
  int b[] = {0, 1, 2, 4, 1, 4};
  cout << WaveSorting(b, sizeof(b)/sizeof(*b)) << '\n'; // "true"
  int c[] = {0, 1, 2, 4, 1, 1, 1};
  cout << WaveSorting(c, sizeof(c)/sizeof(*c)) << '\n'; // "false"
  int d[] = {0, 4, 22, 4, 14, 4, 2};
  cout << WaveSorting(d, sizeof(d)/sizeof(*d)) << '\n'; // "true"

  return 0;    
} 
