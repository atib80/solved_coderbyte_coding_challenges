/*
Coderbyte coding challenge: Gas Station

Using the C++ language, have the function GasStation(strArr) take strArr which
will be an an array consisting of the following elements: N which will be the
number of gas stations in a circular route and each subsequent element will be
the string g:c where g is the amount of gas in gallons at that gas station and c
will be the amount of gallons of gas needed to get to the following gas station.
For example strArr may be: ["4","3:1","2:2","1:2","0:1"].
Your goal is to return the index of the starting gas station that will allow you
to travel around the whole route once, otherwise return the string impossible.
For the example above, there are 4 gas stations, and your program should return
the string 1 because starting at station 1 you receive 3 gallons of gas and
spend 1 getting to the next station. Then you have 2 gallons + 2 more at the
next station and you spend 2 so you have 2 gallons when you get to the 3rd
station. You then have 3 but you spend 2 getting to the final station, and at
the final station you receive 0 gallons and you spend your final gallon getting
to your starting point. Starting at any other gas station would make getting
around the route impossible, so the answer is 1. If there are multiple gas
stations that are possible to start at, return the smallest index (of the gas
station). N will be >= 2.

Sample test cases:

Input:  "4","1:1","2:2","1:2","0:1"
Output: "impossible"

Input:  "4","0:1","2:2","1:2","3:1"
Output: "4"
*/

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str)
{
	const size_t str_len{str.length()};

	if (!str_len)
		return string{};

	size_t first{}, last{str_len - 1};

	for (; first <= last; ++first)
	{
		if (!isspace(str[first]))
			break;
	}

	if (first > last)
		return string{};

	for (; last > first; --last)
	{
		if (!isspace(str[last]))
			break;
	}

	return str.substr(first, last - first + 1);
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos)
{
	vector<string> parts{};

	string needle_st{needle};

	const size_t source_len{source.length()};

	const size_t needle_len{needle_st.size()};

	if ((0u == source_len) || (0u == needle_len))
		return parts;

	size_t number_of_parts{}, prev{};

	while (true)
	{
		const size_t current{source.find(needle_st, prev)};

		if (string::npos == current)
			break;

		number_of_parts++;

		if ((string::npos != max_count) && (parts.size() == max_count))
			break;

		if ((current - prev) > 0)
			parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source_len)
			break;
	}

	if (prev < source_len)
	{
		if (string::npos == max_count)
			parts.emplace_back(source.substr(prev));

		else if ((string::npos != max_count) && (parts.size() < max_count))
			parts.emplace_back(source.substr(prev));
	}

	return parts;
}

string GasStation(string* str_arr, const size_t str_arr_size)
{
	const size_t N{stoul(trim(*str_arr))};

	vector<pair<int, int>> gas_stations(N);

	for (size_t i{1u}; i < str_arr_size; i++)
	{
		if (i > N)
			break;

		str_arr[i] = trim(str_arr[i]);

		auto g_c_parts = split(str_arr[i], ":", 2);

		gas_stations[i - 1] = make_pair(stoi(g_c_parts[0]), stoi(g_c_parts[1]));
	}

	for (size_t i{}; i < N; i++)
	{
		size_t ci{i};

		int gallons{};

		while (true)
		{
			gallons += gas_stations[ci].first;

			if (gas_stations[ci].second > gallons)
				break;

			gallons -= gas_stations[ci].second;

			ci = (ci + 1 >= N) ? 0 : ci + 1;

			if (ci == i)
				return to_string(i + 1);
		}
	}

	return "impossible";
}

int main()
{
	// string A[] = gets(stdin);
	// cout << GasStation(A, sizeof(A)/sizeof(*A));
	string B[] = {"4", "3:1", "2:2", "1:2", "0:1"};
	cout << GasStation(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: "1"
	string C[] = {"4", "1:1", "2:2", "1:2", "0:1"};
	cout << GasStation(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: "impossible"
	string D[] = {"4", "0:1", "2:2", "1:2", "3:1"};
	cout << GasStation(D, sizeof(D) / sizeof(*D)) << '\n'; // expected output: "4"

	return 0;
}
