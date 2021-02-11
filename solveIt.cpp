/*  
    Advanced Algorithms I - Divide and Conqueer

    Solve It: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1282
*/

#include <iostream>
#include <math.h>
#include <cmath>
#define e 2.718281828459 // Euler number
const double ERROR = 0.00000001;

using namespace std;

// Value of formula using giving x
double formula(double x, int p, int q, int r, int s, int t, int u)
{
    return (p * pow(e, -x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u);
}

// Gets X value
double bisection(double hi, double lo, int p, int q, int r, int s, int t, int u)
{
    double mid, x;

    do
    {
        mid = (hi - lo) / 2 + lo;
        x = formula(mid, p, q, r, s, t, u);

        if (x < 0)
            hi = mid;
        else
            lo = mid;

    } while (abs(x) > ERROR);

    return mid;
}

int main()
{
    int p, q, r, s, t, u; // Equation parameters

    while (cin >> p)
    {
        cin >> q >> r >> s >> t >> u;

        // Check value on extremes
        double min = formula(0, p, q, r, s, t, u);
        double max = formula(1, p, q, r, s, t, u);

        // Check if solution exists
        if ((min >= 0 && max <= 0) || (min <= 0 && max >= 0))
            printf("%0.4f\n", bisection(1, 0, p, q, r, s, t, u));
        else
            cout << "No solution" << endl;
    }
    return 0;
}