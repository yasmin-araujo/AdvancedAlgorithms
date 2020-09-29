/*  
    Advanced Algorithms I - Stable Matching Problems

    Stable Marriage Problem: https://www.codechef.com/problems/STABLEMP
*/

#include <iostream>
#include <queue>

using namespace std;

// Function to read the preferences from the input and store in a matrix
void readPreferences(int n, int **prefs)
{
    for (int i = 0; i < n; i++)
    {
        // Reading value that isn't going to be used
        int index;
        cin >> index;

        prefs[i] = new int[n];

        // Read preferences values
        for (int j = 0; j < n; j++)
        {
            cin >> prefs[i][j];
            // Change to 0 based system
            prefs[i][j]--;
        }
    }
}

// Function to inverse the preferences values with the indexes
void inversePreference(int n, int **prefs)
{
    int *aux = new int[n];

    // For each woman
    for (int i = 0; i < n; i++)
    {
        // Fill auxiliar array with new positions
        for (int j = 0; j < n; j++)
            aux[prefs[i][j]] = j;

        // Move new value to matrix
        for (int j = 0; j < n; j++)
            prefs[i][j] = aux[j];
    }

    delete[] aux;
}

// Function to initialize arrays with -1 - everyone as singles
void inicialize(int *array, int n)
{
    for (int i = 0; i < n; i++)
        array[i] = -1;
}

// Function to find the first valid preference
int findFirstPreference(int n, int *prefs)
{
    // Search for the first greater than -1
    for (int i = 0; i < n; i++)
    {
        if (prefs[i] >= 0)
        {
            // Mark as already used preference and return it's value
            int answer = prefs[i];
            prefs[i] = -1;
            return answer;
        }
    }
    return -1;
}

// Function to print final result
void printPairs(int *array, int n)
{
    for (int i = 0; i < n; i++)
        cout << i + 1 << " " << array[i] + 1 << endl;
}

// Function to perform the stable matching
void stableMatching(int n, int **womanPrefs, int **manPrefs)
{
    // Arrays of current engagement status
    int *womanStatus = new int[n];
    int *manStatus = new int[n];

    // Initializing everyone as singles
    inicialize(womanStatus, n);
    inicialize(manStatus, n);

    // Queue for all single man to be processed
    queue<int> single;

    // Fill queue with all men
    for (int i = 0; i < n; i++)
        single.push(i);

    // While there are no single men to propose someone
    while (!single.empty())
    {
        // Get man from queue
        int man = single.front();

        // Find woman to be proposed depending on the preferences
        int woman = findFirstPreference(n, manPrefs[man]);

        // If no woman was found
        if (woman == -1)
        {
            // Remove man from the queue - he will stay single
            single.pop();
            continue;
        }

        // If she is single -> engage
        if (womanStatus[woman] == -1)
        {
            womanStatus[woman] = man;
            manStatus[man] = woman;
            single.pop();
        }
        else
        {
            // If she prefers the new to the old husband -> change
            if (womanPrefs[man] < womanPrefs[womanStatus[woman]])
            {
                // Add old husband back to the single queue
                single.push(womanStatus[woman]);
                // Upadte status and remove new man from queue
                womanStatus[woman] = man;
                manStatus[man] = woman;
                single.pop();
            }
        }
    }

    // Show results
    printPairs(manStatus, n);

    delete[] womanStatus;
    delete[] manStatus;
}

int main()
{
    int t; // Number of test cases
    int n; // Number of marriages to find

    cin >> t;

    // For each test case
    while (t--)
    {
        cin >> n;

        // Women and men preferences
        int **womanPrefs = new int *[n];
        int **manPrefs = new int *[n];

        readPreferences(n, womanPrefs);
        readPreferences(n, manPrefs);

        inversePreference(n, womanPrefs);

        stableMatching(n, womanPrefs, manPrefs);


        // Delete memory dinamically alocated
        for (int i = 0; i < n; i++)
        {
            delete[] womanPrefs[i];
            delete[] manPrefs[i];
        }

        delete[] womanPrefs;
        delete[] manPrefs;
    }

    return 0;
}