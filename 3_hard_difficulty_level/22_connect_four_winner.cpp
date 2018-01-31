/*
Coderbyte coding challenge: Connect Four Winner

Using the C++ language, have the function ConnectFourWinner(strArr) read the
strArr parameter being passed which will represent a 6x7 Connect Four board. The
rules of the game are: two players alternate turns and place a colored disc down
into the grid from the top and the disc falls down the column until it hits the
bottom or until it hits a piece beneath it. The object of the game is to connect
four of one's own discs of the same color next to each other vertically,
horizontally, or diagonally before your opponent. The input strArr will
represent a Connect Four board and it will be structured in the following
format: ["R/Y","(R,Y,x,x,x,x,x)","(...)","(...)",...)] where R represents the
player using red discs, Y represents the player using yellow discs and x
represents an empty space on the board. The first element of strArr will be
either R or Y and it represents whose turn it is. Your program should determine,
based on whose turn it is, whether a space exists that can give that player a
win. If a space does exist your program should return the space in the following
format: (RxC) where R=row and C=column. If no space exists, return the string
none. The board will always be in a legal setup.

For example, if strArr is:
["R","(x,x,x,x,x,x,x)","(x,x,x,x,x,x,x)","(x,x,x,x,x,x,x)","(x,x,x,R,x,x,x)","(x,x,x,R,x,x,x)","(x,x,x,R,Y,Y,Y)"]
then your program should return (3x4).

Another example, if strArr is:
["Y","(x,x,x,x,x,x,x)","(x,x,x,x,x,x,x)","(x,x,x,x,x,x,x)","(x,x,Y,Y,x,x,x)","(x,R,R,Y,Y,x,R)","(x,Y,R,R,R,Y,R)"]
then your program should return (3x3).
*/

