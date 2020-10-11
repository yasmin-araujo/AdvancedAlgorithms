/*  
    Advanced Algorithms I - BackTracking

    CD Tracks: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=565
*/

#include <iostream>
#include <vector>

using namespace std;

void backtracking(int n, int &sum, vector<int> &tracks, vector<int> duration, int index)
{
    // If out of border
    if (index >= (int)duration.size())
        return;

    // If element + sum is equal to all the time available
    if (sum + duration[index] == n)
    {
        tracks.push_back(duration[index]);
        sum += duration[index];
        return;
    }

    // If it doesn't fit in the tape - don't add and jump to next
    if (sum + duration[index] > n)
    {
        backtracking(n, sum, tracks, duration, index + 1);
    }
    else
    {
        // Helper variables
        int sum1 = sum;
        int sum2 = sum;
        vector<int> newTrack1 = tracks;
        vector<int> newTrack2 = tracks;

        sum1 += duration[index];
        newTrack1.push_back(duration[index]);

        // Call recursive function including the element
        backtracking(n, sum1, newTrack1, duration, index + 1);

        // Call recursive function without the element
        if (sum1 != n)
            backtracking(n, sum2, newTrack2, duration, index + 1);

        // Add best values to the variables that will be returned
        tracks = sum1 > sum2 ? newTrack1 : newTrack2;
        sum = max(sum1, sum2);
    }

    return;
}

void printOutput(int sum, vector<int> tracks)
{
    for (int i = 0; i < (int)tracks.size(); i++)
        cout << tracks[i] << " ";
    cout << "sum:" << sum << endl;
}

int main()
{
    int n;                // Minutes available on the tape
    int num;              // Number of tracks;
    vector<int> duration; // Duration of each track
    vector<int> tracks;   // Tracks chosen to be on the tape
    int sum;              // Sum of time duration

    while (cin >> n)
    {
        duration.clear();

        // Input read
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            int d;
            cin >> d;
            duration.push_back(d);
        }

        sum = 0;
        tracks.clear();

        backtracking(n, sum, tracks, duration, 0);

        printOutput(sum, tracks);
    }

    return 0;
}