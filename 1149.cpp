#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Matchstick cost for each digit (0-9)
int costForDigit[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

// Recursively generate all numbers that use exactly 'rem' matches.
// 'started' indicates whether we have placed a nonzero digit already (to avoid leading zeros).
// 'cur' is the current number being built.
void gen(int rem, long long cur, bool started, vector<long long> &vec)
{
    if (rem == 0)
    {
        if (started)
            vec.push_back(cur);
        return;
    }
    if (!started)
    {
        // Special: we can only represent 0 if exactly costForDigit[0] matches remain.
        if (rem == costForDigit[0])
            vec.push_back(0);
        // For a nonzero number, the first digit must be 1..9.
        for (int d = 1; d <= 9; d++)
        {
            if (rem >= costForDigit[d])
                gen(rem - costForDigit[d], d, true, vec);
        }
    }
    else
    {
        // Once started, we can use any digit 0..9.
        for (int d = 0; d <= 9; d++)
        {
            if (rem >= costForDigit[d])
                gen(rem - costForDigit[d], cur * 10 + d, true, vec);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // If there are fewer than 4 matches then we cannot even form the '+' and '='.
    if (n < 4)
    {
        cout << 0;
        return 0;
    }

    int digitTotal = n - 4; // Total matches available for digits

    // validNumbers[c] will store all numbers that can be formed with exactly c matches.
    vector<vector<long long>> validNumbers(digitTotal + 1);
    for (int cost = 1; cost <= digitTotal; cost++)
    {
        gen(cost, 0, false, validNumbers[cost]);
    }

    // For quick membership check we also build an unordered_set for each cost value.
    vector<unordered_set<long long>> validSet(digitTotal + 1);
    for (int i = 1; i <= digitTotal; i++)
    {
        for (auto num : validNumbers[i])
            validSet[i].insert(num);
    }

    long long ans = 0;
    // Iterate over all ways to partition the digit matches: cA + cB + cC = digitTotal, with cA,cB,cC >= 1.
    for (int cA = 1; cA <= digitTotal; cA++)
    {
        for (int cB = 1; cA + cB <= digitTotal; cB++)
        {
            int cC = digitTotal - cA - cB;
            if (cC < 1)
                continue;
            for (auto A : validNumbers[cA])
            {
                for (auto B : validNumbers[cB])
                {
                    long long C = A + B;
                    // Check if C can be formed with exactly cC matches.
                    if (validSet[cC].count(C))
                    {
                        // Determine whether A, B, C are all positive (i.e. not 0).
                        bool allPositive = (A > 0 && B > 0 && C > 0);
                        if (allPositive)
                        {
                            // When all are positive, order matters: if A and B are different,
                            // the pair (A,B) and (B,A) are considered two distinct equations.
                            ans++;
                        }
                        else
                        {
                            // If any of the numbers is 0, then A+B=C and B+A=C are considered the same.
                            // To avoid double counting, count only if A <= B.
                            if (A <= B)
                                ans++;
                        }
                    }
                }
            }
        }
    }

    cout << ans;
    return 0;
}
