/*
Coderbyte coding challenge: Charlie The Dog

Using the C++ language, have the function CharlietheDog(strArr) read the array of strings stored in strArr
which will be a 4x4 matrix of the characters 'C', 'H', 'F', 'O', where C represents Charlie the dog, 
H represents its home, F represents dog food, and O represents and empty space in the grid. 
Your goal is to figure out the least amount of moves required to get Charlie to grab each piece of food in the grid 
by moving up, down, left, or right, and then make it home right after. 
Charlie cannot move onto the home before all pieces of food have been collected. 
For example: if strArr is ["FOOF", "OCOO", "OOOH", "FOOO"], then this looks like the following grid:

|F|O|O|F|
|O|C|O|O|
|O|O|O|H|
|F|O|O|O| 

For the input above, the least amount of steps where the dog can reach each piece of food, and then return home is 11 steps, 
so your program should return the number 11. The grid will always contain between 1 and 8 pieces of food.

Sample test cases:

Input:  "OOOO", "OOFF", "OCHO", "OFOO"
Output: 7

Input:  "FOOO", "OCOH", "OFOF", "OFOO"
Output: 10
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

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

size_t calculate_distance(const pair<size_t, size_t>& x, const pair<size_t, size_t>& y) {

  const size_t x1 { x.first };
  const size_t y1 { x.second };
  const size_t x2 { y.first };
  const size_t y2 { y.second };

  const size_t distance { (x1 > x2 ? x1 - x2 : x2 - x1) + (y1 > y2 ? y1 - y2 : y2 - y1) };

  return distance;
}

size_t CharlietheDog(string* str_arr, const size_t arr_size) { 

  if (!arr_size || !str_arr) return 0;

  const size_t row_size { arr_size };
  
  size_t col_size { string::npos };

  pair<size_t,size_t> dog{string::npos, string::npos}, home{string::npos, string::npos};
  vector<pair<size_t,size_t>> food_positions{};

  for (size_t i{}; i != arr_size; i++) {

    str_arr[i] = trim(str_arr[i]);

    if (string::npos == col_size) col_size = str_arr[i].length();
    else if (str_arr[i].length() != col_size) return 0;

    for (size_t j{}; j < col_size; j++) {        
    
        if ('c' == str_arr[i][j] || 'C' == str_arr[i][j]) {
              
              if ((string::npos != dog.first) && (string::npos != dog.second)) return 0;              
              dog = make_pair(i,j);

        } else if ('h' == str_arr[i][j] || 'H' == str_arr[i][j]) {

              if ((string::npos != home.first) && (string::npos != home.second)) return 0;
              home = make_pair(i,j);

        } else if ('f' == str_arr[i][j] || 'F' == str_arr[i][j]) {

          food_positions.emplace_back(make_pair(i,j));

        }       
    }
  
  }

  size_t min_steps_count{string::npos};
  
  sort(begin(food_positions), end(food_positions), [](const pair<size_t, size_t>& x, const pair<size_t, size_t>& y) {
      
      return ((x.first < y.first) && (x.second < y.second));
      
  });

  while (true) {
      
      pair<size_t, size_t> dog_pos{dog};
      
      size_t steps_count{};
      
      for (const auto& food_position : food_positions) {

          steps_count += calculate_distance(dog_pos, food_position);
          
          dog_pos = food_position;
      }

      steps_count += calculate_distance(dog_pos, home);
      
      if (steps_count < min_steps_count) min_steps_count = steps_count;
      
      if (!next_permutation(begin(food_positions), end(food_positions))) break;
  } 
  
  return min_steps_count;            

}

int main() {   
    
  // string A[] = gets(stdin);
  // cout << CharlietheDog(A, sizeof(A)/sizeof(*A));
  string B[] = {"FOOF", "OCOO", "OOOH", "FOOO"};
  cout << CharlietheDog(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 11
  string C[] = {"OOOO", "OOFF", "OCHO", "OFOO"};
  cout << CharlietheDog(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 7  
  string D[] = {"FOOO", "OCOH", "OFOF", "OFOO"};
  cout << CharlietheDog(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 10

  return 0;
}
