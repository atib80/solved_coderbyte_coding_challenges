/*
Coderbyte coding challenge: RREF Matrix

Using the C++ language, have the function RREFMatrix(strArr) take strArr which
will be an array of integers represented as strings. Within the array there will
also be "<>" elements which represent break points. The array will make up a
matrix where the (number of break points + 1) represents the number of rows.
Here is an example of how strArr may look: ["5","7","8","<>","1","1","2"]. There
is one "<>", so 1 + 1 = 2. Therefore there will be two rows in the array and the
contents will be row1=[5 7 8] and row2=[1 1 2]. Your program should take the
given array of elements, create the proper matrix, and then through the process
of Gaussian elimination create a reduced row echelon form matrix (RREF matrix).
For the array above, the resulting RREF matrix would be: row1=[1 0 3], row2=[0 1
-1]. Your program should return that resulting RREF matrix in string form
combining all the integers, like so: "10301-1". The matrix can have any number
of rows and columns (max=6x6 matrix and min=1x1 matrix). The matrix will not
necessarily be a square matrix. If the matrix is an nx1 matrix it will not
contain the "<>" element. The integers in the array will be such that the
resulting RREF matrix will not contain any fractional numbers.

Sample test  cases:

Input:  "2","4","8","<>","6","12","14"
Output: "120001"

Input:  "2","2","4","<>","1","1","8","<>","7","6","5"
Output: "100010001"
*/

// clang-format cb_rref_matrix_ex2.cpp -style=Google -i
// clang cb_rref_matrix_ex2.cpp -Wall -Wextra -pedantic -std=c++17 -O3 -Ofast -o test

#include <cctype>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len) return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first])) break;
  }

  if (first > last) return string{};

  for (; last > first; --last) {
    if (!isspace(str[last])) break;
  }

  return str.substr(first, last - first + 1);
}

class rref_matrix {
 public:
  explicit rref_matrix(string* str_arr, const size_t str_arr_size) {
    vector<int> row{};

    for (size_t i{}; i < str_arr_size; i++) {
      str_arr[i] = trim(str_arr[i]);

      if (str_arr[i] != "<>") {
        row.emplace_back(stoi(str_arr[i]));

      } else {
        matrix_.emplace_back(row);
        row.clear();
      }
    }

    matrix_.emplace_back(row);
  }

  vector<int> multiply_vector(const size_t row_index, const int factor) const {
    auto row = this->operator[](row_index);

    for (auto& element : row) element *= factor;

    return row;
  }

  void divide_vector_in_place(const size_t row_index, const int factor) {
    if (row_index >= matrix_.size()) return;

    for (auto& element : matrix_[row_index]) element /= factor;
  }

  void add_vectors_in_place(const size_t row_index, const vector<int>& src) {
    const size_t src_size{src.size()};

    if (row_index >= matrix_.size()) return;

    if (matrix_[row_index].size() != src_size) return;

    for (size_t i{}; i < src_size; i++) matrix_[row_index][i] += src[i];
  }

  int get_index_of_first_non_zero_element(const size_t row_index) {
    if (row_index >= matrix_.size()) return -1;

    for (size_t i{}; i < matrix_[row_index].size(); i++) {
      if (matrix_[row_index][i]) return i;
    }

    return -1;
  }

  void swap_matrix_rows(const size_t index) {
    if (index >= matrix_[0].size()) return;

    size_t min_index{index};
    int minimum{numeric_limits<int>::max()};

    for (size_t i{index}; i < matrix_.size(); i++) {
      if (matrix_[i][index] && (abs(matrix_[i][index]) < minimum)) {
        minimum = abs(matrix_[i][index]);

        min_index = i;
      }
    }

    const auto matrix_row = matrix_[min_index];
    matrix_[min_index] = matrix_[index];
    matrix_[index] = matrix_row;
  }

  vector<int> operator[](const size_t index) const {
    if (index >= matrix_.size())
      throw range_error("Specified index is out of allowed range!");

    return matrix_[index];
  }

