/*
Coderbyte coding challenge: Scale Balancing

Using the C++ language, have the function ScaleBalancing(strArr) read strArr which will contain two elements, the first being the two positive integer weights 
on a balance scale (left and right sides) and the second element being a list of available weights as positive integers. 
Your goal is to determine if you can balance the scale by using the least amount of weights from the list, but using at most only 2 weights. 
For example: if strArr is ["[5, 9]", "[1, 2, 6, 7]"] then this means there is a balance scale with a weight of 5 on the left side and 9 on the right side. 
It is in fact possible to balance this scale by adding a 6 to the left side from the list of weights and adding a 2 to the right side. 
Both scales will now equal 11 and they are perfectly balanced. 
Your program should return a common separated string of the weights that were used from the list in ascending order, 
so for this example your program should return the string 2,6

There will only ever be one unique solution and the list of available weights will not be empty. 
It is also possible to add two weights to only one side of the scale to balance it. 
If it is not possible to balance the scale then your program should return the string not possible.

Sample test cases:

Input:  "[3, 4]", "[1, 2, 7, 7]"
Output: "1"

Input:  "[13, 4]", "[1, 2, 3, 6, 14]"
Output: "3,6"
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <functional>
#include <cctype>

using namespace std;

string trim(const string& str)
{
  size_t begin_str{};
  size_t end_str{str.size() - 1};

  if (0u == str.length()) return string{};

  for (; begin_str <= end_str; ++begin_str)
  {
    if (!isspace(str[begin_str])) break;
  }

  if (begin_str > end_str) return string{};

  for (; end_str > begin_str; --end_str)
  {
    if (!isspace(str[end_str])) break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

vector<string> split(const string& source, const char* needle,
                              size_t const max_count = string::npos)
{
	vector<string> parts{};			

	string needle_st{needle};

	const size_t source_len{source.length()};
	const size_t needle_len{needle_st.length()};

	if ((0u == source_len) || (0u == needle_len)) return parts;

	size_t number_of_parts{}, prev{};

	while (true)
	{
		const size_t current { source.find(needle_st, prev) };

		if (string::npos == current) break;

		number_of_parts++;

		if ((string::npos != max_count) && (parts.size() == max_count)) break;

		if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source_len) break;
	}

	if (prev < source_len)
	{
		if (string::npos == max_count) parts.emplace_back(source.substr(prev));

		else if ((string::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
	}

	return parts;
}

string get_needed_weights_string(const size_t first_weight, const size_t second_weight) {

	ostringstream oss{};

	if (first_weight < second_weight) {

		oss << first_weight << ',' << second_weight;		

	} else {

		oss << second_weight << ',' << first_weight;

	}	

	return oss.str();
}

string ScaleBalancing(string *str_arr, const size_t array_size) {

	if (array_size < 2u) return string { "not possible" };

	str_arr[0] = trim(str_arr[0]);
	str_arr[0].erase(begin(str_arr[0]));
	str_arr[0].erase(--end(str_arr[0]));

	auto left_right_scale_str = split(str_arr[0], ",");	
	for (auto& str : left_right_scale_str) str = trim(str);
	if (2u != left_right_scale_str.size()) return string{"not possible"};

	const size_t left_scale = stoul(left_right_scale_str[0]);
	const size_t right_scale = stoul(left_right_scale_str[1]);
	if (left_scale == right_scale) return string{"scale already balanced"};

	str_arr[1] = trim(str_arr[1]);
	str_arr[1].erase(begin(str_arr[1]));
	str_arr[1].erase(--end(str_arr[1]));

	auto weights_str = split(str_arr[1], ",");
	for (auto& str : weights_str) str = trim(str);

	multiset<size_t, greater<size_t>> aw{};
	for (const auto& weight_str : weights_str) aw.insert(stoul(weight_str));

	const size_t needed_extra_weight = left_scale > right_scale ? left_scale - right_scale : right_scale - left_scale;

	const auto found_needed_weight = aw.find(needed_extra_weight);

	if (found_needed_weight != end(aw)) {

		return to_string(*found_needed_weight);
	}

	size_t first_weight = 0u;

	for (auto start = begin(aw); start != end(aw); ++start) {

		if (*start > needed_extra_weight) continue;

		const size_t cw{ *start };

		if (!first_weight) {

			first_weight = cw;

			continue;
		}

		if ((first_weight + cw) == needed_extra_weight) {

			return get_needed_weights_string(first_weight, cw);

		}

	}

	multiset<size_t> aw_less(begin(aw), end(aw));

	for (auto start1 = begin(aw_less); start1 != end(aw_less); ++start1) {

		for (auto start2 = begin(aw_less); start2 != end(aw_less); ++start2) {

			if ((left_scale + *start1) == (right_scale + *start2)) {

				return get_needed_weights_string(*start1, *start2);

			}

			if ((left_scale + *start2) == (right_scale + *start1)) {

				return get_needed_weights_string(*start2, *start1);

			}			

		}

	}

	return string{ "not possible" };
}

int main() {

	// string a[] = gets(stdin);
	string a[] = { "[3, 4]", "[1, 2, 7, 7]" };
	cout << ScaleBalancing(a, sizeof(a) / sizeof(*a)) << '\n';
	string b[] = { "[13, 4]", "[1, 2, 3, 6, 14]" };
	cout << ScaleBalancing(b, sizeof(b) / sizeof(*b)) << '\n';
	string c[] = { "[5, 9]", "[1, 2, 6, 7]" };
	cout << ScaleBalancing(c, sizeof(c) / sizeof(*c)) << '\n';
	string d[] = { "[6, 2]", "[1, 10, 6, 5]" };
	cout << ScaleBalancing(d, sizeof(d) / sizeof(*d)) << '\n';
	return 0;
}
