#include <bits/stdc++.h>
using namespace std;

int a[1000];

int main(int argc, char const *argv[])
{
    int n, sum = 0;
    scanf("%d", &n);
    double avg, var = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    avg = double(sum) / n;
    for (int i = 0; i < n; ++i)
        var += (a[i] - avg) * (a[i] - avg);
    var /= n;
    for (int i = 0; i < n; ++i)
        printf("%f\n", (a[i] - avg) / sqrt(var));
    return 0;
}