#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string trim(const string& str)
{
    const size_t str_len{ str.length() };

    if (!str_len)
        return string{};

    size_t first{}, last{ str_len - 1 };

    for (; first <= last; ++first) {
        if (!isspace(str[first]))
            break;
    }

    if (first > last)
        return string{};

    for (; last > first; --last) {
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

    string needle_st{ needle };

    const size_t source_len{ source.length() };

    const size_t needle_len{ needle_st.size() };

    if (!source_len)
        return parts;

    if (!needle_len) {
        const size_t upper_limit{ max_count < source_len ? max_count : source_len };
        for (size_t i{}; i < upper_limit; i++)
            parts.emplace_back(1, source[i]);
        return parts;
    }

    size_t number_of_parts{}, prev{};

    while (true) {
        const size_t current{ source.find(needle_st, prev) };

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

    if (prev < source_len) {
        if (string::npos == max_count)
            parts.emplace_back(source.substr(prev));

        else if ((string::npos != max_count) && (parts.size() < max_count))
            parts.emplace_back(source.substr(prev));
    }

    return parts;
}

enum class cf {
    red_disc,
    yellow_disc,
    empty_slot
};

// winning sequence of discs (R or Y) in horizontal, vertical or diagonal
// direction
bool is_there_a_winning_sequence_of_discs_at_specified_position(
    const vector<vector<cf>>& game_board,
    const pair<int, int>& position)
{
    const cf player_disc{ game_board[position.first][position.second] };

    const int min_x{ position.first > 3 ? position.first - 3 : 0 };
    const int max_x{ position.first < 2 ? position.first + 3 : 5 };
    const int min_y{ position.second > 3 ? position.second - 3 : 0 };
    const int max_y{ position.second < 3 ? position.second + 3 : 6 };

    // 1. check vertical direction for >= 4 player discs of the same color
    // (cf::red_disc or cf::yellow_disc)

    size_t count{ 1 };

    for (int x{ position.first - 1 }; x >= min_x; x--) {
        if (player_disc != game_board[x][position.second])
            break;
        count++;
    }

    if (count >= 4)
        return true;

    for (int x{ position.first + 1 }; x <= max_x; x++) {
        if (player_disc != game_board[x][position.second])
            break;
        count++;
    }

    if (count >= 4)
        return true;

    // 2. check horizontal direction for >= 4 player discs of the same color
    // (cf::red_disc or cf::yellow_disc)

    count = 1;

    for (int y{ position.second - 1 }; y >= min_y; y--) {
        if (player_disc != game_board[position.first][y])
            break;
        count++;
    }

    if (count >= 4)
        return true;

    for (int y{ position.second + 1 }; y <= max_y; y++) {
        if (player_disc != game_board[position.first][y])
            break;
        count++;
    }

    if (count >= 4)
        return true;

    // 3. check first diagonal direction (k=1) for >= 4 player discs of the same
    // color (cf::red_disc or cf::yellow_disc)

    count = 1;

    for (int x{ position.first - 1 }, y{ position.second - 1 }; x >= 0 && y >= 0;
         x--, y--) {
        if (player_disc != game_board[x][y])
            break;
        count++;
    }

    if (count >= 4)
        return true;

    for (int x{ position.first + 1 }, y{ position.second + 1 }; x <= 5 && y <= 6;
         x++, y++) {
        if (player_disc != game_board[x][y])
            break;
        count++;
    }

    if (count >= 4)
        return true;

    // 4. check second diagonal direction (k=-1) for >= 4 player discs of the same
    // color (cf::red_disc or cf::yellow_disc)

    count = 1;

    for (int x{ position.first + 1 }, y{ position.second - 1 }; x <= 5 && y >= 0;
         x++, y--) {
        if (player_disc != game_board[x][y])
            break;
        count++;
    }

    if (count >= 4)
        return true;

    for (int x{ position.first - 1 }, y{ position.second + 1 }; x >= 0 && y <= 6;
         x--, y++) {
        if (player_disc != game_board[x][y])
            break;
        count++;
    }

    if (count >= 4)
        return true;

    return false;
}

vector<pair<int, cf>> get_top_level_game_items(
    const vector<vector<cf>>& game_board)
{
    vector<pair<int, cf>> top_level_game_items(7,
        pair<int, cf>{ 5, cf::empty_slot });

    for (int y{}; y != 7; y++) {
        for (int x{}; x != 6; x++) {
            if (cf::empty_slot != game_board[x][y]) {
                top_level_game_items[y] = make_pair(x, game_board[x][y]);
                break;
            }
        }
    }

    return top_level_game_items;
}

string play_the_game(vector<vector<cf>>& game_board, const cf& player)
{
    const vector<pair<int, cf>> top_level_game_items{
        get_top_level_game_items(game_board)
    };

    for (size_t y{}; y != 7; y++) {
        if ((0 == top_level_game_items[y].first) && (cf::empty_slot != top_level_game_items[y].second))
            continue;

        const int x_pos_for_player_disc{ cf::empty_slot != top_level_game_items[y].second
                ? top_level_game_items[y].first - 1
                : top_level_game_items[y].first };

        const cf prev_game_item{ game_board[x_pos_for_player_disc][y] };

        game_board[x_pos_for_player_disc][y] = player;

        if (is_there_a_winning_sequence_of_discs_at_specified_position(
                game_board, make_pair(x_pos_for_player_disc, y))) {
            ostringstream oss{};
            oss << '(' << (x_pos_for_player_disc + 1) << 'x' << (y + 1) << ')';
            return oss.str();
        }

        game_board[x_pos_for_player_disc][y] = prev_game_item;
    }

    return "none";
}

vector<vector<cf>> construct_connect_four_game_board(
    string* str_arr,
    const size_t str_arr_size)
{
    vector<vector<cf>> game_board(6, vector<cf>(7, cf::empty_slot));

    for (size_t i{ 1u }; i != str_arr_size; i++) {
        str_arr[i] = trim(str_arr[i]);
        str_arr[i].erase(begin(str_arr[i]));
        str_arr[i].erase(--end(str_arr[i]));
        const auto row_elements = split(str_arr[i], ",", 7);
        if (7u != row_elements.size())
            throw runtime_error{ "not possible" };
        for (size_t j{}; j != 7; j++) {
            if ("x" == row_elements[j] || "X" == row_elements[j])
                continue;

            game_board[i - 1][j] = "R" == row_elements[j] || "r" == row_elements[j]
                ? cf::red_disc
                : cf::yellow_disc;
        }
    }

    return game_board;
}

string ConnectFourWinner(string* str_arr, const size_t str_arr_size)
{
    if (str_arr_size < 7)
        return "not possible";

    const cf player{ "R" == *str_arr || "r" == *str_arr ? cf::red_disc
                                                        : cf::yellow_disc };

    vector<vector<cf>> game_board{
        construct_connect_four_game_board(str_arr, str_arr_size)
    };

    return play_the_game(game_board, player);
}

int main()
{
    // string A[] = gets(stdin);
    // cout << ConnectFourWinner(A, sizeof(A)/sizeof(*A));

    string B[] = { "R",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,R,x,x,x)",
        "(x,x,x,R,x,x,x)",
        "(x,x,x,R,Y,Y,Y)" };
    cout << ConnectFourWinner(B, sizeof(B) / sizeof(*B))
         << '\n'; // expected output: "(3x4)"
    string C[] = { "Y",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,Y,Y,x,x,x)",
        "(x,R,R,Y,Y,x,R)",
        "(x,Y,R,R,R,Y,R)" };
    cout << ConnectFourWinner(C, sizeof(C) / sizeof(*C))
         << '\n'; // expected output: "(3x3)"
    string D[] = { "R",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,R,x,x,x)",
        "(x,x,x,R,x,x,x)",
        "(x,x,x,R,Y,Y,Y)" };
    cout << ConnectFourWinner(D, sizeof(D) / sizeof(*D))
         << '\n'; // expected output: "(3x4)"
    string E[] = { "Y",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,Y,Y,x,x,x)",
        "(x,R,R,Y,Y,x,R)",
        "(x,Y,R,R,R,Y,R)" };
    cout << ConnectFourWinner(E, sizeof(E) / sizeof(*E))
         << '\n'; // expected output: "(3x3)"
    string F[] = { "Y",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(Y,Y,Y,x,R,R,R)" };
    cout << ConnectFourWinner(F, sizeof(F) / sizeof(*F))
         << '\n'; // expected output: "(6x4)"
    string G[] = { "R",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(Y,Y,Y,x,R,R,R)" };
    cout << ConnectFourWinner(G, sizeof(G) / sizeof(*G))
         << '\n'; // expected output: "(6x4)"
    string H[] = { "R",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(Y,x,x,x,x,x,R)",
        "(Y,x,x,x,x,x,R)",
        "(Y,x,x,x,x,x,R)" };
    cout << ConnectFourWinner(H, sizeof(H) / sizeof(*H))
         << '\n'; // expected output: "(3x7)"
    string I[] = { "Y",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,R,Y,x,Y)",
        "(x,x,x,R,R,Y,R)",
        "(x,x,x,Y,R,R,Y)" };
    cout << ConnectFourWinner(I, sizeof(I) / sizeof(*I))
         << '\n'; // expected output: "(3x4)"
    string J[] = { "R",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(x,x,x,x,x,x,x)",
        "(R,x,Y,x,x,x,x)",
        "(R,Y,R,Y,R,Y,Y)",
        "(R,Y,R,Y,R,Y,R)" };
    cout << ConnectFourWinner(J, sizeof(J) / sizeof(*J))
         << '\n'; // expected output: "(3x1)"

    return 0;
}