  int operator()(const size_t i, const size_t j) const {
    if (i >= matrix_.size()) {
      ostringstream oss{};
      oss << "Specified row index (i = " << i << ") is out of bounds!";
      throw range_error(oss.str());
    }

    if (j >= matrix_[i].size()) {
      ostringstream oss{};
      oss << "Specified column index (j = " << j << ") is out of bounds!";
      throw range_error(oss.str());
    }

    return matrix_[i][j];
  }

  int get_row_count() const noexcept {
    return static_cast<int>(matrix_.size());
  }

  int get_col_count(const size_t row_index) const noexcept {
    if (row_index >= matrix_.size()) return 0;

    return static_cast<int>(matrix_[row_index].size());
  }

  explicit operator string() const {
    ostringstream ss{};

    for (const auto& row : matrix_) {
      for (const auto& element : row) ss << element;
    }

    return ss.str();
  }

  string to_string() const {
    ostringstream ss{};

    for (const auto& row : matrix_) {
      for (const auto& element : row) ss << element;
    }

    return ss.str();
  }

  friend istream& operator>>(istream&, rref_matrix&);
  friend ostream& operator<<(ostream&, const rref_matrix&);

 private:
  vector<vector<int>> matrix_;
};

ostream& operator<<(ostream& ostr, const rref_matrix& m) {
  for (const auto& row : m.matrix_) {
    for (const auto& element : row) ostr << element;
  }

  return ostr;
}

istream& operator>>(istream& istr, rref_matrix& m) {
  m.matrix_.clear();

  vector<int> row{};

  string line{};

  while (getline(istr, line)) {
    line = trim(line);

    if (line != "<>") {
      row.emplace_back(stoi(line));

    } else {
      m.matrix_.emplace_back(row);
      row.clear();
    }

    m.matrix_.emplace_back(row);
  }

  return istr;
}

string RREFMatrix(string* str_arr, const size_t str_arr_size) {
  rref_matrix matrix{str_arr, str_arr_size};

  for (int i{}; i < matrix.get_row_count(); i++) {
    if (i >= matrix.get_col_count(i)) continue;

    matrix.swap_matrix_rows(i);

    if (!matrix(i, i)) continue;

    matrix.divide_vector_in_place(i, matrix[i][i]);

    for (int j{i + 1}; j < matrix.get_row_count(); j++) {
      const auto row = matrix.multiply_vector(i, -matrix[j][i]);

      matrix.add_vectors_in_place(j, row);
    }
  }

  for (int i{matrix.get_row_count() - 1}; i >= 0; i--) {
    const int index{matrix.get_index_of_first_non_zero_element(i)};

    if (index < 0) continue;

    matrix.divide_vector_in_place(i, matrix[i][index]);

    for (int j{i - 1}; j >= 0; j--) {
      const auto row = matrix.multiply_vector(i, -matrix[j][index]);

      matrix.add_vectors_in_place(j, row);
    }
  }

  // return matrix; // implicitly invokes 'operator string() const'
  // return static_cast<string>(matrix); // explicitly invokes 'explicit operator string() const' on matrix

  return matrix.to_string();

}

int main() {
  // string A[] = gets(stdin);
  // cout << RREFMatrix(A, sizeof(A)/sizeof(*A));
  string B[] = {"5", "7", "8", "<>", "1", "1", "2"};
  cout << RREFMatrix(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "10301-1"
  string C[] = {"2", "4", "8", "<>", "6", "12", "14"};
  cout << RREFMatrix(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "120001"
  string D[] = {"2", "2", "4", "<>", "1", "1", "8", "<>", "7", "6", "5"};
  cout << RREFMatrix(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "100010001"
  string E[] = {"4", "<>", "5", "<>", "3"};
  cout << RREFMatrix(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "100"
  string F[] = {"5", "5", "5", "<>", "6",  "6",  "6",  "<>",
                "2", "1", "3", "<>", "10", "15", "17", "<>",
                "2", "2", "1", "<>", "6",  "7",  "8"};
  cout << RREFMatrix(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "100010001000000000"

  return 0;
}
