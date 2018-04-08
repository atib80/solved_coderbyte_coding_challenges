/*
Coderbyte coding challenge: Symmetric Matrix

Using the C++ language, have the function SymmetricMatrix(strArr) read strArr
which will be an array of integers represented as strings. Within the array
there will also be "<>" elements which represent break points. The array will
make up a matrix where the (number of break points + 1) represents the number of
rows. Here is an example of how strArr may look:
["1","0","1","<>","0","1","0","<>","1","0","1"]. There are two "<>", so 2 + 1
= 3. Therefore there will be three rows in the array and the contents will be
row1=[1 0 1], row2=[0 1 0] and row3=[1 0 1]. Your program should take the given
array of elements, create the proper matrix, and then determine whether the
matrix is symmetric, in other words, if matrix M is equal to M transpose. If it
is, return the string symmetric and if it isn't return the string not symmetric.
A matrix may or may not be a square matrix and if this is the case you should
return the string not possible. For the example above, your program should
return symmetric.

Sample test cases:

Input:  "5","0","<>","0","5"
Output: "symmetric"

Input:  "1","2","4","<>","2","1","1","<>","-4","1","-1"
Output: "not symmetric"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
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

template <typename T>
class symmetric_matrix {
 public:
  explicit symmetric_matrix(const size_t row_count = 0,
                            const size_t col_count = 0) {
    if (!row_count || !col_count)
      throw invalid_argument{
          "Constructing a symmetrix_matrix object requires row_count and/or "
          "col_count to be >= 1!"};

    matrix_.resize(row_count);

    for (auto& row : matrix_)
      row.resize(col_count);
  }

  explicit symmetric_matrix(string* str_arr, const size_t str_arr_size) {
    vector<T> row{};

    size_t prev_col_width{};

    for (size_t i{}; i < str_arr_size; i++) {
      str_arr[i] = trim(str_arr[i]);

      if (str_arr[i] != "<>") {
        row.emplace_back(stoi(str_arr[i]));
      } else {
        if (!prev_col_width)
          prev_col_width = row.size();
        else if (row.size() != prev_col_width)
          throw runtime_error{"Matrix rows must have equal column widths!"};
        matrix_.emplace_back(row);
        row.clear();
      }
    }

    if (prev_col_width && (row.size() != prev_col_width))
      throw runtime_error{"Matrix rows must have equal column widths!"};

    if (!row.empty())
      matrix_.emplace_back(row);
  }

  size_t get_row_count() const noexcept { return matrix_.size(); }

  size_t get_col_count() const noexcept {
    if (!matrix_.size())
      return 0;

    return matrix_[0].size();
  }

  symmetric_matrix transpose() const {
    const size_t rc{get_row_count()};
    const size_t cc{get_col_count()};

    symmetric_matrix transposed_matrix(cc, rc);

    for (size_t i{}; i < rc; i++) {
      for (size_t j{}; j < cc; j++)
        transposed_matrix(j, i) = operator()(i, j);
    }

    return transposed_matrix;
  }

  bool operator==(const symmetric_matrix& m) const {
    const size_t rc{get_row_count()};
    const size_t cc{get_col_count()};

    if (!m.get_row_count())
      return false;
    if (m.get_row_count() != rc)
      return false;
    if (m.get_col_count() != cc)
      return false;

    for (size_t i{}; i < rc; i++) {
      for (size_t j{}; j < cc; j++) {
        if (m(i, j) != operator()(i, j))
          return false;
      }
    }

    return true;
  }

  T operator()(const size_t i, const size_t j) const {
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

  T& operator()(const size_t i, const size_t j) {
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

  explicit operator string() const {
    ostringstream ss{};

    for (const auto& row : matrix_) {
      for (const auto& element : row)
        ss << element;
    }

    return ss.str();
  }

  string to_string() const {
    ostringstream ss{};

    for (const auto& row : matrix_) {
      for (const auto& element : row)
        ss << element;
    }

    return ss.str();
  }

  friend istream& operator>>(istream&, symmetric_matrix&);
  friend ostream& operator<<(ostream&, const symmetric_matrix&);

 private:
  vector<vector<T>> matrix_;
};

template <typename T>
ostream& operator<<(ostream& ostr, const symmetric_matrix<T>& m) {
  for (const auto& row : m.matrix_) {
    for (const auto& element : row)
      ostr << element;
  }

  return ostr;
}

template <typename T>
istream& operator>>(istream& istr, symmetric_matrix<T>& m) {
  m.matrix_.clear();

  vector<T> row{};
  string line{};
  size_t prev_col_width{};

  while (getline(istr, line)) {
    line = trim(line);

    if (line != "<>") {
      row.emplace_back(stoi(line));
    } else {
      if (!prev_col_width)
        prev_col_width = row.size();
      else if (row.size() != prev_col_width)
        throw runtime_error{
            "The rows of matrix must have equal column widths!"};
      m.matrix_.emplace_back(row);
      row.clear();
    }

    if (prev_col_width && (row.size() != prev_col_width))
      throw runtime_error{"The rows of matrix must have equal column widths!"};

    if (!row.empty())
      m.matrix_.emplace_back(row);
  }

  return istr;
}

string SymmetricMatrix(string* str_arr, const size_t str_arr_size) {
  try {
    const symmetric_matrix<int> matrix(str_arr, str_arr_size);

    if (matrix.get_row_count() != matrix.get_col_count())
      return "not possible";

    const symmetric_matrix<int> transposed_matrix{matrix.transpose()};

    if (matrix == transposed_matrix)
      return "symmetric";
  } catch (const runtime_error&) {
    return "not possible";
  }

  return "not symmetric";
}

int main() {
  // string A[] = gets(stdin);
  // cout << SymmetricMatrix(A, sizeof(A)/sizeof(*A));
  string B[] = {"1", "0", "1", "<>", "0", "1", "0", "<>", "1", "0", "1"};
  cout << SymmetricMatrix(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "symmetric"
  string C[] = {"5", "0", "<>", "0", "5"};
  cout << SymmetricMatrix(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "symmetric"
  string D[] = {"1", "2", "4", "<>", "2", "1", "1", "<>", "-4", "1", "-1"};
  cout << SymmetricMatrix(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "not symmetric"
  string E[] = {"1",  "2", "4", "<>", "2",  "1",  "1",
                "<>", "1", "1", "1",  "<>", "100"};
  cout << SymmetricMatrix(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "not possible"

  return 0;
}
