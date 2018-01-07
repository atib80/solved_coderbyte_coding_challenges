/*
Coderbyte coding challenge: Coin Determiner

Using the C++ language, have the function CoinDeterminer(num) take the input, which will be an integer ranging from 1 to 250, 
and return an integer output that will specify the least number of coins, that when added, equal the input integer. 
Coins are based on a system as follows: there are coins representing the integers 1, 5, 7, 9, and 11. 
So for example: if num is 16, then the output should be 2 because you can achieve the number 16 with the coins 9 and 7. 
If num is 25, then the output should be 3 because you can achieve 25 with either 11, 9, and 5 coins or with 9, 9, and 7 coins.

Sample test cases:

Input:  6
Output: 2

Input:  16
Output: 2
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int CoinDeterminer(int money) {

	if (!money) return 0;

	money = abs(money);

	const vector<int> coins { 11, 9, 7, 5, 1 };

	for (const auto coin : coins) {

		if (coin == money) return 1;

	}

	if (money % 11 == 0) return money / 11;
	
	int min_number_of_needed_coins{numeric_limits<int>::max()};
	size_t max_number_of_tries { coins.size() };
	int amount { money }, coins_count{};
	size_t i{};	

	while (true) {

		const int factor { amount / coins[i] };		

		if (!factor) {

			i++;					
			
			if (coins.size() == i) {
				max_number_of_tries--;
				if (!max_number_of_tries) break;
				i = coins.size() - max_number_of_tries;
			}

			continue;
		}

		coins_count += factor;

		amount -= factor * coins[i];

		if (!amount) {
			if (coins_count < min_number_of_needed_coins) min_number_of_needed_coins = coins_count;
			amount = money;
			coins_count = 0;
			max_number_of_tries--;
			if (!max_number_of_tries) break;
			i = coins.size() - max_number_of_tries;
			continue;
		}

		i++;
		
	}

  return min_number_of_needed_coins;
  
}

int main() { 
  
  // cout << CoinDeterminer(gets(stdin));
  cout << CoinDeterminer(16) << '\n'; // expected output: 2
  cout << CoinDeterminer(25) << '\n'; // expected output: 3
  cout << CoinDeterminer(6) << '\n';  // expected output: 2
  return 0;    
}
