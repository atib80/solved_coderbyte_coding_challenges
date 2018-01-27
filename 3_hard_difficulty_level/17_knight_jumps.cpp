/*
Coderbyte coding challenge: Knight Jumps

Using the C++ language, have the function KnightJumps(str) read str which will be a string consisting of the location of a knight
on a standard 8x8 chess board with no other pieces on the board. The structure of str will be the following:
"(x y)" which represents the position of the knight with x and y ranging from 1 to 8.
Your program should determine the number of spaces the knight can move to from a given location.
For example: if str is "(4 5)" then your program should output 8 because the knight can move to 8 different spaces from position x=4 and y=5.

Sample test cases:

Input:  "(1 1)"
Output: 2

Input:  "(2 8)"
Output: 3
*/

#include <cctype>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

string trim(const string &str)
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

pair<int, int> parse_coordinate_pair_values(string str)
{
    str.erase(begin(str));
    str.erase(--end(str));
    const int x{stoi(str.substr(0, 1))};
    const int y{stoi(str.substr(2, 1))};
    return make_pair(x, y);
}

string KnightJumps(string str)
{

    str = trim(str);

    const auto coord = parse_coordinate_pair_values(move(str));

    if (((1 == coord.first) && (1 == coord.second)) ||
        ((1 == coord.first) && (8 == coord.second)) ||
        ((8 == coord.first) && (1 == coord.second)) ||
        ((8 == coord.first) && (8 == coord.second)))
        return "2";

    if (((3 <= coord.first) && (coord.first <= 6)) &&
        ((3 <= coord.second) && (coord.second <= 6)))
        return "8";

    size_t moves_count{};

    // upper-left corner  : (1,1) - NW direction
    // upper-right corner : (1,8) - NE direction
    // lower-left corner  : (8,1) - SW direction
    // lower-right corner : (8,8) - SE direction

    if ((coord.first >= 3) && (coord.second <= 7))
        moves_count++;
    if ((coord.first >= 3) && (coord.second >= 2))
        moves_count++;
    if ((coord.first <= 6) && (coord.second <= 7))
        moves_count++;
    if ((coord.first <= 6) && (coord.second >= 2))
        moves_count++;

    if ((coord.first <= 7) && (coord.second <= 6))
        moves_count++;
    if ((coord.first <= 7) && (coord.second >= 3))
        moves_count++;
    if ((coord.first >= 2) && (coord.second <= 6))
        moves_count++;
    if ((coord.first >= 2) && (coord.second >= 3))
        moves_count++;

    return to_string(moves_count);
}

int main()
{

    // cout << KnightJumps(move(string{ gets(stdin) }));
    cout << KnightJumps(move(string{"(4 5)"})) << '\n'; // expected output: "8"
    cout << KnightJumps(move(string{"(1 1)"})) << '\n'; // expected output: "2"
    cout << KnightJumps(move(string{"(2 8)"})) << '\n'; // expected output: "3"

    return 0;
}
