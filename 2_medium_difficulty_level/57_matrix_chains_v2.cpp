/*
Coderbyte coding challenge: Matrix Chains

Using the C++ language, have the function MatrixChains(arr) read the array of
positive integers stored in arr where every pair will represent an NxM matrix.
For example: if arr is [1, 2, 3, 4] this means you have a 1x2, 2x3, and a 3x4
matrix. So there are N-1 total matrices where N is the length of the array. Your
goal is to determine the least number of multiplications possible after
multiplying all the matrices. Matrix multiplication is associative so (A*B)*C is
equal to A*(B*C).

For the above example, let us assume the following letters represent the
different matrices: A = 1x2, B = 2x3, and C = 3x4. Then we can multiply the
matrices in the following orders: (AB)C or A(BC). The first ordering requires
(1*2*3) = 6 then we multiply this new 1x3 matrix by the 3x4 matrix and we get
(1*3*4) = 12. So in total, this ordering required 6 + 12 = 18 multiplications.
Your program should therefore return 18 because the second ordering produces
more multiplications. The input array will contain between 3 and 30 elements.

See the Cormen book for details of the following algorithm.

Sample test cases:

Input:  2, 3, 4
Output: 24

Input:  1, 4, 5, 6, 8
Output: 98
*/

#include <iostream>
#include <string>

using namespace std;

size_t MatrixChainOrder_v2(const int* matrices,
                           const size_t i,
                           const size_t j) {
  if (i == j)
    return 0;

  size_t min_number_of_multiplications{string::npos};

  for (size_t k{i}; k < j; k++) {
    const size_t count{MatrixChainOrder_v2(matrices, i, k) +
                       MatrixChainOrder_v2(matrices, k + 1, j) +
                       matrices[i - 1] * matrices[k] * matrices[j]};

    if (count < min_number_of_multiplications)
      min_number_of_multiplications = count;
  }

  return min_number_of_multiplications;
}

size_t MatrixChains(const int* arr, const size_t arr_size) {
  return MatrixChainOrder_v2(arr, 1, arr_size - 1);
}

int main() {
  // const int A[] = gets(stdin);
  // cout << MatrixChains(A, sizeof(A)/sizeof(*A));
  const int B[] = {1, 2, 3, 4};
  cout << MatrixChains(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 18
  const int C[] = {2, 3, 4};
  cout << MatrixChains(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 24
  const int D[] = {1, 4, 5, 6, 8};
  cout << MatrixChains(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 98
  const int E[] = {10, 2, 4, 12, 15, 20, 4, 56};
  cout << MatrixChains(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 2784
  const int F[] = {10, 20, 100, 5, 4, 6, 9, 1, 2, 3, 5, 10, 9, 71};
  cout << MatrixChains(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 4308
  const int G[] = {5, 6, 7, 8, 9, 1, 1, 1, 2};
  cout << MatrixChains(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: 213

  return 0;
}
