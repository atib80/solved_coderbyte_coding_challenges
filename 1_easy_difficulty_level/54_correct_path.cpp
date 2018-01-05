/*
Coderbyte coding challenge: Correct Path

Using the C++ language, have the function CorrectPath(str) read the str parameter being passed,
which will represent the movements made in a 5x5 grid of cells starting from the top left position.
The characters in the input string will be entirely composed of: r, l, u, d, ?.
Each of the characters stand for the direction to take within the grid, for example: r = right, l = left, u = up, d = down.
Your goal is to determine what characters the question marks should be in order for a path
to be created to go from the top left of the grid all the way to the bottom right without touching previously travelled on cells in the grid.

For example: if str is "r?d?drdd" then your program should output the final correct string that will allow a path
to be formed from the top left of a 5x5 grid to the bottom right. For this input, your program should therefore return the string rrdrdrdd.
There will only ever be one correct path and there will always be at least one question mark within the input string.

Sample test cases:

Input:  "???rrurdr?"
Output: "dddrrurdrd"

Input:  "drdr??rrddd?"
Output: "drdruurrdddd"
*/

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <set>
#include <cctype>
#include <algorithm>

using namespace std;

void generate_all(const string&, const int);
void combinations(const string&);
void set_next_available(char*, const int, const int);
bool add_one(int*, const int, const int);

void find_all_string_combinations_for_k_length(const string&, const size_t, vector<string>&);
void collect_all_k_length_words(const string&, const string&, const size_t, const size_t, vector<string>&);

const vector<string>& get_possible_path_directions(const string& path, const vector<set<char>>& allowed_directions)
{
	static vector<string> possible_path_directions{};

	if (!possible_path_directions.empty()) possible_path_directions.clear();

	if (allowed_directions.empty()) return possible_path_directions;

	size_t i{};

	for (const auto& dir : allowed_directions)
	{
		if (dir.size() > 1)
		{
			i++;
		}
	}

	const string possible_directions{ "rdul" };

	find_all_string_combinations_for_k_length(possible_directions, i, possible_path_directions);

	if (2u == (*begin(allowed_directions)).size())
	{

		auto end_pos = remove_if(begin(possible_path_directions), end(possible_path_directions), [](const string& dir)
		{
			return (('u' == dir[0]) || ('l' == dir[0]));

		});

		if (end_pos != end(possible_path_directions)) possible_path_directions.erase(end_pos, end(possible_path_directions));

	}

	auto end_pos = remove_if(begin(possible_path_directions), end(possible_path_directions), [&path](const string& dir)
	{
		string potential_path_way{ path };

		for (size_t x{}, y{}; x < path.length(); x++)
		{
			if ('?' == path[x]) {
				potential_path_way[x] = dir[y];
				y++;
			}
		}

		int r_count{};
		int l_count{};
		int d_count{};
		int u_count{};

		char prev_dir{};
		bool correct_path{ true };

		for (const auto c : potential_path_way)
		{
			if (c == 'r') {

				if ('l' == prev_dir)
				{
					correct_path = false;
					break;
				}

				r_count++;
				prev_dir = 'r';
				continue;
			}

			if (c == 'l') {

				if ('r' == prev_dir)
				{
					correct_path = false;
					break;
				}

				l_count++;
				prev_dir = 'l';
				continue;
			}

			if (c == 'd') {

				if ('u' == prev_dir)
				{
					correct_path = false;
					break;
				}

				d_count++;
				prev_dir = 'd';
				continue;
			}

			if (c == 'u') {

				if ('d' == prev_dir)
				{
					correct_path = false;
					break;
				}

				u_count++;
				prev_dir = 'u';
			}
		}

		if (!correct_path) return true;
		if ((r_count - l_count) != 4) return true;
		if ((d_count - u_count) != 4) return true;

		return false;

	});

	if (end_pos != end(possible_path_directions)) possible_path_directions.erase(end_pos, end(possible_path_directions));

	return possible_path_directions;

}

bool get_next_path(string& next_path, const vector<string>& possible_path_directions)
{
	static size_t counter{};

	if (possible_path_directions.size() == counter) return false;

	for (size_t i{}, j{}; i < next_path.length(); i++)
	{
		if ('?' == next_path[i]) {
			next_path[i] = possible_path_directions[counter][j];
			j++;
		}
	}

	counter++;

	return true;

}

