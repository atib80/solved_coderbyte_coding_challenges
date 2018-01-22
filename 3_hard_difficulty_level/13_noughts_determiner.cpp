/*
Coderbyte codingt challenge: Noughts Determiner

Using the C++ language, have the function NoughtsDeterminer(strArr) take the
strArr parameter being passed which will be an array of size eleven. The array
will take the shape of a Tic-tac-toe board with spaces strArr[3] and strArr[7]
being the separators ("<>") between the rows, and the rest of the spaces will be
either "X", "O", or "-" which signifies an empty space. So for example strArr
may be ["X","O","-","<>","-","O","-","<>","O","X","-"]. This is a Tic-tac-toe
board with each row separated by double arrows ("<>"). Your program should
output the space in the array by which any player could win by putting down
either an "X" or "O". In the array above, the output should be 2 because if an
"O" is placed in strArr[2] then one of the players wins. Each board will only
have one solution for a win, not multiple wins. You output should never be 3 or
7 because those are the separator spaces.

Sample test cases:

Input:  "X","O","-","<>","-","O","-","<>","O","X","-"
Output: 2

Input:  "X","-","O","<>","-","-","O","<>","-","-","X"
Output: 5

Input:  "X","O","X","<>","-","O","O","<>","X","X","O"
Output: 4
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str)
{
	const size_t str_len{str.length()};

	if (!str_len)
		return string{};

	size_t first{}, last{str_len - 1};

	for (; first <= last; ++first)
	{
		if (!isspace(str[first]))
			break;
	}

	if (first > last)
		return string{};

	for (; last > first; --last)
	{
		if (!isspace(str[last]))
			break;
	}

	return str.substr(first, last - first + 1);
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos)
{
	vector<string> parts{};

	string needle_st{needle};

	const size_t source_len{source.length()};

	const size_t needle_len{needle_st.size()};

	if ((0u == source_len) || (0u == needle_len))
		return parts;

	size_t number_of_parts{}, prev{};

	while (true)
	{
		const size_t current{source.find(needle_st, prev)};

		if (string::npos == current)
			break;

		number_of_parts++;

		if ((string::npos != max_count) && (parts.size() == max_count))
			break;

		if ((current - prev) > 0)
			parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source_len)
			break;
	}

	if (prev < source_len)
	{
		if (string::npos == max_count)
			parts.emplace_back(source.substr(prev));

		else if ((string::npos != max_count) && (parts.size() < max_count))
			parts.emplace_back(source.substr(prev));
	}

	return parts;
}

enum class tic_tac_toe_player
{
	X,
	O,
	EMPTY,
	XO
};

class tic_tac_toe
{
public:
	explicit tic_tac_toe(const size_t dimension = 3)
	{
		if (!dimension)
			return;

		matrix_.resize(dimension);

		for (auto& row : matrix_)
			row.resize(dimension);
	}

	explicit tic_tac_toe(string* str_arr, const size_t str_arr_size)
	{
		vector<tic_tac_toe_player> row{};

		size_t prev_col_width{};

		for (size_t i{}; i < str_arr_size; i++)
		{
			str_arr[i] = trim(str_arr[i]);

			if ("<>" != str_arr[i])
			{
				if ("X" == str_arr[i])
					row.emplace_back(tic_tac_toe_player::X);
				else if ("O" == str_arr[i])
					row.emplace_back(tic_tac_toe_player::O);
				else if ("-" == str_arr[i])
					row.emplace_back(tic_tac_toe_player::EMPTY);
			}
			else
			{
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

		matrix_.emplace_back(row);

		if (!matrix_.empty() && (matrix_.size() != matrix_[0].size()))
			throw runtime_error{
				"Matrix must have identical number of rows and columns (square "
				"matrix)!"
			};
	}

	size_t get_dimension() const noexcept { return matrix_.size(); }

	static vector<vector<tic_tac_toe_player>> transpose(
		const vector<vector<tic_tac_toe_player>>& matrix)
	{
		if (matrix.empty())
			return vector<vector<tic_tac_toe_player>>{};

		const size_t rc{matrix.size()};
		const size_t cc{matrix[0].size()};

		vector<vector<tic_tac_toe_player>> transposed_matrix(
			cc, vector<tic_tac_toe_player>{});

		for (auto& row : transposed_matrix)
			row.resize(rc);

		for (size_t i{}; i < rc; i++)
		{
			for (size_t j{}; j < cc; j++)

				transposed_matrix[j][i] = matrix[i][j];
		}

		return transposed_matrix;
	}

	static size_t calculate_correct_position_index(
		const vector<vector<tic_tac_toe_player>>& matrix,
		const size_t position_index)
	{
		if (matrix.empty())
			return string::npos;

		const size_t dim{matrix[0].size()};

		size_t position{dim}, offset{};

		while (position <= position_index)
		{
			offset++;
			position += dim;
		}

		return (position_index + offset);
	}

	static bool check_if_player_won_tic_tac_toe_game(
		const vector<vector<tic_tac_toe_player>>& t,
		const tic_tac_toe_player& tp)
	{
		if (t.empty())
			return false;

		for (const auto& row : t)
		{
			if (all_of(begin(row), end(row),
			           [&](const tic_tac_toe_player& p) { return (p == tp); }))
				return true;
		}

		const vector<vector<tic_tac_toe_player>> tt{transpose(t)};

		for (const auto& row : tt)
		{
			if (all_of(begin(row), end(row),
			           [&](const tic_tac_toe_player& p) { return (p == tp); }))
				return true;
		}

		const size_t dim{t.size()};

		if (dim != t[0].size())
			return false;

		bool is_diagonal_match{true};

		for (size_t x1{}, y1{}; x1 < dim; x1++, y1++)
		{
			if (t[x1][y1] != tp)
			{
				is_diagonal_match = false;
				break;
			}
		}

		if (is_diagonal_match)
			return true;

		is_diagonal_match = true;

		for (size_t x2{}, y2{dim - 1}; x2 < dim; x2++, y2--)
		{
			if (t[x2][y2] != tp)
			{
				is_diagonal_match = false;
				break;
			}
		}

		if (is_diagonal_match)
			return true;

		return false;
	}

	size_t find_correct_spot_for_winning(
		const tic_tac_toe_player tp = tic_tac_toe_player::XO) const
	{
		vector<vector<tic_tac_toe_player>> t{matrix_};

		if (tic_tac_toe_player::XO == tp)
		{
			for (size_t x{}; x < t.size(); x++)
			{
				for (size_t y{}; y < t[x].size(); y++)
				{
					if (tic_tac_toe_player::EMPTY == t[x][y])
					{
						t[x][y] = tic_tac_toe_player::X;
						if (check_if_player_won_tic_tac_toe_game(t, tic_tac_toe_player::X))
							return calculate_correct_position_index(t, x * get_dimension() + y);
						t[x][y] = tic_tac_toe_player::O;
						if (check_if_player_won_tic_tac_toe_game(t, tic_tac_toe_player::O))
							return calculate_correct_position_index(t, x * get_dimension() + y);
						t[x][y] = tic_tac_toe_player::EMPTY;
					}
				}
			}
		}
		else if (tic_tac_toe_player::X == tp)
		{
			for (size_t x{}; x < t.size(); x++)
			{
				for (size_t y{}; y < t[x].size(); y++)
				{
					if (tic_tac_toe_player::EMPTY == t[x][y])
					{
						t[x][y] = tic_tac_toe_player::X;
						if (check_if_player_won_tic_tac_toe_game(t, tic_tac_toe_player::X))
							return calculate_correct_position_index(t, x * get_dimension() + y);

						t[x][y] = tic_tac_toe_player::EMPTY;
					}
				}
			}
		}
		else if (tic_tac_toe_player::O == tp)
		{
			for (size_t x{}; x < t.size(); x++)
			{
				for (size_t y{}; y < t[x].size(); y++)
				{
					if (tic_tac_toe_player::EMPTY == t[x][y])
					{
						t[x][y] = tic_tac_toe_player::O;
						if (check_if_player_won_tic_tac_toe_game(t, tic_tac_toe_player::O))
							return calculate_correct_position_index(t, x * get_dimension() + y);
						t[x][y] = tic_tac_toe_player::EMPTY;
					}
				}
			}
		}

		return string::npos;
	}

	vector<vector<tic_tac_toe_player>>& get_matrix_contents() { return matrix_; };

	const vector<vector<tic_tac_toe_player>>& get_matrix_contents() const
	{
		return matrix_;
	};

	bool operator==(const tic_tac_toe& t) const
	{
		const size_t dim{get_dimension()};

		if (!t.get_dimension())
			return false;
		if (t.get_dimension() != dim)
			return false;

		for (size_t x{}; x < dim; x++)
		{
			for (size_t y{}; y < dim; y++)
			{
				if (t(x, y) != operator()(x, y))
					return false;
			}
		}

		return true;
	}

	tic_tac_toe_player operator()(const size_t i, const size_t j) const
	{
		if (i >= matrix_.size())
		{
			ostringstream oss{};
			oss << "Specified row index (i = " << i << ") is out of bounds!";
			throw range_error(oss.str());
		}

		if (j >= matrix_[i].size())
		{
			ostringstream oss{};
			oss << "Specified column index (j = " << j << ") is out of bounds!";
			throw range_error(oss.str());
		}

		return matrix_[i][j];
	}

	tic_tac_toe_player& operator()(const size_t i, const size_t j)
	{
		if (i >= matrix_.size())
		{
			ostringstream oss{};
			oss << "Specified row index (i = " << i << ") is out of bounds!";
			throw range_error(oss.str());
		}

		if (j >= matrix_[i].size())
		{
			ostringstream oss{};
			oss << "Specified column index (j = " << j << ") is out of bounds!";
			throw range_error(oss.str());
		}

		return matrix_[i][j];
	}

	string to_string() const
	{
		ostringstream ss{};

		ss << "\n__________\n";

		for (const auto& row : matrix_)
		{
			for (const auto& element : row)
			{
				if (tic_tac_toe_player::X == element)
					ss << "|X";
				else if (tic_tac_toe_player::O == element)
					ss << "|O";
			}

			ss << "|\n__________";
		}

		return ss.str();
	}

private:
	vector<vector<tic_tac_toe_player>> matrix_;
};

ostream& operator<<(ostream& ostr, const tic_tac_toe& m)
{
	const auto& matrix_contents = m.get_matrix_contents();

	ostr << "\n__________\n";

	for (const auto& row : matrix_contents)
	{
		for (const auto& element : row)
		{
			if (tic_tac_toe_player::X == element)
				ostr << "|X";
			else if (tic_tac_toe_player::O == element)
				ostr << "|O";
		}

		ostr << "|\n__________";
	}

	return ostr;
}

istream& operator>>(istream& istr, tic_tac_toe& m)
{
	auto& matrix = m.get_matrix_contents();

	matrix.clear();

	vector<tic_tac_toe_player> row{};
	string line{};
	size_t prev_col_width{};

	while (getline(istr, line))
	{
		line = trim(line);

		if (line != "<>")
		{
			if ("X" == line)
				row.emplace_back(tic_tac_toe_player::X);
			else if ("O" == line)
				row.emplace_back(tic_tac_toe_player::O);
			else if ("-" == line)
				row.emplace_back(tic_tac_toe_player::EMPTY);
		}
		else
		{
			if (!prev_col_width)
				prev_col_width = row.size();
			else if (row.size() != prev_col_width)
				throw runtime_error{
					"The rows of matrix must have equal column widths!"
				};
			matrix.emplace_back(row);
			row.clear();
		}

		if (prev_col_width && (row.size() != prev_col_width))
			throw runtime_error{"The rows of matrix must have equal column widths!"};

		matrix.emplace_back(row);
	}

	return istr;
}

string NoughtsDeterminer(string* str_arr, const size_t str_arr_size)
{
	tic_tac_toe t{str_arr, str_arr_size};

	const size_t space{
		t.find_correct_spot_for_winning()
	}; // called with tic_tac_toe_player::XO
	// by default

	if (string::npos != space)
		return to_string(space);

	return "-1";
}

int main()
{
	// string A[] = gets(stdin);
	// cout << NoughtsDeterminer(A, sizeof(A) / sizeof(*A));
	string B[] = {"X", "O", "-", "<>", "-", "O", "-", "<>", "O", "X", "-"};
	cout << NoughtsDeterminer(B, sizeof(B) / sizeof(*B))
		<< '\n'; // expected output: "2"
	string C[] = {"X", "-", "O", "<>", "-", "-", "O", "<>", "-", "-", "X"};
	cout << NoughtsDeterminer(C, sizeof(C) / sizeof(*C))
		<< '\n'; // expected output: "5"
	string D[] = {"X", "O", "X", "<>", "-", "O", "O", "<>", "X", "X", "O"};
	cout << NoughtsDeterminer(D, sizeof(D) / sizeof(*D))
		<< '\n'; // expected output: "4"

	string E[] = {"O", "-", "O", "<>", "-", "X", "-", "<>", "-", "-", "X"};
	cout << NoughtsDeterminer(E, sizeof(E) / sizeof(*E))
		<< '\n'; // expected output: "1"
	string F[] = {"X", "-", "X", "<>", "-", "O", "-", "<>", "-", "-", "O"};
	cout << NoughtsDeterminer(F, sizeof(F) / sizeof(*F))
		<< '\n'; // expected output: "1"
	string G[] = {"X", "-", "O", "<>", "-", "O", "-", "<>", "-", "-", "X"};
	cout << NoughtsDeterminer(G, sizeof(G) / sizeof(*G))
		<< '\n'; // expected output: "8"

	string H[] = {"X", "O", "X", "<>", "-", "O", "-", "<>", "-", "-", "-"};
	cout << NoughtsDeterminer(H, sizeof(H) / sizeof(*H))
		<< '\n'; // expected output: "9"
	string I[] = {"X", "-", "X", "<>", "-", "-", "O", "<>", "O", "-", "-"};
	cout << NoughtsDeterminer(I, sizeof(I) / sizeof(*I))
		<< '\n'; // expected output: "1"
	string J[] = {"-", "-", "X", "<>", "-", "O", "X", "<>", "O", "-", "-"};
	cout << NoughtsDeterminer(J, sizeof(J) / sizeof(*J))
		<< '\n'; // expected output: "10"
	string K[] = {"-", "-", "X", "<>", "-", "O", "X", "<>", "O", "-", "-"};
	cout << NoughtsDeterminer(K, sizeof(K) / sizeof(*K))
		<< '\n'; // expected output: "10"
	return 0;
}
