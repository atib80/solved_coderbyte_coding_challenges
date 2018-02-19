#include <cstdint>
#include <iostream>

using namespace std;

int64_t FirstFactorial_v1(int64_t num) {
  if (!num)
    return 1LL;

  if (num < 3LL)
    return num;

  int64_t result{num};

  while (num > 2)
    result *= --num;

  return result;
}

int64_t FirstFactorial_v2(const int64_t num) {
  if (num < 2LL)
    return 1LL;

  return num * FirstFactorial_v2(num - 1);
}

int main() {
  // cout << FirstFactorial_v1(gets(stdin));
  cout << FirstFactorial_v1(0) << '\n';  // expected output: 1
  cout << FirstFactorial_v1(1) << '\n';  // expected output: 1
  cout << FirstFactorial_v1(2) << '\n';  // expected output: 2
  cout << FirstFactorial_v1(3) << '\n';  // expected output: 6
  cout << FirstFactorial_v1(4) << '\n';  // expected output: 24
  cout << FirstFactorial_v1(5) << '\n';  // expected output: 120
  cout << FirstFactorial_v1(6) << '\n';  // expected output: 720
  cout << FirstFactorial_v1(7) << '\n';  // expected output: 5040
  cout << FirstFactorial_v1(8) << '\n';  // expected output: 40320

  return 0;
}
