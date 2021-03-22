#include <iostream>
#include <iomanip>
using namespace std;

int **knapsack(int *profit, int *weight, int m, int n)
{
    int **bag = new int*[m +1];
    for (int i = 0; i < m + 1; i++) bag[i] = new int[n+1];

    for (int i = 0; i <= m; i++) bag[0][i] = 0;

    for (int i = 0; i <= n; i++) bag[i][0] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            bag[i][j] = max(bag[i-1][j], bag[i-1][m-weight[i]] + profit[i]);
        }
    }
    return(bag);
}


void output(int **grid, int m, int n)
{
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1 && j <= n) cout << ", ";
            cout << setw(3) << right << grid[i][j];
        }
        cout << endl;
    }
}

int main(void)
{
    int p[] = {0, 1, 2, 5, 6};
    int w[] = {0, 2, 3, 4, 5};
        
    int **knap = knapsack(p, w, 8, 4);

    output(knap, 8, 4);
}
