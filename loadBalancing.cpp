/*  
    Advanced Algorithms I - Greedy Algorithms

    Load Balancing Problem
    Station Balance: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=351
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int c;     // Number of chambers
    int s;     // Number of species
    int x = 0; // Set number

    while (cin >> c)
    {
        int sum = 0;
        float mean = 0;
        float imbalance = 0;

        x++;
        cin >> s;

        vector<int> masses(2 * c, 0); // Mass of each species

        for (int i = 0; i < s; i++)
        {
            int new_mass;
            cin >> new_mass;
            masses[i] = new_mass;
            sum += new_mass;
        }

        sort(masses.begin(), masses.end());
        mean = (float)sum / (float)c;

        cout << "Set #" << x << endl;

        // For each chamber
        for (int i = 0; i < c; i++)
        {
            int firstNum = masses[i];
            int secondNum = masses[masses.size() - i - 1];

            // Print numbers if they are not 0
            cout << i << ": ";
            if (firstNum)
                cout << firstNum << " ";
            if (secondNum)
                cout << secondNum;
            cout << endl;

            imbalance += abs((firstNum + secondNum) - mean);
        }

        cout << setprecision(5) << fixed;
        cout << "IMBALANCE = " << imbalance << endl << endl;
    }
    return 0;
}