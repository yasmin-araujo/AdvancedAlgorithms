/*  
    Advanced Algorithms I - Dynamic Programing

    Coins Change: Minimum number of coins needed
*/

#include <iostream>
#include <vector>

using namespace std;

int numCoins(int value, vector<int> &coins, vector<int> &memo)
{
    if (value == 0)
        return 0;

    // If number of coins was already calculated for this value
    if (memo[value] != -1)
        return memo[value];

    int minNumberCoins = __INT_MAX__;

    // Try this value for each different coin and get smaller number
    for (int i = 0; i < (int)coins.size(); i++)
    {
        if (value - coins[i] >= 0)
        {
            int num = numCoins(value - coins[i], coins, memo);
            minNumberCoins = num == __INT_MAX__ ? minNumberCoins : min(num + 1, minNumberCoins);
        }
    }

    // Store number
    memo[value] = minNumberCoins;

    return minNumberCoins;
}

int main()
{
    int N; // Number of test cases
    int value;
    int coinsNumber; // Number of different coins
    vector<int> coins;

    cin >> N;

    while (N--)
    {
        cin >> value >> coinsNumber;
        vector<int> memo(value + 1, -1);

        coins.clear();
        for (int i = 0; i < coinsNumber; i++)
        {
            int val;
            cin >> val;
            coins.push_back(val);
        }

        int answer = numCoins(value, coins, memo);

        if (answer == __INT_MAX__)
            cout << "No Solution" << endl;
        else
            cout << answer << endl;
    }

    return 0;
}