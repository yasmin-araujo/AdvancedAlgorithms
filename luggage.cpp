/*  
    Advanced Algorithms I - Dynamic Programming

    Luggage: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1605
*/

#include <iostream>
#include <vector>

using namespace std;

// Function to organize bags with equal weight
bool helper(int space, vector<int> weights, int index, vector<vector<bool>> &memo)
{
    // Invalid move
    if (space < 0)
        return false;

    // Means the bag is full
    if (space == 0)
        return true;

    // Means there are no more items available and there is still space on the bag
    if (index >= (int)weights.size())
        return false;

    memo[space][index] = helper(space - weights[index], weights, index + 1, memo) || helper(space, weights, index + 1, memo);

    return memo[space][index];
}

int main()
{
    vector<int> weights; // Array of all weights
    int n;               // Number of test cases
    scanf("%d", &n);

    while (n--)
    {
        weights.clear();
        char temp = '\n'; // Temporary variable to stop reading
        int nextWeight;   // Next wheight to be readed
        int sum = 0;      // Sum of all weights

        // Read input until end of line
        do
        {
            scanf("%d", &nextWeight);
            weights.push_back(nextWeight);
            sum += nextWeight;

        } while (scanf("%c", &temp) != EOF && temp != '\n');

        // It's impossible if sum is odd
        if (sum % 2 == 1)
        {
            cout << "NO" << endl;
            continue;
        }

        vector<vector<bool>> memo((sum / 2) + 1, vector<bool>(weights.size(), false)); // Matrix for memoization

        if (helper(sum / 2, weights, 0, memo))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}