#include <bits/stdc++.h>
using namespace std;

int cost[32][300002] = {0}; // 所有元素设为0

int drop(int a[], int n, int exc)
{

    if (cost[n][exc] == 0 && n > 0)
        if (exc >= a[n])
            cost[n][exc] = max(drop(a, n - 1, exc), drop(a, n - 1, exc - a[n]) + a[n]);
        else
            cost[n][exc] = drop(a, n - 1, exc);
    // printf("DEBUG: cost[%d][%d]=%d\n", n, exc, cost[n][exc]);
    return cost[n][exc];
}

int main()
{
    int n, x;    // n 为挑选的书的数量，x为包邮最低价
    int a[35];   // a[i] 为第 i 本书的价格
    int sum = 0; // 用于记录书的总价
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    int excessive = sum - x;
    // printf("DEBUG: sum=%d, x=%d, excessive=%d\n", sum, x, excessive);
    printf("%d", sum - drop(a, n, excessive));
}

// 94 9 7 66 12 21 58 89 57 60
// 9537 3116 4327 6056 1277 2460 7768 1701 5522 4305 5892 644 8388 6259 5563 9934 8421 7538 3547 624 9580 3439 3176 4602 4126 3139 4267 4156 6123 7634