/*
Coderbyte coding challenge: Matrix Determinant

Using the C++ language, have the function MatrixDeterminant(strArr) read strArr
which will be an array of integers represented as strings. Within the array
there will also be "<>" elements which represent break points. The array will
make up a matrix where the (number of break points + 1) represents the number of
rows. Here is an example of how strArr may look: ["1","2","<>","3","4"]. The
contents of this array are row1=[1 2] and row2=[3 4]. Your program should take
the given array of elements, create the proper matrix, and then calculate the
determinant. For the example above, your program should return -2. If the matrix
is not a square matrix, return -1. The maximum size of strArr will be a 6x6
matrix. The determinant will always be an integer.

Sample test cases:

Input:  "5","0","<>","0","5"
Output: 25

Input:  "1","2","4","<>","2","1","1","<>","4","1","1"
Output: -4
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
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

    if (string::npos != max_count && parts.size() == max_count)
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
class matrix {
 public:
  explicit matrix(const int row_count = 0,
                  const int col_count = 0,
                  const char* matrix_elements_sep_tag = "",
                  const char* matrix_rows_sep_tag = "")
      : sep_matrix_column_elements_{matrix_elements_sep_tag},
        sep_matrix_rows_{matrix_rows_sep_tag} {
    if (row_count <= 0 || col_count <= 0)
      throw invalid_argument{"row_count and col_count must be >= 1!"};

    matrix_.assign(row_count, vector<T>(col_count));
  }

  explicit matrix(string* str_arr,
                  const size_t str_arr_size,
                  const char* matrix_elements_sep_tag = "",
                  const char* matrix_rows_sep_tag = "")
      : sep_matrix_column_elements_{matrix_elements_sep_tag},
        sep_matrix_rows_{matrix_rows_sep_tag} {
    vector<T> row{};

    size_t prev_col_width{};

    for (size_t i{}; i < str_arr_size; i++) {
      str_arr[i] = trim(str_arr[i]);

      istringstream iss{str_arr[i]};

      if (str_arr[i] != "<>") {
        T value{};
        iss >> value;

        if (!iss.good() && !iss.eof()) {
          ostringstream oss{};
          oss << "Input string data cannot be converted to " << typeid(T).name()
              << '!';
          throw invalid_argument{oss.str()};
        }
        row.emplace_back(value);
      } else {
        if (!prev_col_width)
          prev_col_width = row.size();
        else if (row.size() != prev_col_width)
          throw runtime_error{"Matrix rows must have equal column widths!"};
        matrix_.emplace_back(row);
        row.clear();
      }
    }

    if (prev_col_width && row.size() != prev_col_width)
      throw runtime_error{"Matrix rows must have equal column widths!"};

    if (!row.empty())
      matrix_.emplace_back(row);
  }

  inline size_t get_row_count() const noexcept { return matrix_.size(); }

  inline size_t get_col_count() const noexcept {
    if (!matrix_.size())
      return 0;

    return matrix_[0].size();
  }

  matrix transpose() const {
    const size_t rc{get_row_count()};
    const size_t cc{get_col_count()};

    matrix transposed_matrix(cc, rc);

    for (size_t i{}; i < rc; i++) {
      for (size_t j{}; j < cc; j++)
        transposed_matrix(j, i) = *this(i, j);
    }

    return transposed_matrix;
  }

  T get_determinant() const {
    const T determinant{calculate_determinant(matrix_)};
    return determinant;
  }

  static T calculate_determinant(const vector<vector<T>>& matrix) {
    const size_t N{matrix.size()};

    if (1 == N)
      return matrix[0][0];

    if (2 == N)
      return (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]);

    T determinant{};

    int sign_factor{1};

    for (size_t p{}; p < N; p++) {
      vector<vector<T>> sm(N - 1, vector<T>(N - 1));

      for (size_t i{1}; i < N; i++) {
        size_t j2{};
        for (size_t j{}; j < N; j++) {
          if (j == p)
            continue;
          sm[i - 1][j2] = matrix[i][j];
          j2++;
        }
      }

      determinant += sign_factor * matrix[0][p] * calculate_determinant(sm);
      sign_factor = -sign_factor;
    }

    return determinant;
  }

  vector<vector<T>>& get_matrix_contents() { return matrix_; };

  const vector<vector<T>>& get_matrix_contents() const { return matrix_; };

  bool operator==(const matrix& m) const {
    const size_t rc{get_row_count()};
    const size_t cc{get_col_count()};

    if (m.get_row_count() != rc)
      return false;
    if (m.get_col_count() != cc)
      return false;

    for (size_t i{}; i < rc; i++) {
      for (size_t j{}; j < cc; j++) {
        if (m(i, j) != *this(i, j))
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
    ostringstream ostr{};

    for (size_t x{}; x < matrix_.size() - 1; x++) {
      for (size_t y{}; y < matrix_[x].size() - 1; y++)
        ostr << matrix_[x][y] << sep_matrix_column_elements_;
      ostr << matrix_[x].back();
      ostr << sep_matrix_rows_;
    }

    for (size_t y{}; y < matrix_.back().size() - 1; y++)
      ostr << matrix_.back()[y] << sep_matrix_column_elements_;
    ostr << matrix_.back().back();

    return ostr.str();
  }

  string to_string() const {
    ostringstream ostr{};

    for (size_t x{}; x < matrix_.size() - 1; x++) {
      for (size_t y{}; y < matrix_[x].size() - 1; y++)
        ostr << matrix_[x][y] << sep_matrix_column_elements_;
      ostr << matrix_[x].back();
      ostr << sep_matrix_rows_;
    }

    for (size_t y{}; y < matrix_.back().size() - 1; y++)
      ostr << matrix_.back()[y] << sep_matrix_column_elements_;
    ostr << matrix_.back().back();

    return ostr.str();
  }

 private:
  const char* sep_matrix_column_elements_;
  const char* sep_matrix_rows_;
  vector<vector<T>> matrix_;
};

template <typename U>
ostream& operator<<(ostream& ostr, const matrix<U>& m) {
  const auto& matrix_contents = m.get_matrix_contents();

  for (size_t x{}; x < matrix_contents.size() - 1; x++) {
    for (size_t y{}; y < matrix_contents[x].size() - 1; y++)
      ostr << matrix_contents[x][y] << sep_matrix_column_elements_;
    ostr << matrix_contents[x].back();
    ostr << sep_matrix_rows_;
  }

  for (size_t y{}; y < matrix_contents.back().size() - 1; y++)
    ostr << matrix_contents.back()[y] << sep_matrix_column_elements_;
  ostr << matrix_contents.back().back();

  return ostr;
}

template <typename U>
istream& operator>>(istream& istr, matrix<U>& m) {
  auto& matrix = m.get_matrix_contents();

  matrix.clear();

  vector<U> row{};
  string line{};
  size_t prev_col_width{};

  while (getline(istr, line)) {
    line = trim(line);
    istringstream iss{line};

    if (line != "<>") {
      U value{};
      iss >> value;
      if (!iss.good() && !iss.eof()) {
        ostringstream oss{};
        oss << "Input string data cannot be converted to " << typeid(T).name()
            << '!';
        throw invalid_argument{oss.str()};
      }
      row.emplace_back(value);
    } else {
      if (!prev_col_width)
        prev_col_width = row.size();
      else if (row.size() != prev_col_width)
        throw runtime_error{
            "The rows of matrix must have equal column widths!"};
      matrix.emplace_back(row);
      row.clear();
    }

    if (prev_col_width && (row.size() != prev_col_width))
      throw runtime_error{"The rows of matrix must have equal column widths!"};

    if (!row.empty())
      matrix.emplace_back(row);
  }

  return istr;
}

string MatrixDeterminant(string* str_arr, const size_t str_arr_size) {
  try {
    matrix<int> m(str_arr, str_arr_size);

    if (m.get_row_count() != m.get_col_count())
      return "-1";

    return to_string(m.get_determinant());
  } catch (exception&) {
    return "-1";
  }
}

int main() {
  // string A[] = gets(stdin);
  // cout << MatrixDeterminant(A, sizeof(A) / sizeof(*A));
  string B[] = {"1", "2", "<>", "3", "4"};
  cout << MatrixDeterminant(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: -2
  string C[] = {"5", "0", "<>", "0", "5"};
  cout << MatrixDeterminant(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 25
  string D[] = {"1", "2", "4", "<>", "2", "1", "1", "<>", "4", "1", "1"};
  cout << MatrixDeterminant(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: -4
  string E[] = {"1", "2",  "3", "4",  "5", "<>", "2", "2",  "4", "5",
                "6", "<>", "3", "4",  "4", "5",  "6", "<>", "4", "5",
                "5", "0",  "1", "<>", "5", "6",  "6", "1",  "1"};
  cout << MatrixDeterminant(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 43
  string F[] = {"1000", "2",  "3", "4",  "5", "<>", "2", "2",  "4",   "5",
                "6",    "<>", "3", "4",  "4", "5",  "6", "<>", "4",   "5",
                "5",    "0",  "1", "<>", "5", "6",  "6", "1",  "1000"};
  cout << MatrixDeterminant(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 49801192

  return 0;
}
