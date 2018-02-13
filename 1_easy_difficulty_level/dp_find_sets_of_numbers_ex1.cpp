/*
Dynamic programming related coding challenge: 

Find the max. number of subsets of numbers in the given input array of whole numbers that add up 
to the given sum value specified as the first number in the input array.

Sample test cases:

Input:  16 2 4 6 10
Output: 2
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

size_t find_number_of_subsets(int argc, char** argv) {

	if (argc < 3) return 0;	

	const int sum { stoi(trim(string{argv[1]})) };

	vector<int> numbers{};

	for (int i{2}; i < argc; i++) {
		numbers.emplace_back(stoi(trim(string{argv[i]})));
	}

	sort(begin(numbers), end(numbers), [](const int ln, const int rn) {
		return ln > rn;
	});

	size_t number_of_subsets{};

	for (size_t i{}; i < numbers.size() - 1; i++) {

		int current_sum{};
		bool is_continue_search{};
		
		for (size_t j{i}; j < numbers.size(); j++) {

			if (current_sum + numbers[j] == sum) {
				number_of_subsets++;
				is_continue_search = true;
				continue;
			} else if (current_sum + numbers[j] > sum) {
				is_continue_search = true;
				continue;
			}

			current_sum += numbers[j];
		}

		if (!is_continue_search) break;

	}

	return number_of_subsets;
}

int main(int argc, char** argv) {	

	cout << find_number_of_subsets(argc, argv) << '\n';

	return 0;

}