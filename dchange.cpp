#include <iostream>
#include <iomanip>
#include <climits>
#include <vector>
using namespace std;

void goalCell(const vector<int> &, const int, int *, int *);

int minCoinChange(const vector<int> &coins, const int amount)
{
  int i, j;
  vector<vector<int>> C;
  for (i = 0; i <= coins.size(); i++) {
    vector<int> row(amount + 1);
    C.push_back(row);
  }
  for (i = 0; i <= coins.size(); i++) {
    C[i][0] = 0;
  }
  for (j = 1; j <= amount; j++) {
    C[0][j] = INT_MAX;
  }
  for (i = 1; i <= coins.size(); i++) {
    for (j = 1; j <= amount; j++) {
      if ((j - coins[i-1]) < 0) {
	C[i][j] = C[i-1][j];
      }
      else {
	C[i][j] = min(1 + C[i][j - coins[i-1]], C[i - 1][j]);
      }
    }
  }
  goalCell(coins, amount, &i, &j);
  return C[i][j];
}

int main(void)
{
  vector<int> coins{1, 4, 6};
  int amount = 11;
  cout << minCoinChange(coins, amount) << endl;
}

void goalCell(const vector<int> &coins, const int amount, int *i, int *j)
{
  *i = coins.size();
  *j = amount;
}
