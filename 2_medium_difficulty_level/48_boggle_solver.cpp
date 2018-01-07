/*
Coderbyte coding challenge: Boggle Solver

Using the C++ language, have the function BoggleSolver(strArr) read the array of strings stored in strArr, which will contain 2 elements: 
the first element will represent a 4x4 matrix of letters, and the second element will be a long string of comma-separated words each at least 3 letters long, 
in alphabetical order, that represents a dictionary of some arbitrary length. 
For example: strArr can be: ["rbfg, ukop, fgub, mnry", "bog,bop,gup,fur,ruk"]. 
Your goal is to determine if all the comma separated words as the second parameter exist in the 4x4 matrix of letters. 
For this example, the matrix looks like the following:

r b f g
u k o p
f g u b
m n r y

The rules to make a word are as follows:

1. A word can be constructed from sequentially adjacent spots in the matrix, where adjacent means moving horizontally, vertically, or diagonally in any direction.
2. A word cannot use the same location twice to construct itself.

The rules are similar to the game of Boggle. So for the example above, all the words exist in that matrix so your program should return the string true. 
If all the words cannot be found, then return a comma separated string of the words that cannot be found, in the order they appear in the dictionary.

Sample test cases:

Input:  "aaey, rrum, tgmn, ball", "all,ball,mur,raeymnl,tall,true,trum"
Output: "true"

Input:  "aaey, rrum, tgmn, ball", "all,ball,mur,raeymnl,rumk,tall,true,trum,yes"
Output: "rumk,yes"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <string>
#include <vector>
#include <set>

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

bool find_word_in_matrix_at_specified_position(const vector<vector<char>>& m, const size_t i, const size_t j, const string& word, 
  set<pair<size_t, size_t>>& visited_coordinates, const size_t offset = 0u) {

  visited_coordinates.insert(make_pair(i, j));

  if (offset == (word.length() - 1)) return true; 
  
  // N direction
  if ((i > 0) && (offset < (word.length() - 1)) && (visited_coordinates.find(make_pair(i - 1, j)) == end(visited_coordinates)) 
      && (word[offset + 1] == m[i - 1][j]) && find_word_in_matrix_at_specified_position(m, i - 1, j, word, visited_coordinates, offset + 1)) return true;
  // NE direction
  if ((i > 0) && (j < 3) && (offset < (word.length() - 1)) && (visited_coordinates.find(make_pair(i - 1, j + 1)) == end(visited_coordinates)) 
      && (word[offset + 1] == m[i - 1][j + 1]) && find_word_in_matrix_at_specified_position(m, i - 1, j + 1, word, visited_coordinates, offset + 1)) return true;
  // E direction
  if ((j < 3) && (offset < (word.length() - 1)) && (visited_coordinates.find(make_pair(i, j + 1)) == end(visited_coordinates)) 
      && (word[offset + 1] == m[i][j + 1]) && find_word_in_matrix_at_specified_position(m, i, j + 1, word, visited_coordinates, offset + 1)) return true;
  // SE direction
  if ((i < 3) && (j < 3) && (offset < (word.length() - 1)) && (visited_coordinates.find(make_pair(i + 1, j + 1)) == end(visited_coordinates)) 
      && (word[offset + 1] == m[i + 1][j + 1]) && find_word_in_matrix_at_specified_position(m, i + 1, j + 1, word, visited_coordinates, offset + 1)) return true;
  // S direction
  if ((i < 3) && (offset < (word.length() - 1)) && (visited_coordinates.find(make_pair(i + 1, j)) == end(visited_coordinates)) 
      && (word[offset + 1] == m[i + 1][j]) && find_word_in_matrix_at_specified_position(m, i + 1, j, word, visited_coordinates, offset + 1)) return true;
  // SW direction
  if ((i < 3) && (j > 0) && (offset < (word.length() - 1)) && (visited_coordinates.find(make_pair(i + 1, j - 1)) == end(visited_coordinates))
      && (word[offset + 1] == m[i + 1][j - 1]) && find_word_in_matrix_at_specified_position(m, i + 1, j - 1, word, visited_coordinates, offset + 1)) return true;  
  // W direction
  if ((j > 0) && (offset < (word.length() - 1)) && (visited_coordinates.find(make_pair(i, j - 1)) == end(visited_coordinates)) 
      && (word[offset + 1] == m[i][j - 1]) && find_word_in_matrix_at_specified_position(m, i, j - 1, word, visited_coordinates, offset + 1)) return true;
  // NW direction
    if ((i > 0) && (j > 0) && (offset < (word.length() - 1)) && (visited_coordinates.find(make_pair(i - 1, j - 1)) == end(visited_coordinates)) 
      && (word[offset + 1] == m[i - 1][j - 1]) && find_word_in_matrix_at_specified_position(m, i - 1, j - 1, word, visited_coordinates, offset + 1)) return true;

  return false;
  
}

bool find_word_in_matrix(const vector<vector<char>>& matrix, const string& word) {

  for (size_t i{}; i != 4; i++) {

    for (size_t j{}; j != 4; j++) {

      if (matrix[i][j] == word.front()) {        

        set<pair<size_t, size_t>> visited_coordinates{};

        if (find_word_in_matrix_at_specified_position(matrix, i, j, word, visited_coordinates)) return true;

        }
    }
  
  }

  return false;
}

string BoggleSolver(string* str_arr, const size_t str_arr_size) { 

  if (!str_arr || str_arr_size != 2u) return string{"Not possible!"};

  str_arr[0] = trim(str_arr[0]);
  str_arr[1] = trim(str_arr[1]);

  vector<string> matrix_rows = split(str_arr[0], ", ");

  for (string& row : matrix_rows) row = trim(row);

  if (4u != matrix_rows.size()) return string{"Not possible!"};

  vector<string> dict_words = split(str_arr[1], ",");

  for (string& word : dict_words) word = trim(word);

  vector<vector<char>> matrix(4, vector<char>{});  

  for (size_t i{}; i != 4; i++) {

    matrix[i].resize(4);

    for (size_t j{}; j != 4; j++) matrix[i][j] = matrix_rows[i][j];

  }

  ostringstream oss{};

  bool is_found_missing_word{};

  for (const string& word : dict_words) {

    if (!find_word_in_matrix(matrix, word)) {

      is_found_missing_word = true;

      oss << word << ',';
    }

  }

  if (is_found_missing_word) {

      string result{oss.str()};     
    
      result.erase(--end(result));

      return result;
  }  

  return string{"true"};
  
}

int main() { 
   
  // string A[] = gets(stdin);
  // cout << BoggleSolver(A, sizeof(A)/sizeof(*A));
  string B[] = {"rbfg, ukop, fgub, mnry", "bog,bop,gup,fur,ruk"};
  cout << BoggleSolver(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "true"
  string C[] = {"aaey, rrum, tgmn, ball", "all,ball,mur,raeymnl,tall,true,trum"};
  cout << BoggleSolver(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "true"
  string D[] = {"aaey, rrum, tgmn, ball", "all,ball,mur,raeymnl,rumk,tall,true,trum,yes"};
  cout << BoggleSolver(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "rumk,yes"
  return 0;
} 
