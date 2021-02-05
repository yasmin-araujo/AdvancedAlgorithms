/*  
    Advanced Algorithms I - Divide and Conquer

    Counting number of inversions
*/

#include <iostream>

using namespace std;

// Merge two sorted halfs into one and count number of inversions
int mergeHalfs(int *nums, int firstHalf, int secondHalf, int end)
{
    int s1 = secondHalf - firstHalf; // Size of first half array
    int s2 = end - secondHalf + 1;   // Size of second half array
    int tempFirst[s1];               // Temp array to keep first half values
    int tempSecnd[s2];               // Temp array to keep second half values
    int f = 0;                       // Pointer to index of first array
    int s = 0;                       // Pointer to index of second array
    int i = firstHalf;               // Pointer to index of final array
    int cnt = 0;                     // Number of elements from second half added
    int inversions = 0;              // Number of inversions

    // Copy data to temp arrays
    for (int i = 0; i < s1; i++)
        tempFirst[i] = nums[firstHalf + i];
    for (int i = 0; i < s2; i++)
        tempSecnd[i] = nums[secondHalf + i];

    // Merge temp arrays at nums
    while (f < s1 && s < s2)
    {
        if (tempFirst[f] <= tempSecnd[s])
        {
            nums[i] = tempFirst[f];
            f++;
            inversions += cnt;
        }
        else
        {
            nums[i] = tempSecnd[s];
            s++;
            cnt++;
        }
        i++;
    }

    // Copy remaining elements of temp arrays if any
    while (f < s1)
    {
        nums[i] = tempFirst[f];
        inversions += cnt;
        f++;
        i++;
    }
    while (s < s2)
    {
        nums[i] = tempSecnd[s];
        s++;
        i++;
    }

    return inversions;
}

// Count inversions recursively by sorting the array and counting
int countInversions(int *nums, int left, int right)
{
    // List has 1 or 0 elements
    if (right - left <= 0)
        return 0;

    int mid = (right - left) / 2 + left;
    int counter = 0;

    counter += countInversions(nums, left, mid);
    counter += countInversions(nums, mid + 1, right);
    counter += mergeHalfs(nums, left, mid + 1, right);

    return counter;
}

int main()
{
    int N; // Number of test cases
    int C; // Number of elements in each test case
    int numberOfInversions;

    cin >> N;

    while (N--)
    {
        cin >> C;
        int nums[C];

        for (int i = 0; i < C; i++)
            cin >> nums[i];

        numberOfInversions = countInversions(nums, 0, C - 1);

        cout << numberOfInversions << endl;
    }

    return 0;
}