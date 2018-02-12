/*
Coderbyte coding challenge: Alphabet Soup

Using the C++ language, have the function AlphabetSoup(str) take the str string parameter being passed and return the string with the letters in alphabetical order 
(ie. hello becomes ehllo). Assume numbers and punctuation symbols will not be included in the string.

Sample test cases:

Input:  "coderbyte"
Output: "bcdeeorty"

Input:  "hooplah"
Output: "ahhloop"
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string AlphabetSoup(string str) { 

  sort(begin(str), end(str));

  return str;

}

int main() { 

  // cout << AlphabetSoup(move(string{gets(stdin)}));
  cout << AlphabetSoup(move(string{"hello"})) << '\n';    // expected output: ehllo
  cout << AlphabetSoup(move(string{"coderbyte"})) << '\n'; // expected output: bcdeeorty
  cout << AlphabetSoup(move(string{"hooplah"})) << '\n';   // expected output: ahhloop
  
  return 0;
    
}
