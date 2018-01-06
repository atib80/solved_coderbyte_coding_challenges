/*
Coderbyte coding challenge: Closest Enemy II

Using the C++ language, have the function ClosestEnemyII(strArr) read the matrix of numbers stored in strArr which will be a 2D matrix 
that contains only the integers 1, 0, or 2. Then from the position in the matrix where a 1 is, return the number of spaces either left, right, down, or up 
you must move to reach an enemy which is represented by a 2. You are able to wrap around one side of the matrix to the other as well. 
For example: if strArr is ["0000", "1000", "0002", "0002"] then this looks like the following:

0 0 0 0
1 0 0 0
0 0 0 2
0 0 0 2

For this input your program should return 2 because the closest enemy (2) is 2 spaces away from the 1 by moving left to wrap to the other side and then moving down once. 
The array will contain any number of 0's and 2's, but only a single 1. It may not contain any 2's at all as well, where in that case your program should return a 0.

Sample test cases:

Input:  "000", "100", "200"
Output: 1

Input:  "0000", "2010", "0000", "2002"
Output: 2
*/

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

size_t abs_diff(const size_t x, const size_t y)
{
	return (x < y ? y - x : x - y);
}

size_t find_closest_distance_to_enemy(const pair<size_t, size_t>& one_pos, const pair<size_t, size_t>& enemy_pos,
                                      const size_t row_size, const size_t column_size)
{
	vector<size_t> distances{};

	const size_t one_x{one_pos.first};
	const size_t one_y{one_pos.second};
	const size_t enemy_x{enemy_pos.first};
	const size_t enemy_y{enemy_pos.second};

	distances.emplace_back(abs_diff(enemy_x, one_x) + abs_diff(enemy_y, one_y));

	size_t row_dist2, column_dist2;

	if (one_x < enemy_x)
	{
		row_dist2 = one_x + row_size - enemy_x;
		distances.emplace_back(row_dist2 + abs_diff(enemy_y, one_y));
	}
	else if (one_x > enemy_x)
	{
		row_dist2 = row_size - one_x + enemy_x;
		distances.emplace_back(row_dist2 + abs_diff(one_y, enemy_y));
	}

	if (one_y < enemy_y)
	{
		column_dist2 = one_y + column_size - enemy_y;
		distances.emplace_back(column_dist2 + abs_diff(enemy_x, one_x));
	}
	else if (one_y > enemy_y)
	{
		column_dist2 = column_size - one_y + enemy_y;
		distances.emplace_back(column_dist2 + abs_diff(one_x, enemy_x));
	}

	size_t current_min_distance{distances[0]};

	for (size_t i{1u}; i < distances.size(); i++)
	{
		if (distances[i] < current_min_distance) current_min_distance = distances[i];
	}

	return current_min_distance;
}

size_t find_distance_to_closest_enemy_position(const pair<size_t, size_t>& one_pos,
                                               const vector<pair<size_t, size_t>>& two_pos, const size_t row_count,
                                               const size_t col_count)
{
	vector<size_t> distances{};

	for (const auto& enemy_pos : two_pos)
	{
		distances.emplace_back(find_closest_distance_to_enemy(one_pos, enemy_pos, row_count, col_count));
	}

	size_t current_min_steps{distances[0]};

	for (size_t i{1u}; i < distances.size(); i++)
	{
		if (distances[i] < current_min_steps) current_min_steps = distances[i];
	}

	return current_min_steps;
}

string closest_enemy_ii(const string* str_array, const size_t str_array_size)
{
	bool found_one{false}, found_twos{false};
	pair<size_t, size_t> one_position{};
	vector<pair<size_t, size_t>> enemy_positions{};

	for (size_t i{}; i != str_array_size; i++)
	{
		for (size_t j{}; j != str_array[i].length(); j++)
		{
			if ('2' == str_array[i][j])
			{
				enemy_positions.emplace_back(make_pair(i, j));
				found_twos = true;
				continue;
			}

			if (!found_one && ('1' == str_array[i][j]))
			{
				one_position = make_pair(i, j);
				found_one = true;
			}
		}
	}

	if (!found_one || !found_twos) return string{"0"};

	return to_string(
		find_distance_to_closest_enemy_position(one_position, enemy_positions, str_array_size, str_array_size));
}

int main()
{

	// const string matrix[] = gets(stdin);
	// cout << closest_enemy_ii(matrix, sizeof(matrix) / sizeof(matrix[0]));

	const string m1[] = {"10", "02"}; 
	cout << closest_enemy_ii(m1, sizeof(m1) / sizeof(m1[0])) << '\n'; // expected output: 2
    
    const string m2[] = {"00000", "10000", "00000", "00002", "02002"}; 
	cout << closest_enemy_ii(m2, sizeof(m2) / sizeof(m2[0])) << '\n'; // expected output: 3

	const string m3[] = {"0000000", "0001000", "0000000", "0000000", "0000000", "2000000", "0000000"};
	cout << closest_enemy_ii(m3, sizeof(m3) / sizeof(m3[0])) << '\n'; // expected output: 6
	
	const string m4[] = { "0000", "1000", "0002", "0002" };
	cout << closest_enemy_ii(m4, sizeof(m4)/sizeof(m4[0])) << '\n'; // expected output: 2

	const string m5[] = { "000", "100", "200" };
	cout << closest_enemy_ii(m5, sizeof(m5) / sizeof(m5[0])) << '\n'; // expected output: 1

	const string m6[] = { "0000", "2010", "0000", "2002" };
	cout << closest_enemy_ii(m6, sizeof(m6) / sizeof(m6[0])) << '\n'; // expected output: 2

	return 0;
}
