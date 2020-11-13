/*  
    Advanced Algorithms I - BackTracking

    Rat in a Maze: https://www.codechef.com/problems/BPHC03
*/

#include <iostream>
#include <vector>

using namespace std;

int backtracking(int n, vector<vector<int>> maze, int i, int j)
{
    // Out of borders
    if (i >= n || i < 0 || j >= n || j < 0) 
        return 0;

    // Blocked or already used cell
    if (maze[i][j] != 0)
        return 0;

    // Found cheese
    if (i == n - 1 && j == n - 1)
        return 1;

    // Mark as visited
    maze[i][j] = 2;

    int paths = 0;

    // Count number of paths for each direction
    paths += backtracking(n, maze, i + 1, j);
    paths += backtracking(n, maze, i - 1, j);
    paths += backtracking(n, maze, i, j + 1);
    paths += backtracking(n, maze, i, j - 1);

    return paths;
}

int main()
{
    int n; // Number of lines
    cin >> n;

    vector<vector<int>> maze(n, vector<int>(n, 0));

    // Input read
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> maze[i][j];
    }

    // Count number of possible paths
    int paths = backtracking(n, maze, 0, 0);

    cout << paths << endl;

    return 0;
}