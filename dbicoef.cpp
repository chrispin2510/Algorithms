#include <iostream>
using namespace std;

// prototype
void column_init(int **, int);
void diagonal_init(int **, int);

int C(int n, int k)
// return binomial coeffiecient of (n, k)
{
  if (n < 0 || k < 0) return(0);
  
  int **bc = new int*[n+1];
  for (int i=0; i<= n; i++) bc[i] = new int[k+1];

  for (int i=0; i<=n; i++) {
    column_init(bc, i);
    diagonal_init(bc, i);
  }

  for (int i=2; i<=n; i++)
    for (int j=1; j<=k; j++)
      bc[i][j] = bc[i-1][j] + bc[i-1][j-1];

  return(bc[n][k]);
}

int main(void)
{
  int n, k;
  cout << "give n and k: ";
  cin >> n >> k;
  cout << "C(" << n << ", " << k << ") is " << C(n, k) << endl;
  return(0);
}

void column_init(int **bc, int i)
{
  bc[i][0] = 1;
}

void diagonal_init(int **bc, int i)
{
  bc[i][i] = 1;
}
