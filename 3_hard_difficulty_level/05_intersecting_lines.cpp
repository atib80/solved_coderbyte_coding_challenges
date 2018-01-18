/*
Coderbyte coding challenge: Intersecting Lines

Using the C++ language, have the function IntersectingLines(strArr) take strArr which will be an array of 4 coordinates in the form: (x,y). 
Your program should take these points where the first 2 form a line and the last 2 form a line, and determine whether the lines intersect, 
and if they do, at what point. 
For example: if strArr is ["(3,0)","(1,4)","(0,-3)","(2,3)"], then the line created by (3,0) and (1,4) and the line created by (0,-3) (2,3) intersect at (9/5,12/5). 
Your output should therefore be the 2 points in fraction form in the following format: (9/5,12/5). 
If there is no denominator for the resulting points, then the output should just be the integers like so: (12,3). 
If any of the resulting points is negative, add the negative sign to the numerator like so: (-491/63,-491/67). 
If there is no intersection, your output should return the string "no intersection". 
The input points and the resulting points can be positive or negative integers.

Sample test cases:

Input:  "(9,-2)","(-2,9)","(3,4)","(10,11)"
Output: "(3,4)"

Input:  "(1,2)","(3,4)","(-5,-6)","(-7,-8)"
Output: "no intersection"
*/

#include <iostream>
#include <sstream>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

string trim(const string& str)
{
  const size_t str_len{ str.length() };

  if (!str_len) return string{};

  size_t first{}, last{ str_len - 1 };

  for (; first <= last; ++first)
  {
    if (!isspace(str[first])) break;
  }

  if (first > last) return string{};

  for (; last > first; --last)
  {
    if (!isspace(str[last])) break;
  }

  return str.substr(first, last - first + 1);
}

vector<string> split(const string& source, const char* needle, size_t const max_count = string::npos)
{
	vector<string> parts{};

	string needle_st{ needle };

	const size_t source_len{ source.length() };

	const size_t needle_len{ needle_st.size() };

	if ((0u == source_len) || (0u == needle_len)) return parts;

	size_t number_of_parts{}, prev{};

	while (true)
	{
		const size_t current{ source.find(needle_st, prev) };

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

 // example for str_arr: { "(3,0)","(1,4)","(0,-3)","(2,3)" }, str_arr_size = 4

vector<pair<int, int>> parse_2d_coordinate_pairs(string* str_arr, const size_t str_arr_size) {

	vector<pair<int, int>> coordinates{};

	for (size_t i{}; i < str_arr_size; i++) {

		str_arr[i] = trim(str_arr[i]);

		str_arr[i].erase(begin(str_arr[i]));

		str_arr[i].erase(--end(str_arr[i]));

		auto const number_parts = split(str_arr[i], ",");

		if (2u != number_parts.size()) return vector<pair<int, int>>{};

		coordinates.emplace_back(make_pair(stoi(number_parts[0]), stoi(number_parts[1])));
	}

	return coordinates;
}

pair<int, int> factorize_rational_number(int nominator, int denominator) {

	const bool is_rational_number_negative { (((nominator < 0) && (denominator > 0)) || ((nominator > 0) && (denominator < 0))) };
	
	nominator = abs(nominator);

	denominator = abs(denominator);

	const int min_number { min(nominator, denominator) };

	for (int i{min_number}; i > 1; i--) {

		if ( ( nominator % i == 0) && (denominator % i == 0 ) ) {

			nominator /= i;

			denominator /= i;

			if (is_rational_number_negative) nominator = -nominator;

			return make_pair(nominator, denominator);
		}

	}

	if (is_rational_number_negative) nominator = -nominator;

	return make_pair(nominator, denominator);
}

string find_intersection_point_coordinates_of_two_lines(const pair<int, int>& A, const pair<int, int>& B, const pair<int, int>& C, const pair<int, int>& D) {

    // Line 'AB' represented as a1x + b1y = c1
    const int a1 { B.second - A.second };
    const int b1 { A.first - B.first };
    const int c1 { a1 * A.first + b1 * A.second };
  
    // Line 'CD' represented as a2x + b2y = c2
    const int a2 { D.second - C.second };
    const int b2 { C.first - D.first };
    const int c2 { a2 * C.first + b2 * C.second };
  
    const int determinant { a1 * b2 - a2 * b1 };
  
    if (!determinant) return "no intersection";

    ostringstream oss{};

    const int x{b2 * c1 - b1 * c2};

    if ((x % determinant) != 0) {
    	const auto frn = factorize_rational_number(x, determinant);
    	oss << '(' << frn.first << '/' << frn.second << ',';
	} else {
		oss << '(' << (x / determinant) << ',';
	}

	const int y{a1 * c2 - a2 * c1};

	if ((y % determinant) != 0) {
    	const auto frn = factorize_rational_number(y, determinant);
    	oss << frn.first << '/' << frn.second << ')';
	} else {
		oss << (y / determinant) << ')';
	}
    
    return oss.str();
}

string IntersectingLines(string *str_arr, const size_t str_arr_size) {

  const auto points = parse_2d_coordinate_pairs(str_arr, str_arr_size);

  if (4u != points.size()) return "no intersection";
  
  return find_intersection_point_coordinates_of_two_lines(points[0], points[1], points[2], points[3]);

}

int main() { 
   
  string A[] = gets(stdin);
  cout << IntersectingLines(A, sizeof(A)/sizeof(*A));
  // string b[] = {"(3,0)","(1,4)","(0,-3)","(2,3)"};
  // cout << IntersectingLines(b, sizeof(b)/sizeof(*b)) << '\n'; // expected output: "(9/5,12/5)"
  // string c[] = {"(9,-2)","(-2,9)","(3,4)","(10,11)"};
  // cout << IntersectingLines(c, sizeof(c)/sizeof(*c)) << '\n'; // expected output: "(3,4)"
  // string d[] = {"(1,2)","(3,4)","(-5,-6)","(-7,-8)"};
  // cout << IntersectingLines(d, sizeof(d)/sizeof(*d)) << '\n'; // expected output: "no intersection"

  return 0;    
} 
