#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    double interest, power = 1, profit = 0, earning;
    scanf("%d %lf", &n, &interest);
    // printf("DEBUG: n=%d, interest=%lf\n", n, interest);
    for (int i = 0; i < n + 1; i++)
    {
        scanf("%lf", &earning);
        profit += earning * power;
        // printf("DEBUG: earning=%lf, power=%lf, profit=%lf\n", earning, power, profit);
        power /= (1 + interest);
    }
    printf("%.3lf", profit);
}