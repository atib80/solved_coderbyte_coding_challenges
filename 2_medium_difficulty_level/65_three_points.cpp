/*
Coderbyte coding challenge: Three Points

Using the C++ language, have the function ThreePoints(strArr) read the array of strings stored in strArr which will always contain 3 elements and be in the form: 
["(x1,y1)", "(x2,y2)", "(x3,y3)"]. Your goal is to first create a line formed by the first two points (that starts from the first point and moves in the direction 
of the second point and that stretches in both directions through the two points), and then determine what side of the line point 3 is on. 
The result will either be right, left, or neither. For example: if strArr is ["(1,1)", "(3,3)", "(2,0)"] then your program should return the string right 
because the third point lies to the right of the line formed by the first two points.

Sample test cases:

Input:  "(0,-3)", "(-2,0)", "(0,0)"
Output: "right"

Input:  "(0,0)", "(0,5)", "(0,2)"
Output: "neither"
*/

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <climits>

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

pair<int, int> parse_x_y_coordinate_pair(const string& position) {

	size_t start { position.find_first_of("-+0123456789") };

	if (string::npos == start) return make_pair(INT_MIN, INT_MIN);

	size_t last { position.find_first_not_of("-+0123456789", start + 1) };

	if (string::npos == last) return make_pair(INT_MIN, INT_MIN);
	
	const int x { stoi(position.substr(start, last - start)) };

	start = position.find_first_of("-+0123456789", last + 1);

	if (string::npos == start) return make_pair(INT_MIN, INT_MIN);

	last = position.find_first_not_of("-+0123456789", start + 1);

	if (string::npos == last) return make_pair(INT_MIN, INT_MIN);
	
	const int y { stoi(position.substr(start, last - start)) };

	return make_pair(x, y);
}

string ThreePoints(string* str_arr, const size_t str_arr_size) {

  if (str_arr_size < 3u) return "not possible";

  for (size_t i{}; i != str_arr_size; i++) str_arr[i] = trim(str_arr[i]);

  const pair<int, int> A {parse_x_y_coordinate_pair(str_arr[0]) };

  if (INT_MIN == A.first || INT_MIN == A.second) return "not possible";

  const pair<int, int> B {parse_x_y_coordinate_pair(str_arr[1]) };

  if (INT_MIN == B.first || INT_MIN == B.second) return "not possible";

  const pair<int, int> C {parse_x_y_coordinate_pair(str_arr[2]) };

  if (INT_MIN == C.first || INT_MIN == C.second) return "not possible";

  if (((A.first == B.first) && (B.first == C.first)) || ((A.second == B.second) && (B.second == C.second))) return "neither";

  const int a { A.second - B.second }; // a = y1 - y2
 
  const int b { B.first - A.first };   // b = x2 - x1

  const int c { (a * A.first) + (b * A.second) }; // c = a * x1 + b * y1

  if (((a * C.first) + (b * C.second) - c) > 0) return "left";  // if (a * x3 + b * y3 - c > 0) return "left";

  if (((a * C.first) + (b * C.second) - c) < 0) return "right"; // if (a * x3 + b * y3 - c < 0) return "right";

  return "neither";
  
}

int main() { 
   
  // string A[] = gets(stdin);
  // cout << ThreePoints(A, sizeof(A)/sizeof(*A));
  string B[] = {"(1,1)", "(3,3)", "(2,0)"};
  cout << ThreePoints(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "right"
  string C[] = {"(0,-3)", "(-2,0)", "(0,0)"};
  cout << ThreePoints(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "right"
  string D[] = {"(0,0)", "(0,5)", "(0,2)"};
  cout << ThreePoints(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "neither"
  string E[] = {"(0,0)", "(0,5)", "(-2,2)"};
  cout << ThreePoints(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: "left"
  string F[] = {"(0,0)", "(0,100)", "(-200,5)"};
  cout << ThreePoints(F, sizeof(F)/sizeof(*F)) << '\n'; // expected output: "left"
  string G[] = {"(-3,0)", "(0,1)", "(-1,0)"} ;
  cout << ThreePoints(G, sizeof(G)/sizeof(*G)) << '\n'; // expected output: "right"
  string H[] = {"(0,1)", "(-3,0)", "(-1,0)"};
  cout << ThreePoints(H, sizeof(H)/sizeof(*H)) << '\n'; // expected output: "left"
  string I[] = {"(0,5)", "(0,-5)", "(1,1)"};
  cout << ThreePoints(I, sizeof(I)/sizeof(*I)) << '\n'; // expected output: "left"

  return 0;

}
