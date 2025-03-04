#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p;
    cin >> n >> m >> p;

    // Read matrix A (n x m)
    vector<vector<int>> A(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> A[i][j];

    // Read matrix B (m x p)
    vector<vector<int>> B(m, vector<int>(p));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < p; ++j)
            cin >> B[i][j];

    // Compute matrix multiplication C = A * B, where C is (n x p)
    vector<vector<long long>> C(n, vector<long long>(p, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < p; ++j)
        {
            for (int k = 0; k < m; ++k)
            {
                C[i][j] += static_cast<long long>(A[i][k]) * B[k][j];
            }
        }
    }

    // Output the result matrix C
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < p; ++j)
        {
            cout << C[i][j] << (j == p - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
