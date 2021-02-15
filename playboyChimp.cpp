/*  
    Advanced Algorithms I - Divide and Conqueer

    The Playboy Chimp: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=593
*/

#include <iostream>

using namespace std;

void binarySearch(int q, int *h, int lo, int hi, int &taller, int &smaller)
{
    int mid;
    int N = hi + 1;

    while (lo < hi)
    {
        mid = (hi - lo) / 2 + lo;
        if (h[mid] == q)
            break;
        else if (h[mid] > q)
            hi = mid;
        else
            lo = mid + 1;
    }

    // If found same height as his - jump to next different values
    if (h[mid] == q)
    {
        int i = mid;

        do
        {
            // Check if next element boundaries
            taller = i + 1 < N ? h[i + 1] : -1;
            i++;

        } while (taller == q);

        i = mid;
        do
        {
            smaller = i - 1 >= 0 ? h[i - 1] : -1;
            i--;

        } while (smaller == q);
    }
    else if (h[hi] < q) // If found is smaller -> last element from list
    {
        smaller = h[hi];
    }
    else
    {
        taller = h[hi];
        smaller = mid - 1 >= 0 ? h[hi - 1] : -1;
    }
}

int main()
{
    int N; // Number of lady chimps on the line
    int Q; // Number of queries;
    int q; // Luchu height

    cin >> N;

    int h[N]; // Heights of the lady chimps

    for (int i = 0; i < N; i++)
        cin >> h[i];

    cin >> Q;

    // For each different height
    while (Q--)
    {
        cin >> q;

        int taller = -1;
        int smaller = -1;

        // Search
        binarySearch(q, h, 0, N - 1, taller, smaller);

        // Print results
        if (smaller > 0)
            cout << smaller << " ";
        else
            cout << "X ";
        if (taller > 0)
            cout << taller << endl;
        else
            cout << "X" << endl;
    }

    return 0;
}