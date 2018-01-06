/*
Coderbyte coding challenge: Question Marks

Using the C++ language, have the function QuestionsMarks(str) take the str string parameter, which will contain single digit numbers, letters, and question marks, 
and check if there are exactly 3 question marks between every pair of two numbers that add up to 10. If so, then your program should return the string true, 
otherwise it should return the string false. If there aren't any two numbers that add up to 10 in the string, then your program should return false as well.

For example: if str is "arrb6???4xxbl5???eee5" then your program should return true because there are exactly 3 question marks between 6 and 4, and 3 question marks 
between 5 and 5 at the end of the string.

Sample test cases:

Input:  "aa6?9"
Output: "false"

Input:  "acc?7??sss?3rr1??????5"
Output: "true"
*/

#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>

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

string questions_marks(string str) {

	str = trim(str);

	size_t first_digit_pos{string::npos};

	string is_correct{"false"};

	while (true) {

		if (string::npos == first_digit_pos) {

			first_digit_pos = str.find_first_of("0123456789");

			if (string::npos == first_digit_pos) return is_correct;
		}

		size_t second_digit_pos = str.find_first_of("0123456789", first_digit_pos + 1);

		if (string::npos == second_digit_pos) return is_correct;

		string first_digit{ str.substr(first_digit_pos, 1) };

		string second_digit{ str.substr(second_digit_pos, 1) };

		size_t first_number{ stoul(first_digit) };
		
		size_t second_number{ stoul(second_digit) };

		if ((first_number + second_number ) == 10) {

			const string sub_str{ str.substr(first_digit_pos + 1, second_digit_pos - (first_digit_pos + 1)) };

			const auto number_of_question_marks = count(begin(sub_str), end(sub_str), '?');

			if (number_of_question_marks == 3) is_correct = "true";
				
			else return "false";
		}
		
		first_digit_pos = second_digit_pos;
		
		if ((first_digit_pos + 5) >= str.length()) {

			second_digit_pos = str.find_first_of("0123456789", first_digit_pos + 1);

			if (string::npos == second_digit_pos) return is_correct;

			first_digit = str.substr(first_digit_pos, 1);

			second_digit = str.substr(second_digit_pos, 1);

			first_number = stoul(first_digit);

			second_number = stoul(second_digit);

			if ((first_number + second_number) == 10) {

				const string sub_str{ str.substr(first_digit_pos + 1, second_digit_pos - (first_digit_pos + 1)) };

				const auto number_of_question_marks = count(begin(sub_str), end(sub_str), '?');

				if (number_of_question_marks == 3) is_correct = "true";
				
				else return "false";			
			}

			return is_correct;
			
		}

	}
	
}

int main() {

	// cout << questions_marks(move(string{gets(stdin)}));
	cout << questions_marks(move(string{"arrb6???4xxbl5???eee5"})) << '\n';      // expected output: "true"
	cout << questions_marks(move(string{"aa6?9"})) << '\n'; 				     // expected output: "false"
	cout << questions_marks(move(string{"acc?7??sss?3rr1??????5"})) << '\n';     // expected output: "true"
	cout << questions_marks(move(string{"9???1???9??1???9"})) << '\n';           // expected output: "false"
	cout << questions_marks(move(string{"5??aaaaaaaaaaaaaaaaaaa?5?5"})) << '\n'; // expected output: "false"
	
	return 0;
}
