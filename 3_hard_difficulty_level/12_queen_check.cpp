/*
Coderbyte coding challenge: Queen Check

Using the C++ language, have the function QueenCheck(strArr) read strArr which will be an array consisting of the locations 
of a Queen and King on a standard 8x8 chess board with no other pieces on the board. 
The structure of strArr will be the following: ["(x1,y1)","(x2,y2)"] with (x1,y1) representing the position of the queen 
and (x2,y2) representing the location of the king with x and y ranging from 1 to 8. 
Your program should determine if the king is in check based on the current positions of the pieces, 
and if so, return the number of spaces it can move to in order to get out of check. 
If the king is not in check, return -1. 
For example: if strArr is ["(4,4)","(6,6)"] then your program should output 6. 
Remember, because only the queen and king are on the board, if the queen is checking the king by being directly adjacent to it, 
technically the king can capture the queen.

Sample test cases:

Input:  "(1,1)","(1,4)"
Output: "3"

Input:  "(3,1)","(4,4)"
Output: "-1"
*/

#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

pair<int, int> parse_coordinate_pair(const string &str)
{

    size_t start{str.find_first_of("0123456789")};

    if (string::npos == start)
        return make_pair(0, 0);

    size_t last{str.find_first_not_of("0123456789")};

    if (string::npos == last)
        return make_pair(0, 0);

    const int x{stoi(str.substr(start, last - start))};

    start = str.find_first_of("0123456789", last);

    if (string::npos == start)
        return make_pair(0, 0);

    last = str.find_first_not_of("0123456789", start + 1);

    const int y{string::npos == last ? stoi(str.substr(start)) : stoi(str.substr(start, last - start))};

    return make_pair(x, y);
}

int distance(const pair<int, int> &king, const pair<int, int> &queen)
{

    return (abs(queen.first - king.first) + abs(queen.second - king.second));
}

bool is_king_in_check_by_queen(const pair<int, int> &king, const pair<int, int> &queen)
{

    if (king.first == queen.first || king.second == queen.second)
        return true;

    if ((king.first > queen.first) && (king.second > queen.second) && (king.first - queen.first == king.second - queen.second))
        return true;

    if ((king.first > queen.first) && (king.second < queen.second) && (king.first - queen.first == queen.second - king.second))
        return true;

    if ((king.first < queen.first) && (king.second > queen.second) && (queen.first - king.first == king.second - queen.second))
        return true;

    if ((king.first < queen.first) && (king.second < queen.second) && (queen.first - king.first == queen.second - king.second))
        return true;

    return false;
}

string QueenCheck(string *str_arr, const size_t str_arr_size)
{

    if (!str_arr || str_arr_size < 2u)
        return "not possible";

    const int min_coord{1}, max_coord{8};

    str_arr[0] = trim(str_arr[0]);
    str_arr[0].erase(begin(str_arr[0]));
    str_arr[0].erase(--end(str_arr[0]));

    auto const queen = parse_coordinate_pair(str_arr[0]);

    str_arr[1] = trim(str_arr[1]);
    str_arr[1].erase(begin(str_arr[1]));
    str_arr[1].erase(--end(str_arr[1]));

    auto const king = parse_coordinate_pair(str_arr[1]);

    if (!is_king_in_check_by_queen(king, queen))
        return "-1";

    size_t moves_count{};

    const int min_x{king.first > min_coord ? king.first - 1 : min_coord};
    const int max_x{king.first < max_coord ? king.first + 1 : max_coord};
    const int min_y{king.second > min_coord ? king.second - 1 : min_coord};
    const int max_y{king.second < max_coord ? king.second + 1 : max_coord};

    for (int x{min_x}; x <= max_x; x++)
    {

        for (int y{min_y}; y <= max_y; y++)
        {

            if ((x == king.first) && (y == king.second))
                continue;

            const auto king_new_coord = make_pair(x, y);

            if (!is_king_in_check_by_queen(king_new_coord, queen))
                moves_count++;

            else if (0 == distance(king_new_coord, queen))
                moves_count++;
        }
    }

    return to_string(moves_count);
}

int main()
{

    // string A[] = gets(stdin);
    // cout << QueenCheck(A, sizeof(A)/sizeof(*A));
    string B[] = {"(4,4)", "(6,6)"};
    cout << QueenCheck(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: "6"
    string C[] = {"(1,1)", "(1,4)"};
    cout << QueenCheck(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: "3"
    string D[] = {"(3,1)", "(4,4)"};
    cout << QueenCheck(D, sizeof(D) / sizeof(*D)) << '\n'; // expected output: "-1"
    string E[] = {"(1,8)", "(2,7)"};
    cout << QueenCheck(E, sizeof(E) / sizeof(*E)) << '\n'; // expected output: "3"
    string F[] = {"(8,2)", "(7,3)"};
    cout << QueenCheck(F, sizeof(F) / sizeof(*F)) << '\n'; // expected output: "3"
    string G[] = {"(8,2)", "(7,1)"};
    cout << QueenCheck(G, sizeof(G) / sizeof(*G)) << '\n'; // expected output: "2"

    return 0;
}
