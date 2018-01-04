/*
Coderbyte coding challenge: Check Nums

Using the C++ language, have the function CheckNums(num1,num2) take both parameters being passed and return the string true if num2 is greater than num1, 
otherwise return the string false. If the parameter values are equal to each other then return the string -1.

Sample test cases:

Input:  3 & num2 = 122
Output: "true"

Input:  67 & num2 = 67
Output: "-1"
*/

#include <iostream>
#include <string>

using namespace std;

string CheckNums(const int num1, const int num2) { 

  if (num1 == num2) return "-1";
  
  if (num2 > num1) return "true";
   
  return "false";
  
}

int main() { 
  
  // cout << CheckNums(gets(stdin));
  cout << CheckNums(3, 122) << '\n'; // expected output: "true"
  cout << CheckNums(67, 67) << '\n'; // expected output: "-1"
  cout << CheckNums(35, 17) << '\n'; // expected output: "false"
  return 0;  
}
