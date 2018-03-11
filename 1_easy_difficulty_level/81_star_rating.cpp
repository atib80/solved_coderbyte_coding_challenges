/*
Coderbyte coding challenge: Star Rating

Using the C++ language, have the function StarRating(str) take the str parameter
being passed which will be an average rating between 0.00 and 5.00, and convert
this rating into a list of 5 image names to be displayed in a user interface to
represent the rating as a list of stars and half stars. Ratings should be
rounded up to the nearest half. There are 3 image file names available:
"full.jpg", "half.jpg", "empty.jpg". The output will be the name of the 5 images
(without the extension), from left to right, separated by spaces. For example:
if str is "2.36" then your program should return the string "full full half
empty empty".

Sample test cases:

Input:  "0.38"
Output: "half empty empty empty empty"

Input:  "4.5"
Output: "full full full full half"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

string StarRating_v1(string str) {
  str = trim(str);

  const float rating{stof(str)};

  int whole_part{static_cast<int>(rating)};
  int decimal_part{static_cast<int>(round((rating - whole_part) * 100))};

  bool is_half_star_rating{((decimal_part >= 25) && (decimal_part < 75))};

  if (decimal_part >= 75)
    whole_part++;

  ostringstream oss{};

  for (size_t i{}; i < 5; i++) {
    if (whole_part) {
      whole_part--;
      oss << "full";
    }

    else if (is_half_star_rating) {
      is_half_star_rating = false;
      oss << "half";
    }

    else
      oss << "empty";

    if (i < 4)
      oss << ' ';
  }

  return oss.str();
}

string StarRating_v2(string str) {
  str = trim(str);

  int rating_times_100{static_cast<int>(round(stof(str) * 100.f))};

  ostringstream oss{};

  for (size_t i{}; i < 5; i++) {
    if (rating_times_100 >= 75) {
      rating_times_100 -= 100;
      oss << "full";
    }

    else if (rating_times_100 >= 25 && rating_times_100 < 75) {
      rating_times_100 -= 75;
      oss << "half";
    }

    else
      oss << "empty";

    if (i < 4)
      oss << ' ';
  }

  return oss.str();
}

int main() {
  // cout << StarRating_v2(move(string{gets(stdin)}));
  cout << StarRating_v2(move(string{"2.36"}))
       << '\n';  // expected output: "full full half empty empty"
  cout << StarRating_v2(move(string{"0.38"}))
       << '\n';  // expected output: "half empty empty empty empty"
  cout << StarRating_v2(move(string{"4.5"}))
       << '\n';  // expected output: "full full full full half"
  cout << StarRating_v2(move(string{"0.0"}))
       << '\n';  // expected output: "empty empty empty empty empty"
  cout << StarRating_v2(move(string{"3.02"}))
       << '\n';  // expected output: "full full full empty empty"
  cout << StarRating_v2(move(string{"2.75"}))
       << '\n';  // expected output: "full full full empty empty"
  return 0;
}
