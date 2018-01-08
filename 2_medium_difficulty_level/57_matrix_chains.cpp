/*
Coderbyte coding challenge: Matrix Chains

Using the C++ language, have the function MatrixChains(arr) read the array of positive integers stored in arr where every pair will represent an NxM matrix. 
For example: if arr is [1, 2, 3, 4] this means you have a 1x2, 2x3, and a 3x4 matrix. So there are N-1 total matrices where N is the length of the array. 
Your goal is to determine the least number of multiplications possible after multiplying all the matrices. 
Matrix multiplication is associative so (A*B)*C is equal to A*(B*C).

For the above example, let us assume the following letters represent the different matrices: A = 1x2, B = 2x3, and C = 3x4. 
Then we can multiply the matrices in the following orders: (AB)C or A(BC). The first ordering requires (1*2*3) = 6 
then we multiply this new 1x3 matrix by the 3x4 matrix and we get (1*3*4) = 12. So in total, this ordering required 6 + 12 = 18 multiplications. 
Your program should therefore return 18 because the second ordering produces more multiplications. The input array will contain between 3 and 30 elements.

See the Cormen book for details of the following algorithm.

Sample test cases:

Input:  2, 3, 4
Output: 24

Input:  1, 4, 5, 6, 8
Output: 98
*/

#include <iostream>
#include <climits>

using std::cout;
 
// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
int MatrixChainOrder(const int* p, const size_t n)
{
 
    /* For simplicity of the program, one extra row and one
       extra column are allocated in m[][].  0th row and 0th
       column of m[][] are not used */
    int** m = new int*[n]{};

    for (size_t i{}; i < n; i++) m[i] = new int[n]{};
 
    int j, k, q;
 
    /* m[i,j] = Minimum number of scalar multiplications needed
       to compute the matrix A[i]A[i+1]...A[j] = A[i..j] where
       dimension of A[i] is p[i-1] x p[i] */
 
    // cost is zero when multiplying one matrix.
    for (size_t i{1u}; i < n; i++) m[i][i] = 0;
 
    // L is chain length.
    for (size_t L{2}; L < n; L++)
    {
        for (size_t i{1u}; i < n - L + 1; i++)
        {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j]) m[i][j] = q;
            }
        }
    }

    const int result { m[1][n-1] };

    for (size_t i{}; i < n; i++) {
        if (m[i]) {
            delete[] m[i];
            m[i] = nullptr;
        }        
    }

    if (m) {
        delete[] m;
        m = nullptr;
    }    

    return result;
}
 
int main()
{
  
  // const int A[] = gets(stdin);
  // cout << MatrixChains(A, sizeof(A)/sizeof(*A));
  const int B[] = {1, 2, 3, 4};
  cout << MatrixChainOrder(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 18
  const int C[] = {2, 3, 4};
  cout << MatrixChainOrder(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 24
  const int D[] = {1, 4, 5, 6, 8};
  cout << MatrixChainOrder(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 98
  const int E[] = {10, 2, 4, 12, 15, 20, 4, 56};
  cout << MatrixChainOrder(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: 2784
  const int F[] = {10, 20, 100, 5, 4, 6, 9, 1, 2, 3, 5, 10, 9, 71};
  cout << MatrixChainOrder(F, sizeof(F)/sizeof(*F)) << '\n'; // expected output: 4308
  const int G[] = {5, 6, 7, 8, 9, 1, 1, 1, 2}; 
  cout << MatrixChainOrder(G, sizeof(G)/sizeof(*G)) << '\n'; // expected output: 213

  return 0;
}
