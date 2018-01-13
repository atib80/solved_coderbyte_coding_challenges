/*
Coderbyte coding challenge: Nim Winner

Using the C++ language, have the function NimWinner(arr) take the array of integers stored in arr which will represent the amount of coins in each pile. 
For example: [2, 4, 1, 3] means there are 4 piles of coins and there are 2 coins in the first pile, 4 in the second pile, etc. 
Nim is played by each player removing any number of coins from only one pile, and the winner is the player who picks up the last coin. 
For example: if arr is [1, 2, 3] then for example player 1 can remove 2 coins from the last pile which results in [1, 2, 1]. 
Then player 2 can remove 1 coin from the first pile which results in [0, 2, 1], etc. 
The player that has the last possible move taking the last coin(s) from a pile wins the game. 
Your program should output either 1 or 2 which represents which player has a guaranteed win with perfect play for the Nim game.

Sample test cases:

Input:  1,2,3
Output: 2

Input:  1,1,1,4,5,4
Output: 1
*/

#include <iostream>
#include <vector>

using namespace std;

int NimWinner(vector<int> coins) 
{   
  int result { coins[0] };

  for(size_t i{1u}; i != coins.size(); i++) result ^= coins[i];
  
  if (result) return 1;
    
  return 2;

}

int main() 
{ 

  // cout << NimWinner(move(vector<int>{gets(stdin)}));
  cout << NimWinner(move(vector<int>{2, 4, 1, 3})) << '\n';  // 1
  cout << NimWinner(move(vector<int>{1, 2, 3})) << '\n';     // 2
  cout << NimWinner(move(vector<int>{1,1,1,4,5,4})) << '\n'; // 1

  return 0; 
}
