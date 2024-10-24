// The the numbers in the row vector indicates the digits of the row of grid matrix
// for eg consider the number in row[0] will have all bits set of the digits in 0th row of the grid and the same is with the colums.
// the same is the case for the 3*3 subMatrix.

// Problem Link:https://www.geeksforgeeks.org/problems/solve-the-sudoku-1587115621/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article

#include <iostream>
#include <vector>
using namespace std;

#define N 9

bool Solve(vector<int> &row, vector<int> &col, vector<vector<int>> &subMatrix, int grid[N][N])  
{ 
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j] == 0)
            {
                for (int k = 1; k <= 9; k++)
                {
                    if ((row[i] & (1 << k)) == 0 && (col[j] & (1 << k)) == 0 && (subMatrix[i / 3][j / 3] & (1 << k)) == 0)
                    {
                        grid[i][j] = k;
                        row[i] |= 1 << k;
                        col[j] |= 1 << k;
                        subMatrix[i / 3][j / 3] |= 1 << k;

                        if (Solve(row, col, subMatrix, grid))
                            return true;

                        grid[i][j] = 0;
                        row[i] ^= 1 << k;
                        col[j] ^= 1 << k;
                        subMatrix[i / 3][j / 3] ^= 1 << k;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool SolveSudoku(int grid[N][N])
{
    vector<int> row(9, 0);
    vector<int> col(9, 0);
    vector<vector<int>> subMatrix(3, vector<int>(3, 0));
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j] == 0) continue;

            row[i] |= 1 << grid[i][j];
            col[j] |= 1 << grid[i][j];
            subMatrix[i / 3][j / 3] |= 1 << grid[i][j];
        }
    }
    return Solve(row, col, subMatrix, grid);
}

void printGrid(int grid[N][N])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (SolveSudoku(grid))
        printGrid(grid);
    else
        cout << "No solution exists";

    return 0;
}
