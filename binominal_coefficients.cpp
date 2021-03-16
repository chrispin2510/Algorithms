#include <iostream>
#include <ctime>
using namespace std;

#define TIME_DIFF ((double)(end-begin)/(double)(CLOCKS_PER_SEC))

int binomial(int n, int k)
// computes C(n, k)
{
  int **C = new int*[n + 1];
  for (int i=0; i<=n; i++) C[i] = new int[k + 1];

  for (int i=0; i <= n; i++)
    for (int j=0; j <= min(i, k); j++)
      if (j == 0 || j == i)
	C[i][j] = 1;
      else C[i][j] = C[i-1][j-1] + C[i-1][j];
  return(C[n][k]);
}

int binomial_naive(int n, int k)
{
  int **C = new int*[n + 1];
  for (int i=0; i<=n; i++) C[i] = new int[k+1];

  for (int i=0; i <= n; i++)
    for (int j=0; j <= i; j++)
      if (j == 0 || j == i)
	C[i][j] = 1;
      else C[i][j] = C[i-1][j-1] + C[i-1][j];
  return(C[n][k]);
}

int main(void)
{
  time_t begin, end;
  int n, k;
  cout << "give n and k: ";
  cin >> n >> k;
  begin = clock();
  int c1 = binomial(n, k);
  end = clock();
  cout << "EFFICIENT C(" << n << ", " << k
       << ") is " << c1
       << " in " << TIME_DIFF << endl;
  begin = clock();
  int c2 = binomial_naive(n, k);
  end = clock();
  cout << "NAIVE C(" << n << ", " << k
       << ") is " << c2
       << " in " << TIME_DIFF << endl;

  return(0);
}
