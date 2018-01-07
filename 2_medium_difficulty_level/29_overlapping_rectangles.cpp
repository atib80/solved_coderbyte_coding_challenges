/*
Coderbyte coding challenge: Overlapping Rectangles

Using the C++ language, have the function OverlappingRectangles(strArr) read the strArr parameter being passed which will represent two rectangles 
on a Cartesian coordinate plane and will contain 8 coordinates with the first 4 making up rectangle 1 and the last 4 making up rectange 2. 
It will be in the following format: ["(0,0),(2,2),(2,0),(0,2),(1,0),(1,2),(6,0),(6,2)"] 
Your program should determine the area of the space where the two rectangles overlap, 
and then output the number of times this overlapping region can fit into the first rectangle. 
For the above example, the overlapping region makes up a rectangle of area 2, and the first rectangle (the first 4 coordinates) makes up a rectangle of area 4, 
so your program should output 2. The coordinates will all be integers. If there's no overlap between the two rectangles return 0.

Sample test cases:

Input:  "(0,0),(0,-2),(3,0),(3,-2),(2,-1),(3,-1),(2,3),(3,3)"
Output: 6

Input:  "(0,0),(5,0),(0,2),(5,2),(2,1),(5,1),(2,-1),(5,-1)"
Output: 3
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
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

	istringstream iss{str};

	int x{}, y{};
	char ch;

	iss >> x >> ch >> y;

	return make_pair(x, y);

}

string OverlappingRectangles(string* str_arr, const size_t str_arr_size) { 

  if (str_arr_size < 1u) return string{"Not possible!"};  

  vector<string> coordinates_str = split(str_arr[0], "),(");

  if (8u != coordinates_str.size()) return string{"Not possible!"};

  for (auto& str : coordinates_str) str = trim(str);

  coordinates_str[0].erase(begin(coordinates_str[0]));

  coordinates_str[7].erase(--end(coordinates_str[7]));  

  vector<pair<int, int>> first_rectangle_coordinates{};
  vector<pair<int, int>> second_rectangle_coordinates{};

  for (size_t i{}, j{4u}; i != 4; i++, j++) { 
  	first_rectangle_coordinates.emplace_back(parse_x_y_coordinates(coordinates_str[i]));
  	second_rectangle_coordinates.emplace_back(parse_x_y_coordinates(coordinates_str[j]));
  }  

  set<int, greater<int>> first_rectangle_x_coordinates{};
  set<int, greater<int>> first_rectangle_y_coordinates{};
  set<int, greater<int>> second_rectangle_x_coordinates{};
  set<int, greater<int>> second_rectangle_y_coordinates{};
  
  for (size_t i{}; i != 4; i++) {
  	first_rectangle_x_coordinates.insert(first_rectangle_coordinates[i].first);
  	first_rectangle_y_coordinates.insert(first_rectangle_coordinates[i].second);
  	second_rectangle_x_coordinates.insert(second_rectangle_coordinates[i].first);
  	second_rectangle_y_coordinates.insert(second_rectangle_coordinates[i].second);
  }

  auto start_itr = begin(first_rectangle_x_coordinates);
  const int max_x1{*start_itr};
  ++start_itr;
  const int min_x1{*start_itr};

  start_itr = begin(second_rectangle_x_coordinates);
  const int max_x2{*start_itr};
  ++start_itr;
  const int min_x2{*start_itr}; 

  start_itr = begin(first_rectangle_y_coordinates);
  const int max_y1{*start_itr};
  ++start_itr;
  const int min_y1{*start_itr}; 

  start_itr = begin(second_rectangle_y_coordinates);
  const int max_y2{*start_itr};
  ++start_itr;
  const int min_y2{*start_itr};

  if ((max_x1 <= min_x2) || (max_y1 <= min_y2)) return "0"; 

  if ((max_x2 <= min_x1) || (max_y2 <= min_y1)) return "0";  

  const int first_rectangle_area{ abs(max_x1 - min_x1) * abs(max_y1 - min_y1) };

  vector<int> overlapped_rectangle_x_coord{min_x1, max_x1, min_x2, max_x2};

  sort(begin(overlapped_rectangle_x_coord), end(overlapped_rectangle_x_coord));

  vector<int> overlapped_rectangle_y_coord{min_y1, max_y1, min_y2, max_y2};

  sort(begin(overlapped_rectangle_y_coord), end(overlapped_rectangle_y_coord));

  const int overlapped_rectangle_area{ abs(overlapped_rectangle_x_coord[2] - overlapped_rectangle_x_coord[1]) * abs(overlapped_rectangle_y_coord[2] - overlapped_rectangle_y_coord[1]) };

  return to_string(first_rectangle_area/overlapped_rectangle_area); 
            
}

int main() { 
 
  // string A[] = gets(stdin);
  // cout << OverlappingRectangles(A, sizeof(A)/sizeof(*A));
  string B[] = {"(0,0),(2,2),(2,0),(0,2),(1,0),(1,2),(6,0),(6,2)"};
  cout << OverlappingRectangles(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 2
  string C[] = {"(0,0),(0,-2),(3,0),(3,-2),(2,-1),(3,-1),(2,3),(3,3)"};
  cout << OverlappingRectangles(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 6
  string D[] = {"(0,0),(5,0),(0,2),(5,2),(2,1),(5,1),(2,-1),(5,-1)"};
  cout << OverlappingRectangles(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 3  
  
  return 0;

}
