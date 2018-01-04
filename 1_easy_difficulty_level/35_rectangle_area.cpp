/*
Coderbyte coding challenge: Rectangle Area
Using the C++ language, have the function RectangleArea(strArr) take the array of strings stored in strArr, which will only contain 4 elements and be in the form (x y) 
where x and y are both integers, and return the area of the rectangle formed by the 4 points on a Cartesian grid. The 4 elements will be in arbitrary order. 
For example: if strArr is ["(0 0)", "(3 0)", "(0 2)", "(3 2)"] then your program should return 6 because the width of the rectangle is 3 and the height is 2 
and the area of a rectangle is equal to the width * height.

Sample test cases:

Input:  "(1 1)","(1 3)","(3 1)","(3 3)"
Output: 4

Input:  "(0 0)","(1 0)","(1 1)","(0 1)"
Output: 1
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <functional>

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


vector<string> split(const string& source, const char* needle, size_t const max_count = string::npos)
{
  vector<string> parts{}; 

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len)) return parts;

  size_t number_of_parts{}, prev{};

  while (true)
  {
    const size_t current = source.find(needle_st, prev);

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

pair<int, int> parse_x_y_coordinates(const string& str) {

	istringstream iss{trim(str)};

	int x{}, y{};
	char ch;

	iss >> ch >> x >> y >> ch;

	return make_pair(x, y);

}

string RectangleArea(vector<string> xy_coordinate_pairs) { 

  if (xy_coordinate_pairs.size() != 4u) return string{"Not possible!"};

  vector<pair<int, int>> coordinates{};

  for (const auto& xy_str : xy_coordinate_pairs) { 
  	coordinates.emplace_back(parse_x_y_coordinates(xy_str));
  }

  set<int, greater<int>> x_coordinates{};
  set<int, greater<int>> y_coordinates{};
  
  for (const auto& xy_pair : coordinates) {
  	x_coordinates.insert(xy_pair.first);
  	y_coordinates.insert(xy_pair.second);
  }

  if (1u == x_coordinates.size() || 1u == y_coordinates.size()) return "0";

  auto first_x = begin(x_coordinates);
  auto second_x = first_x;
  ++second_x;
  const int width { abs( *first_x - *second_x ) };

  auto first_y = begin(y_coordinates);
  auto second_y = first_y;
  ++second_y;
  const int height { abs( *first_y - *second_y) };

  return to_string(width * height);
}

int main() { 
   
  // cout << RectangleArea(move(vector<string>{gets(stdin)}));
  cout << RectangleArea(move(vector<string>{ "(0 0)", "(3 0)", "(0 2)", "(3 2)" })) << '\n';    // expected output: "6"
  cout << RectangleArea(move(vector<string>{ "(1 1)", "(1 3)", "(3 1)", "(3 3)" })) << '\n';    // expected output: "4"
  cout << RectangleArea(move(vector<string>{ "(0 0)", "(1 0)", "(1 1)", "(0 1)" })) << '\n';    // expected output: "1"
  
  return 0;

}
