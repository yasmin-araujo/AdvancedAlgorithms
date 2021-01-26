/*  
    Advanced Algorithms I - Backtracking - A* Algorithm

    Eight Puzzle: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=593
*/

#include <iostream>
#include <unordered_map>
#include <queue>
#define TARGET "12345678x"

using namespace std;

// Struct for each state
struct state
{
    int distance;
    char board[3][3];
    int depth;
    string moves;
    pair<int, int> xPos;
};

// Struct with sorting rules
struct sortDistance
{
    bool operator()(state const &s1, state const &s2)
    {
        // return "true" if "s1" is ordered before "s2"
        return s1.distance > s2.distance;
    }
};

// Calculate number of inversions -> Number of tiles with lower number on the right
int numberOfInversions(char puzzle[3][3])
{
    int total = 0;

    for (int i = 0; i < 9; i++)
    {
        int sum = 0;
        for (int j = i + 1; j < 9; j++)
        {
            if (puzzle[i / 3][i % 3] == 'x')
                continue;

            if (puzzle[i / 3][i % 3] > puzzle[j / 3][j % 3])
                sum++;
        }
        total += sum;
    }

    return total;
}

// Because the grid width is odd, then the number of inversions in a solvable situation is even.
bool isSolvable(char puzzle[3][3])
{
    if (numberOfInversions(puzzle) % 2 == 0)
        return true;
    return false;
}

// Return puzzle values in format of string
string toString(state puzzle)
{
    string res = "";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            res += puzzle.board[i][j];
    return res;
}

int manhattanDistance(char num, int i, int j)
{
    if (num == 'x')
        return 0;

    int n = num - '0' - 1;

    // Where number should be
    int lin = n / 3;
    int col = n % 3;

    int sum = 0;
    sum += abs(lin - i);
    sum += abs(col - j);

    return sum;
}

// Get distance of each element with manhattan distance and return total
int getDistance(state s)
{
    int total = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            total += manhattanDistance(s.board[i][j], i, j);
    return total + s.depth;
}

// Copy puzzle to another state variable
void copyPuzzle(state initial, state &next)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            next.board[i][j] = initial.board[i][j];
}

// Create new state with passed parameters
void createState(state &initial, state &nextState, char move, int lin, int col, int addLin, int addCol)
{
    nextState.depth = initial.depth + 1;
    nextState.moves = initial.moves + move;
    nextState.xPos = {lin + addLin, col + addCol};
    copyPuzzle(initial, nextState);
    swap(nextState.board[lin][col], nextState.board[lin + addLin][col + addCol]);
    nextState.distance = getDistance(nextState);
}

// Find all possible next states
int findNextStates(state initial, state nextStates[4])
{
    int n = 0;
    int lin = initial.xPos.first;
    int col = initial.xPos.second;

    if (lin + 1 < 3) // down
    {
        createState(initial, nextStates[n], 'd', lin, col, 1, 0);
        n++;
    }
    if (lin - 1 >= 0) // up
    {
        createState(initial, nextStates[n], 'u', lin, col, -1, 0);
        n++;
    }
    if (col + 1 < 3) // right
    {
        createState(initial, nextStates[n], 'r', lin, col, 0, 1);
        n++;
    }
    if (col - 1 >= 0) // left
    {
        createState(initial, nextStates[n], 'l', lin, col, 0, -1);
        n++;
    }

    return n;
}

string bfs(state initial)
{
    priority_queue<state, vector<state>, sortDistance> queue;
    unordered_map<string, int> visited;

    // Insert first element on queue
    queue.push(initial);

    while (!queue.empty())
    {
        // Get first element from queue
        state current = queue.top();
        queue.pop();

        // Check if it's not an already visited state
        if (visited.count(toString(current)) == 0)
        {
            // Mark as visited
            visited[toString(current)] = 1;

            // Return if target found
            if (toString(current) == TARGET)
                return current.moves;

            // Get new states
            state nextStates[4];
            int numStates = findNextStates(current, nextStates);

            // Insert next states on queue
            for (int i = 0; i < numStates; i++)
                if (visited.count(toString(nextStates[i])) == 0)
                    queue.push(nextStates[i]);
        }
    }

    // No target found
    return "error";
}

int main()
{
    int N;         // Number of test cases
    state initial; // Initial puzzle state
    initial.depth = 0;

    cin >> N;

    while (N--)
    {
        // Read values for initial puzzle
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                cin >> initial.board[i][j];
                // Save x position
                if (initial.board[i][j] == 'x')
                    initial.xPos = {i, j};
            }

        // Check if it's solvable
        if (!isSolvable(initial.board))
            cout << "unsolvable" << endl;
        else
        {
            // Initialize distance
            initial.distance = getDistance(initial);

            // Find answer
            string answer = bfs(initial);
            cout << answer << endl;
        }

        // Add space if there is another test case
        if (N)
            cout << endl;
    }

    return 0;
}