/*
Coderbyte coding challenge: Boggle Solver v1
(recursive solution using unordered_set<T>)

Using the C++ language, have the function BoggleSolver(strArr) read the array of
strings stored in strArr, which will contain 2 elements: the first element will
represent a 4x4 matrix of letters, and the second element will be a long string
of comma-separated words each at least 3 letters long, in alphabetical order,
that represents a dictionary of some arbitrary length. For example: strArr can
be: ["rbfg, ukop, fgub, mnry", "bog,bop,gup,fur,ruk"]. Your goal is to determine
if all the comma separated words as the second parameter exist in the 4x4 matrix
of letters. For this example, the matrix looks like the following:

r b f g
u k o p
f g u b
m n r y

The rules to make a word are as follows:

1. A word can be constructed from sequentially adjacent spots in the matrix,
where adjacent means moving horizontally, vertically, or diagonally in any
direction.
2. A word cannot use the same location twice to construct itself.

The rules are similar to the game of Boggle. So for the example above, all the
words exist in that matrix so your program should return the string true. If all
the words cannot be found, then return a comma separated string of the words
that cannot be found, in the order they appear in the dictionary.

Sample test cases:

Input:  "aaey, rrum, tgmn, ball", "all,ball,mur,raeymnl,tall,true,trum"
Output: "true"

Input:  "aaey, rrum, tgmn, ball", "all,ball,mur,raeymnl,rumk,tall,true,trum,yes"
Output: "rumk,yes"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

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

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.length()};

  if (!source_len)
    return parts;

  if (!needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if ((string::npos != max_count) && (parts.size() == max_count))
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

bool search_word_in_matrix_at_specified_position(
    const vector<vector<char>>& m,
    const size_t i,
    const size_t j,
    const string& word,
    unordered_set<size_t>& visited_coordinates,
    const size_t offset = 0) {
  visited_coordinates.insert(i * m[i].size() + j);

  if (offset == word.length() - 1)
    return true;

  // N direction
  if (i > 0 && offset < word.length() - 1 &&
      !visited_coordinates.count((i - 1) * m[i - 1].size() + j) &&
      word[offset + 1] == m[i - 1][j] &&
      search_word_in_matrix_at_specified_position(
          m, i - 1, j, word, visited_coordinates, offset + 1))
    return true;

  // NE direction
  if (i > 0 && j < m[i - 1].size() - 1 && offset < word.length() - 1 &&
      !visited_coordinates.count((i - 1) * m[i - 1].size() + j + 1) &&
      word[offset + 1] == m[i - 1][j + 1] &&
      search_word_in_matrix_at_specified_position(
          m, i - 1, j + 1, word, visited_coordinates, offset + 1))
    return true;

  // E direction
  if (j < m[i].size() - 1 && offset < word.length() - 1 &&
      !visited_coordinates.count(i * m[i].size() + j + 1) &&
      word[offset + 1] == m[i][j + 1] &&
      search_word_in_matrix_at_specified_position(
          m, i, j + 1, word, visited_coordinates, offset + 1))
    return true;

  // SE direction
  if (i < m.size() - 1 && j < m[i + 1].size() - 1 &&
      offset < word.length() - 1 &&
      !visited_coordinates.count((i + 1) * m[i + 1].size() + j + 1) &&
      word[offset + 1] == m[i + 1][j + 1] &&
      search_word_in_matrix_at_specified_position(
          m, i + 1, j + 1, word, visited_coordinates, offset + 1))
    return true;

  // S direction
  if (i < m.size() - 1 && offset < word.length() - 1 &&
      !visited_coordinates.count((i + 1) * m[i - 1].size() + j) &&
      word[offset + 1] == m[i + 1][j] &&
      search_word_in_matrix_at_specified_position(
          m, i + 1, j, word, visited_coordinates, offset + 1))
    return true;

  // SW direction
  if (i < m.size() - 1 && j > 0 && offset < word.length() - 1 &&
      !visited_coordinates.count((i + 1) * m[i - 1].size() + j - 1) &&
      word[offset + 1] == m[i + 1][j - 1] &&
      search_word_in_matrix_at_specified_position(
          m, i + 1, j - 1, word, visited_coordinates, offset + 1))
    return true;

  // W direction
  if (j > 0 && offset < word.length() - 1 &&
      !visited_coordinates.count(i * m[i - 1].size() + j - 1) &&
      word[offset + 1] == m[i][j - 1] &&
      search_word_in_matrix_at_specified_position(
          m, i, j - 1, word, visited_coordinates, offset + 1))
    return true;

  // NW direction
  if (i > 0 && j > 0 && offset < word.length() - 1 &&
      !visited_coordinates.count((i - 1) * m[i - 1].size() + j - 1) &&
      word[offset + 1] == m[i - 1][j - 1] &&
      search_word_in_matrix_at_specified_position(
          m, i - 1, j - 1, word, visited_coordinates, offset + 1))
    return true;

  return false;
}

bool search_word_in_matrix(const vector<vector<char>>& matrix,
                           const string& word) {
  for (size_t i{}; i < matrix.size(); i++) {
    for (size_t j{}; j < matrix[0].size(); j++) {
      if (matrix[i][j] == word.front()) {
        unordered_set<size_t> visited_coordinates{};

        if (search_word_in_matrix_at_specified_position(matrix, i, j, word,
                                                        visited_coordinates))
          return true;
      }
    }
  }

  return false;
}

string BoggleSolver(string* str_arr, const size_t str_arr_size) {
  if (!str_arr || str_arr_size != 2)
    return "not possible";

  str_arr[0] = trim(str_arr[0]);
  str_arr[1] = trim(str_arr[1]);

  vector<string> matrix_rows{split(str_arr[0], ", ")};

  for (string& row : matrix_rows)
    row = trim(row);

  vector<string> dict_words = split(str_arr[1], ",");

  for (string& word : dict_words)
    word = trim(word);

  vector<vector<char>> matrix(matrix_rows.size(), vector<char>{});

  for (size_t i{}; i < matrix.size(); i++) {
    matrix[i].resize(matrix_rows[0].length());

    for (size_t j{}; j < matrix_rows[i].length(); j++)
      matrix[i][j] = matrix_rows[i][j];
  }

  ostringstream oss{};

  bool is_found_missing_word{};

  for (size_t i{}; i < dict_words.size(); i++) {
    if (!search_word_in_matrix(matrix, dict_words[i])) {
      is_found_missing_word = true;
      if (i < dict_words.size() - 1)
        oss << dict_words[i] << ',';
      else
        oss << dict_words[i];
    }
  }

  if (is_found_missing_word)
    return oss.str();

  return "true";
}

int main() {
  // string A[] = gets(stdin);
  // cout << BoggleSolver(A, sizeof(A)/sizeof(*A));
  string B[] = {"rbfg, ukop, fgub, mnry", "bog,bop,gup,fur,ruk"};
  cout << BoggleSolver(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "true"
  string C[] = {"aaey, rrum, tgmn, ball",
                "all,ball,mur,raeymnl,tall,true,trum"};
  cout << BoggleSolver(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "true"
  string D[] = {"aaey, rrum, tgmn, ball",
                "all,ball,mur,raeymnl,rumk,tall,true,trum,yes"};
  cout << BoggleSolver(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "rumk,yes"
  return 0;
}
