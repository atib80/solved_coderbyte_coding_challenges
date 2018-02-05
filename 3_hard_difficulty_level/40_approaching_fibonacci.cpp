/*
Coderbyte coding challenge: Approaching Fibonacci

Using the C++ language, have the function ApproachingFibonacci(arr) take the arr parameter being passed
which will be an array of integers and determine the smallest positive integer (including zero)
that can be added to the array to make the sum of all of the numbers in the array add up to the next closest Fibonacci number.
For example: if arr is [15, 1, 3], then your program should output 2 because if you add up 15 + 1 + 3 + 2
you get 21 which is the closest Fibonacci number.

Sample test cases:

Input:  5,2,1
Output: 0

Input:  1,20,2,5
Output: 6
*/

#include <climits>
#include <cmath>
#include <iostream>
#include <numeric>

using namespace std;

int ApproachingFibonacci(const int *arr, const size_t arr_size)
{
    const int arr_sum{accumulate(arr, arr + arr_size, 0)};

    int min_distance{INT_MAX};

    int a = 0;
    int b = 1;

    while (true)
    {
        const int temp{a};
        a = b;
        b = a + temp;

        if (b > arr_sum)
        {
            if (b - arr_sum < min_distance)
            {
                min_distance = b - arr_sum;
                continue;
            }

            return min_distance;
        }

        /*if (b < arr_sum)
		{
			if (arr_sum - b < min_distance)
			{
				min_distance = arr_sum - b;
				continue;
			}

			return min_distance;
		}*/

        if (arr_sum == b)
            return 0;
    }
}

int main()
{
    // const int A[] = gets(stdin);
    // cout << ApproachingFibonacci(A, sizeof(A)/sizeof(*A));
    const int B[] = {15, 1, 3};
    cout << ApproachingFibonacci(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: 2
    const int C[] = {5, 2, 1};
    cout << ApproachingFibonacci(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: 0
    const int D[] = {1, 20, 2, 5};
    cout << ApproachingFibonacci(D, sizeof(D) / sizeof(*D)) << '\n'; // expected output: 6
    const int E[] = {6, 6, 4};
    cout << ApproachingFibonacci(E, sizeof(E) / sizeof(*E)) << '\n'; // expected output: 5

    return 0;
}
