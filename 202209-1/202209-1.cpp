#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;                      // n 为题目的数量，m 为加密后的数字
    int a[25], b[25], c[25] = {1}; // a[i] 为第 i 道题的选项数量
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &(a[i]));
        c[i] = c[i - 1] * a[i];
    }

    for (int i = n; i > 0; i--)
    {
        b[i] = m / c[i - 1];
        m %= c[i - 1];
    }

    for (int i = 1; i <= n; i++)
        printf("%d ", b[i]);
}