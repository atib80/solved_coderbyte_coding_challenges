/*
Coderbyte coding challenge: Mean Mode

Using the C++ language, have the function MeanMode(arr) take the array of numbers stored in arr and return 1 if the mode equals the mean, 
0 if they don't equal each other (ie. [5, 3, 3, 3, 1] should return 1 because the mode (3) equals the mean (3)). 
The array will not be empty, will only contain positive integers, and will not contain more than one mode.

Sample test cases:

Input:  1, 2, 3
Output: 0

Input:  4, 4, 4, 6, 2
Output: 1
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

int MeanMode(vector<int> numbers) { 

	sort(begin(numbers), end(numbers));

	const int sum { accumulate(begin(numbers), end(numbers), 0) };

	const int numbers_size { static_cast<int>(numbers.size()) };

	const int mean {sum / numbers_size};

	unordered_map<int, size_t> number_occurrences{};

	for (const int n : numbers) {

		if (number_occurrences.find(n) != end(number_occurrences)) {
			number_occurrences[n]++;
		} else {
			number_occurrences.insert(make_pair(n, 1u));
		}		
	}

	vector<pair<int, size_t>> number_freq{};

	for (const auto& no : number_occurrences) {
		number_freq.emplace_back(no);
	}

	sort(begin(number_freq), end(number_freq), [](const pair<int, size_t>& l, const pair<int, size_t>& r) {

		return (l.second > r.second);

	});

	if (mean == number_freq[0].first) return 1;

	return 0;
           
}

int main() { 
     
  // cout << MeanMode ( move(vector<int>{ gets(stdin) } ) );  
  cout << MeanMode ( move(vector<int>{5, 3, 3, 3, 1}) ) << '\n';
  cout << MeanMode ( move(vector<int>{1, 2, 3}) ) << '\n';
  cout << MeanMode ( move(vector<int>{4, 4, 4, 6, 2}) ) << '\n';
  cout << MeanMode ( move(vector<int>{10, 10}) ) << '\n';
  cout << MeanMode ( move(vector<int>{1, 1, 1, 1, 1}) ) << '\n';
  cout << MeanMode ( move(vector<int>{10, 10, 10, 10, 10, 10, 10, 20, 9, 1}) ) << '\n';
  return 0;    
} 
