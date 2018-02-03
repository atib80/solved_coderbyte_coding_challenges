/*
Coderbyte coding challenge: Step Walking

Using the C++ language, have the function StepWalking(num) take the num
parameter being passed which will be an integer between 1 and 15 that represents
the number of stairs you will have to climb. You can climb the set of stairs by
taking either 1 step or 2 steps, and you can combine these in any order. So for
example, to climb 3 steps you can either do: (1 step, 1 step, 1 step) or (2, 1)
or (1, 2). So for 3 steps we have 3 different ways to climb them, so your
program should return 3. Your program should return the number of combinations
of climbing num steps.

Sample test cases:

Input:  1
Output: 1

Input:  3
Output: 3
*/

#include <iostream>
#include <string>

using namespace std;

size_t find_number_of_combinations(const size_t number_of_stairs,
                                   const size_t current_steps_count = 0) {
  if (number_of_stairs == current_steps_count)
    return 1;

  size_t combinations{};

  if (current_steps_count < number_of_stairs)
    combinations +=
        find_number_of_combinations(number_of_stairs, current_steps_count + 1);
  if (current_steps_count < number_of_stairs - 1)
    combinations +=
        find_number_of_combinations(number_of_stairs, current_steps_count + 2);

  return combinations;
}

size_t StepWalking(const size_t num) {
  const size_t combinations{find_number_of_combinations(num)};

  return combinations;
}

int main() {
  // cout << StepWalking(gets(stdin));
  cout << StepWalking(1) << '\n';   // expected output: 1
  cout << StepWalking(2) << '\n';   // expected output: 3
  cout << StepWalking(3) << '\n';   // expected output: 3
  cout << StepWalking(4) << '\n';   // expected output: 3
  cout << StepWalking(5) << '\n';   // expected output: 3
  cout << StepWalking(6) << '\n';   // expected output: 1
  cout << StepWalking(7) << '\n';   // expected output: 3
  cout << StepWalking(8) << '\n';   // expected output: 3
  cout << StepWalking(9) << '\n';   // expected output: 3
  cout << StepWalking(10) << '\n';  // expected output: 3

  return 0;
}
