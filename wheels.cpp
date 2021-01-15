/*  
    Advanced Algorithms I - Backtracking - A* Algorithm

    Playing with wheels: https://
*/

#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

#define MAX 4        // Max number of digits
#define NUM_STATES 8 // Max number of different next states

// Struct for each state
struct state
{
    int distance;
    int digit[MAX];
    int depth;
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

// Possible moves for next state
int moves[NUM_STATES][MAX] = {{-1, 0, 0, 0},
                              {1, 0, 0, 0},
                              {0, -1, 0, 0},
                              {0, 1, 0, 0},
                              {0, 0, -1, 0},
                              {0, 0, 1, 0},
                              {0, 0, 0, -1},
                              {0, 0, 0, 1}};

// Get string version of integer array
string toString(int forbidden[][MAX], int n)
{
    string res = "";
    for (int i = 0; i < MAX; i++)
        res += forbidden[n][i] + '0';

    return res;
}

// Get string version of integer array
string toString(state s)
{
    string res = "";
    for (int i = 0; i < MAX; i++)
        res += s.digit[i] + '0';

    return res;
}

// Calculate distance value from state to target
int getDistance(state s, state target)
{
    int d = 0;
    for (int i = 0; i < MAX; i++)
        d += min(abs(s.digit[i] - target.digit[i]), 10 - max(s.digit[i], target.digit[i]) + min(s.digit[i], target.digit[i]));
    return d + s.depth;
}

// Find all possible next states
void findNextStates(state s, state nextStates[NUM_STATES], state target)
{
    for (int i = 0; i < NUM_STATES; i++)
    {
        nextStates[i].depth = s.depth + 1;
        for (int j = 0; j < MAX; j++)
        {
            nextStates[i].digit[j] = (s.digit[j] + moves[i][j]) % 10;
            if (nextStates[i].digit[j] < 0)
                nextStates[i].digit[j] += 10;
        }
        nextStates[i].distance = getDistance(nextStates[i], target);
    }
}


int bfs(state initial, unordered_map<string, int> &visited, state target)
{
    priority_queue<state, vector<state>, sortDistance> queue;

    // Insert first element on queue
    queue.push(initial);

    while (!queue.empty())
    {
        // Get first element from queue
        state current = queue.top();
        queue.pop();

        // Check if it's not a forbidden or already visited number
        if (visited.count(toString(current)) == 0)
        {
            // Mark as visited
            visited[toString(current)] = 1;

            // Return if target found
            if (toString(current) == toString(target))
                return current.depth;

            // Get new states
            state nextStates[NUM_STATES];
            findNextStates(current, nextStates, target);

            // Insert next states on queue
            for (int i = 0; i < NUM_STATES; i++)
                queue.push(nextStates[i]);
        }
    }

    // No target found
    return -1;
}

int main()
{
    int N;         // Number of test cases
    state initial; // Initial configuration
    state target;  // Target configuration
    int n;         // Number of forbidden configurations
    unordered_map<string, int> visited; // Hashmap to mark visited/forbidden states

    cin >> N;

    // For each test case
    while (N--)
    {
        visited.clear();

        // Input reading
        for (int i = 0; i < MAX; i++)
            cin >> initial.digit[i];
        initial.depth = 0;

        for (int i = 0; i < MAX; i++)
            cin >> target.digit[i];
        initial.distance = getDistance(initial, target);

        cin >> n;
        int forbidden[n][MAX];

        while (n--)
        {
            for (int i = 0; i < MAX; i++)
                cin >> forbidden[n][i];

            // Mark all forbidden numbers as visited
            string number = toString(forbidden, n);
            visited[number] = 1;
        }

        int answer = bfs(initial, visited, target);
        cout << answer << endl;
    }

    return 0;
}