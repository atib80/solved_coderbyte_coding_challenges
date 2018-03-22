/*
Coderbyte coding challenge: Seating Students

Using the C++ language, have the function SeatingStudents(arr) read the array of
integers stored in arr which will be in the following format: [K, r1, r2, r3,
...] where K represents the number of desks in a classroom, and the rest of the
integers in the array will be in sorted order and will represent the desks that
are already occupied. All of the desks will be arranged in 2 columns, where desk
#1 is at the top left, desk #2 is at the top right, desk #3 is below #1, desk #4
is below #2, etc. Your program should return the number of ways 2 students can
be seated next to each other. This means 1 student is on the left and 1 student
on the right, or 1 student is directly above or below the other student.

For example: if arr is [12, 2, 6, 7, 11] then this classrooms looks like the
following picture:

Based on above arrangement of occupied desks, there are a total of 6 ways to
seat 2 new students next to each other. The combinations are: [1, 3], [3, 4],
[3, 5], [8, 10], [9, 10], [10, 12]. So for this input your program should
return 6. K will range from 2 to 24 and will always be an even number. After K,
the number of occupied desks in the array can range from 0 to K.

Sample test cases:

Input:  6, 4
Output: 4

Input:  8, 1, 8
Output: 6
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t SeatingStudents(const size_t* arr, const size_t arr_size) {
  if (1 == arr_size)
    return (arr[0] / 2 * arr[0] / 2);

  const size_t number_of_desks{arr[0]};

  vector<bool> seats(number_of_desks);

  for (size_t i{1}; i < arr_size; i++)
    seats[arr[i] - 1] = true;

  size_t count{};

  for (size_t i{}; i < number_of_desks; i++) {
    if (!seats[i]) {
      if (i % 2 == 0) {
        if (i + 1 < number_of_desks && !seats[i + 1])
          count++;
        if (i + 2 < number_of_desks && !seats[i + 2])
          count++;
      } else if (i + 2 < number_of_desks && !seats[i + 2])
        count++;
    }
  }

  return count;
}

int main() {
  // const size_t A[] = gets(stdin);
  // cout << SeatingStudents(A, sizeof(A)/sizeof(*A));
  const size_t B[] = {12, 2, 6, 7, 11};
  cout << SeatingStudents(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 6
  const size_t C[] = {6, 4};
  cout << SeatingStudents(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 4
  const size_t D[] = {8, 1, 8};
  cout << SeatingStudents(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 6
  const size_t E[] = {4};
  cout << SeatingStudents(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 4
  const size_t F[] = {2};
  cout << SeatingStudents(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 1

  return 0;
}
