/*
Coderbyte coding challenge: Star Rating

Using the C++ language, have the function StarRating(str) take the str parameter being passed which will be an average rating between 0.00 and 5.00, 
and convert this rating into a list of 5 image names to be displayed in a user interface to represent the rating as a list of stars and half stars. 
Ratings should be rounded up to the nearest half. There are 3 image file names available: "full.jpg", "half.jpg", "empty.jpg". 
The output will be the name of the 5 images (without the extension), from left to right, separated by spaces. 
For example: if str is "2.36" then your program should return the string "full full half empty empty".

Sample test cases:

Input:  "0.38"
Output: "half empty empty empty empty"

Input:  "4.5"
Output: "full full full full half"
*/

#include <iostream>
#include <cctype>
#include <string>
#include <cmath>

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

string StarRating(string str) { 

  str = trim(str);

  const float rating { stof(str) };

  int whole_part { static_cast<int>(floor(rating)) };

  bool is_half_star_rating { ( ( (rating - whole_part) >= 0.25f) && ( (rating - whole_part) < 0.75f) ) };

  if (rating - whole_part >= 0.75f) whole_part++;

  string result{};

  for (size_t i{}; i != 5u; i++) {

  	if (whole_part) {
  		whole_part--;
  		result += "full ";
  	}

  	else if (is_half_star_rating) {
  		is_half_star_rating = false;
  		result += "half ";
  	}

  	else result += "empty ";

  }

  result.erase(--(end(result)));
  
  return result;            

}

int main() { 
  
  // cout << StarRating(move(string{gets(stdin)}));
  cout << StarRating(move(string{"2.36"})) << '\n'; // expected output: "full full half empty empty"
  cout << StarRating(move(string{"0.38"})) << '\n'; // expected output: "half empty empty empty empty"
  cout << StarRating(move(string{"4.5"})) << '\n';  // expected output: "full full full full half"
  cout << StarRating(move(string{"0.0"})) << '\n';  // expected output: "empty empty empty empty empty"
  cout << StarRating(move(string{"3.02"})) << '\n'; // expected output: "full full full empty empty"
  cout << StarRating(move(string{"2.75"})) << '\n'; // expected output: "full full full empty empty"  
  return 0;

} 
