/*
Coderbyte coding challenge: Blackjack Highest

Using the C++ language, have the function BlackjackHighest(strArr) take the strArr parameter being passed
which will be an array of numbers and letters representing blackjack cards.
Numbers in the array will be written out. So for example strArr may be ["two","three","ace","king"].
The full list of possibilities for strArr is: two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace.
Your program should output below, above, or blackjack signifying if you have blackjack (numbers add up to 21)
or not and the highest card in your hand in relation to whether or not you have blackjack.
If the array contains an ace but your hand will go above 21, you must count the ace as a 1.
You must always try and stay below the 21 mark.
So using the array mentioned above, the output should be below king.
The ace is counted as a 1 in this example because if it wasn't you would be above the 21 mark.
Another example would be if strArr was ["four","ten","king"], the output here should be above king.
If you have a tie between a ten and a face card in your hand, return the face card as the "highest card".
If you have multiple face cards, the order of importance is jack, queen, then king.

Sample test cases:

Input:  "four","ace","ten"
Output: "below ten"

Input:  "ace","queen"
Output: "blackjack ace"
*/

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <locale>

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

string get_correct_output_string(const string& highest_card_name, const size_t hand)
{
	ostringstream oss{};

	if (21 == hand)
	{
		oss << "blackjack " << highest_card_name;
	}
	else if (hand < 21)
	{
		oss << "below " << highest_card_name;
	}
	else
	{
		oss << "above " << highest_card_name;
	}

	return oss.str();
}

pair<string, size_t> calculate_final_hand_value_and_find_card_with_highest_value(
	const unordered_map<string, size_t>& blackjack_cards,
	const vector<string>& cards)
{
	size_t hand{};
	string highest_card_name{"one"};
	size_t highest_card_value{1u};

	for (const auto& card : cards)
	{
		if (("ace" == card) && (hand > 10))
		{
			hand++;
		}
		else
		{
			const auto itr = blackjack_cards.find(card);
			hand += itr->second;
			if (itr->second > highest_card_value)
			{
				highest_card_value = itr->second;
				highest_card_name = card;
			}
			else if ((10 == itr->second) && (10 == highest_card_value))
			{
				if (("jack" == card) && ("jack" != highest_card_name))
					highest_card_name = "jack";
				else if (("ten" != card) && ("ten" == highest_card_name))
					highest_card_name = card;
				else if (("queen" == card) && ("king" == highest_card_name))
					highest_card_name = card;
			}
		}
	}

	return make_pair(highest_card_name, hand);
}

string BlackjackHighest(string* str_arr, const size_t str_arr_size)
{
	for (size_t i{}; i != str_arr_size; i++)
	{
		str_arr[i] = trim(str_arr[i]);
		for (auto& ch : str_arr[i]) ch = tolower(ch, locale{});
	}

	vector<string> cards(str_arr, str_arr + str_arr_size);

	unordered_map<string, size_t> blackjack_cards{
		{"one", 1},{"two", 2},{"three", 3},{"four", 4},{"five", 5},{"six", 6},{"seven", 7},
		{"eight", 8},{"nine", 9},{"ten", 10},{"jack", 10},{"queen", 10},{"king", 10},{"ace", 11}
	};

	for (const auto& card : cards)
	{
		if (blackjack_cards.find(card) == end(blackjack_cards)) return "not possible";
	}

	stable_sort(begin(cards), end(cards), [&](const string& lhs, const string& rhs)
	{
		const auto itr1 = blackjack_cards.find(lhs);
		const auto itr2 = blackjack_cards.find(rhs);
		return itr1->second < itr2->second;
	});

	const pair<string, size_t> result{calculate_final_hand_value_and_find_card_with_highest_value(blackjack_cards, cards)};

	return get_correct_output_string(result.first, result.second);
}

int main()
{
	// string A[] = gets(stdin);
	// cout << BlackjackHighest(A, sizeof(A)/sizeof(*A));
	string B[] = {"two","three","ace","king"};
	cout << BlackjackHighest(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: "below king"
	string C[] = {"four","ten","king"};
	cout << BlackjackHighest(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: "above king"
	string D[] = {"four","ace","ten"};
	cout << BlackjackHighest(D, sizeof(D) / sizeof(*D)) << '\n'; // expected output: "below ten"
	string E[] = {"ace","queen"};
	cout << BlackjackHighest(E, sizeof(E) / sizeof(*E)) << '\n'; // expected output: "blackjack ace"

	return 0;
}
