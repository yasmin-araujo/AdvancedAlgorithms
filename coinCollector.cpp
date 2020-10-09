/*  
    Advanced Algorithms I - Greedy Algorithms

    Coin Collector: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2231
*/

#include <iostream>

using namespace std;

int main()
{
    int t; // Number of test cases
    cin >> t;

    while (t--)
    {
        int n; // Number of different types of coins
        cin >> n;

        int *coinValues = new int[n];

        // Read coin values
        for (int i = 0; i < n; i++)
        {
            cin >> coinValues[i];
        }

        int sum = coinValues[0];
        int coins = 1; // Maximum number of coins that can be collected

        for (int i = 1; i < n - 1; i++)
        {
            if (coinValues[i] + sum < coinValues[i + 1])
            {
                sum += coinValues[i];
                coins++;
            }
        }

        // Add last coin
        coins++;

        cout << coins << endl;
    }

    return 0;
}