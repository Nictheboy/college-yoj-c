#include <iostream>
#include <string>
using namespace std;

// Recursive function to generate the "0,2表示" string for a positive integer n.
string represent(int n)
{
    // Find the highest power index k (i.e. floor(log2(n)))
    int k = 0;
    while ((1 << (k + 1)) <= n)
    {
        k++;
    }

    string result = "";
    bool first = true;
    // Loop from the highest bit down to 0
    for (int i = k; i >= 0; i--)
    {
        if (n & (1 << i))
        { // if the i-th bit is set
            string term;
            if (i == 0)
            {
                term = "2(0)";
            }
            else if (i == 1)
            {
                term = "2";
            }
            else
            {
                term = "2(" + represent(i) + ")";
            }
            if (!first)
            {
                result += "+";
            }
            result += term;
            first = false;
        }
    }
    return result;
}

int main()
{
    int n;
    cin >> n;
    cout << represent(n);
    return 0;
}
