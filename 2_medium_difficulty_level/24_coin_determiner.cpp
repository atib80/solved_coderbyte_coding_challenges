/*
Coderbyte coding challenge: Coin Determiner

Using the C++ language, have the function CoinDeterminer(num) take the input,
which will be an integer ranging from 1 to 250, and return an integer output
that will specify the least number of coins, that when added, equal the input
integer. Coins are based on a system as follows: there are coins representing
the integers 1, 5, 7, 9, and 11. So for example: if num is 16, then the output
should be 2 because you can achieve the number 16 with the coins 9 and 7. If num
is 25, then the output should be 3 because you can achieve 25 with either 11, 9,
and 5 coins or with 9, 9, and 7 coins.

Sample test cases:

Input:  6
Output: 2

Input:  16
Output: 2
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t CoinDeterminer_v1(const size_t money) {
  if (!money)
    return 0;

  const vector<size_t> coins{11, 9, 7, 5, 1};

  for (const auto coin : coins) {
    if (money % coin == 0)
      return money / coin;

    if (coin < money)
      break;
  }

  // string::npos is usually equivalent to 2^32 - 1 or 2^64 - 1
  // (the largest positive value a 32-bit or 64-bit unsigned integral type
  // (uint32_t or uint64_t) can hold)
  size_t min_number_of_needed_coins{string::npos};

  for (size_t i{}; i < coins.size(); i++) {
    size_t amount{money}, coins_count{};
    bool skip_iteration{false};

    for (size_t j{i}; j < coins.size(); j++) {
      if (coins[j] > amount)
        continue;

      const size_t factor{amount / coins[j]};

      if (coins_count + factor >= min_number_of_needed_coins) {
        skip_iteration = true;
        break;
      }

      coins_count += factor;

      amount %= coins[j];

      if (!amount)
        break;
    }

    if (!skip_iteration && (coins_count < min_number_of_needed_coins))
      min_number_of_needed_coins = coins_count;
  }

  return min_number_of_needed_coins;
}

void find_minimum_number_of_coins_for_specified_money_amount(
    const vector<size_t>& coins,
    const size_t index,
    const size_t target_amount,
    size_t& min_number_of_coins,
    const size_t current_number_of_coins = 0) {
  if (!target_amount && (current_number_of_coins < min_number_of_coins)) {
    min_number_of_coins = current_number_of_coins;
    return;
  }

  if (current_number_of_coins >= min_number_of_coins)
    return;

  for (size_t i{index}; i < coins.size(); i++) {
    if (coins[i] > target_amount)
      continue;

    find_minimum_number_of_coins_for_specified_money_amount(
        coins, i + 1, target_amount % coins[i], min_number_of_coins,
        current_number_of_coins + target_amount / coins[i]);
  }
}

size_t CoinDeterminer_v2(const size_t money) {
  if (!money)
    return 0;

  const vector<size_t> coins{11, 9, 7, 5, 1};

  for (const auto coin : coins) {
    if (money % coin == 0)
      return money / coin;

    if (coin < money)
      break;
  }

  size_t min_number_of_needed_coins{string::npos};

  find_minimum_number_of_coins_for_specified_money_amount(
      coins, 0, money, min_number_of_needed_coins, 0);

  return min_number_of_needed_coins;
}

size_t CoinDeterminer_v3(const size_t money) {
  if (!money)
    return 0;

  const vector<size_t> coins{11, 9, 7, 5, 1};

  for (const auto coin : coins) {
    if (money % coin == 0)
      return money / coin;

    if (coin < money)
      break;
  }

  size_t min_number_of_needed_coins{string::npos};
  size_t max_number_of_tries{coins.size()};
  size_t amount{money}, coins_count{};
  size_t i{};

  while (true) {
    const size_t factor{amount / coins[i]};

    if (!factor) {
      i++;

      if (coins.size() == i) {
        max_number_of_tries--;
        if (!max_number_of_tries)
          break;
        i = coins.size() - max_number_of_tries;
      }

      continue;
    }

    coins_count += factor;

    // amount -= factor * coins[i];

    amount %= coins[i];

    if (!amount) {
      if (coins_count < min_number_of_needed_coins)
        min_number_of_needed_coins = coins_count;
      amount = money;
      coins_count = 0;
      max_number_of_tries--;
      if (!max_number_of_tries)
        break;
      i = coins.size() - max_number_of_tries;
      continue;
    }

    i++;
  }

  return min_number_of_needed_coins;
}

int main() {
  // cout << CoinDeterminer_v1(gets(stdin));
  cout << "CoinDeterminer_v1(16) returns: " << CoinDeterminer_v1(16)
       << '\n';  // expected output: 2
  cout << "CoinDeterminer_v1(25) returns: " << CoinDeterminer_v1(25)
       << '\n';  // expected output: 3
  cout << "CoinDeterminer_v1(6)  returns: " << CoinDeterminer_v1(6)
       << '\n';  // expected output: 2
  cout << "-----------------------------\n";
  cout << "CoinDeterminer_v2(16) returns: " << CoinDeterminer_v2(16)
       << '\n';  // expected output: 2
  cout << "CoinDeterminer_v2(25) returns: " << CoinDeterminer_v2(25)
       << '\n';  // expected output: 3
  cout << "CoinDeterminer_v2(6)  returns: " << CoinDeterminer_v2(6)
       << '\n';  // expected output: 2
  cout << "-----------------------------\n";
  cout << "CoinDeterminer_v3(16) returns: " << CoinDeterminer_v3(16)
       << '\n';  // expected output: 2
  cout << "CoinDeterminer_v3(25) returns: " << CoinDeterminer_v3(25)
       << '\n';  // expected output: 3
  cout << "CoinDeterminer_v3(6)  returns: " << CoinDeterminer_v3(6)
       << '\n';  // expected output: 2

  return 0;
}