string CorrectPath(const string& str) {

	vector<set<char>> allowed_directions{};

	const string path = [&str]()
	{
		string correct_path{ str };

		for (auto& ch : correct_path) ch = static_cast<char>(tolower(ch));

		return correct_path;
	}();

	for (size_t i{}; i < path.length(); i++) {

		switch (path[i]) {

		case '?':

			if (0u == i)allowed_directions.emplace_back(set<char>{ 'r', 'd' });

			else allowed_directions.emplace_back(set<char>{ 'r', 'd', 'u', 'l' });

			break;

		case 'u':


			allowed_directions.emplace_back(set<char>{ 'u' });

			break;

		case 'd':

			allowed_directions.emplace_back(set<char>{ 'd' });

			break;

		case 'r':

			allowed_directions.emplace_back(set<char>{ 'r' });

			break;

		case 'l':

			allowed_directions.emplace_back(set<char>{ 'l' });

			break;

		default:

			break;

		}

	}

	const auto& all_potential_directions = get_possible_path_directions(path, allowed_directions);

	while (true) {

		array<array<bool, 5>, 5> pw{ {} };

		pw[0u][0u] = true;

		string current_path{ path };

		if (!get_next_path(current_path, all_potential_directions)) return string{ "error" };

		bool is_wrong_path{};

		size_t xi{}, yi{};

		for (const auto dir : current_path)
		{
			switch (dir)
			{
			case 'l':
				if ((0 == yi) || pw[xi][yi - 1u]) {
					is_wrong_path = true;
				}
				else
				{
					yi--;
					pw[xi][yi] = true;
				}
				break;

			case 'r':
				if ((4u == yi) || pw[xi][yi + 1u]) {
					is_wrong_path = true;
				}
				else
				{
					yi++;
					pw[xi][yi] = true;
				}
				break;

			case 'u':
				if ((0u == xi) || pw[xi - 1u][yi]) {
					is_wrong_path = true;
				}
				else
				{
					xi--;
					pw[xi][yi] = true;
				}
				break;

			case 'd':
				if ((4u == xi) || pw[xi + 1u][yi]) {
					is_wrong_path = true;
				}
				else
				{
					xi++;
					pw[xi][yi] = true;
				}
				break;

			default:
				break;

			}

			if (is_wrong_path) break;

		}

		if (!is_wrong_path && (4u == xi) && (4u == yi)) return current_path;

	}

}

int main() {

	cout << CorrectPath("???rrurdr?"); // expected output: "dddrrurdrd"
	// cout << CorrectPath(gets(stdin));

	return 0;

}

// str: string of characters or digits
void generate_all(const string& str, const int k)
{
	const int n = str.length();

	// initialization of the first subset containing k elements
	const auto sub_tab = new int[k];

	for (int j{ 0 }; j < k; ++j)
	{
		sub_tab[j] = j;
	}

	do
	{
		// Convert combination to string
		const auto sub_str = new char[k];

		for (int j{ 0 }; j < k; ++j)
		{
			sub_str[j] = str[sub_tab[j]];
		}
		// Print combinations of each set
		combinations(sub_str);
		// get next sub string
	} while (add_one(sub_tab, k - 1, n) == true);

	delete[] sub_tab;
}

void combinations(const string& str)
{
	const int n = str.length();

	// Compute all factorials from 0 to n
	const auto factorials = new unsigned long[n + 1];
	factorials[0] = 1;
	for (int i{ 1 }; i <= n; ++i)
		factorials[i] = factorials[i - 1] * i;

	const auto tab = new char[n];

	// Initialization with the first combination 0123...n-1
	for (int i{ 0 }; i < n; ++i)
	{
		tab[i] = static_cast<char>(i);
		cout << str[i] << " ";
	}
	cout << endl;

	for (unsigned long int i(1); i < factorials[n]; ++i)
	{
		for (int j{ 0 }; j < n; ++j)
		{
			if (i % factorials[n - j - 1] == 0)
			{
				// increment tab[j] (or find the next available)
				set_next_available(tab, j, n);
			}
		}
		for (int j{ 0 }; j < n; ++j)
		{
			cout << str[tab[j]] << " ";
		}
		cout << endl;
	}

	delete[] factorials;
}

void set_next_available(char *tab, const int j, const int n)
{
	bool finished;
	do
	{
		finished = true;
		++(*(tab + j));
		if (*(tab + j) == n) *(tab + j) = 0;
		for (int i{ 0 }; i < j; ++i)
		{
			if (*(tab + i) == *(tab + j))
			{
				finished = false;
				break;
			}
		}
	} while (finished == false);
}

bool add_one(int *tab, const int k, const int n)
{
	int i;
	for (i = k; i >= 0; --i)
	{
		if (++tab[i] + k - i != n)
			break;
	}
	if (i == -1)
		return false;

	for (int j = i + 1; j <= k; ++j)
	{
		tab[j] = tab[j - 1] + 1;
	}

	return true;

}

void find_all_string_combinations_for_k_length(const string& set, const size_t k, vector<string>& word_combinations) {

	const size_t n{ set.length() };
	collect_all_k_length_words(set, "", n, k, word_combinations);
}

// The main recursive method to print all possible strings of length k
void collect_all_k_length_words(const string& set, const string& prefix, const size_t n, const size_t k, vector<string>& word_combinations) {
	// Base case: k is 0, print prefix 

	if (k == 0) {
		word_combinations.emplace_back(prefix);
		return;
	}

	// One by one add all characters from set and recursively 
	// call for k equals to k-1
	for (size_t i{}; i < n; ++i) {

		// Next character of input added
		const string new_prefix{ prefix + set[i] };

		// k is decreased, because we have added a new character
		collect_all_k_length_words(set, new_prefix, n, k - 1, word_combinations);
	}
}
