#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdio>
#define MaxRows 10005
int minIndexForRow[MaxRows];
class Matrix
{
private:
    int m, n;
    int *matrix;
    int accessElementCount, accessElementCountLimit;

public:
    Matrix()
    {
        scanf("%d %d", &m, &n);
        matrix = new int[m * n];
        for (int i = 0; i < m * n; i++)
        {
            scanf("%d", &matrix[i]);
        }
        accessElementCount = 0;
        accessElementCountLimit = 0.4 * m * n;
    }
    ~Matrix()
    {
        delete matrix;
    }
    int getElement(int row, int col)
    {
        accessElementCount += 1;
        return matrix[row * n + col];
    }
    bool passAccessElementCountLimit()
    {
        return accessElementCount <= accessElementCountLimit;
    }
    int getRowNumber()
    {
        return m;
    }
    int getColNumber()
    {
        return n;
    }
};

int cal(Matrix &matrix, int r, int c_min, int c_max)
{
    int imin = c_min, min = matrix.getElement(r, imin);
    for (int c = c_min + 1; c < c_max; c++)
    {
        int val = matrix.getElement(r, c);
        if (val < min)
        {
            imin = c;
            min = val;
        }
    }
    return imin;
}

void fill(Matrix &matrix, int r_min, int r_max, int c_min, int c_max)
{
    if (r_max - r_min == 1)
    {
        minIndexForRow[r_min] = cal(matrix, r_min, c_min, c_max);
    }
    else
    {
        int mid = r_min + (r_max - r_min) / 2;
        minIndexForRow[mid] = cal(matrix, mid, c_min, c_max);
        fill(matrix, r_min, mid, c_min, minIndexForRow[mid] + 1);
        fill(matrix, mid, r_max, minIndexForRow[mid], c_max);
    }
}

void solve(Matrix &matrix)
{
    fill(matrix, 0, matrix.getRowNumber(), 0, matrix.getColNumber());
}

int main()
{
    Matrix matrix{};
    solve(matrix);
    if (matrix.passAccessElementCountLimit())
    {
        int m = matrix.getRowNumber();
        for (int i = 0; i < m - 1; ++i)
        {
            printf("%d ", minIndexForRow[i]);
        }
        printf("%d", minIndexForRow[m - 1]);
    }
    return 0;
}