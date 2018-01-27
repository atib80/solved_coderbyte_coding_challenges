/*
Coderbyte coding challenge: Matching Couples

Using the C++ language, have the function MatchingCouples(arr) take the arr parameter being passed which will be an array of integers in the following format:
[B, G, N] where B represents the number of boys, G represents the number of girls, and N represents how many people you want to pair together.
Your program should return the number of different ways you can match boys with girls given the different arguments.
For example: if arr is [5, 3, 2], N=2 here so you want to pair together 2 people, so you'll need 1 boy and 1 girl.
You have 5 ways to choose a boy and 3 ways to choose a girl, so your program should return 15.
Another example: if arr is [10, 5, 4], here N=4 so you need 2 boys and 2 girls.
We can choose 2 boys from a possible 10, and we can choose 2 girls from a possible 5.
Then we have 2 different ways to pair the chosen boys and girls. Our program should therefore return 900

N will always be an even number and it will never be greater than the maximum of (B, G). B and G will always be greater than zero.

Sample test cases:

Input:  5,5,4
Output: 200

Input:  2,2,2
Output: 4
*/

#include <iostream>

using namespace std;

int calculate_permutation(int n, const int k)
{
    const int j{n - k};

    for (int i{n - 1}; i > j; i--)
    {
        if (i < 2)
            break;
        n *= i;
    }

    return n;
}

int MatchingCouples(const int *arr, const size_t arr_size)
{
    const int B{arr[0]};
    const int G{arr[1]};
    const int N{arr[2] / 2};

    const int div_factor{(N > 1 && N % 2 == 1) ? 2 * N : N};

    const int result{(calculate_permutation(B, N) * calculate_permutation(G, N)) / div_factor};

    return result;
}

int main()
{
    // int A[] = gets(stdin);
    // cout << MatchingCouples(A, sizeof(A)/sizeof(*A));
    const int B[] = {5, 3, 2};
    cout << MatchingCouples(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: 15
    const int C[] = {10, 5, 4};
    cout << MatchingCouples(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: 900
    const int D[] = {5, 5, 4};
    cout << MatchingCouples(D, sizeof(D) / sizeof(*D)) << '\n'; // expected output: 200
    const int E[] = {2, 2, 2};
    cout << MatchingCouples(E, sizeof(E) / sizeof(*E)) << '\n'; // expected output: 4
    const int F[] = {10, 10, 6};
    cout << MatchingCouples(F, sizeof(F) / sizeof(*F)) << '\n'; // expected output: 86400
    const int G[] = {15, 10, 6};
    cout << MatchingCouples(G, sizeof(G) / sizeof(*G)) << '\n'; // expected output: 327600

    return 0;
}
