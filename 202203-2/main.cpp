#include <bits/stdc++.h>
using namespace std;

int num_satisfied[200000] = {0};

int main()
{
    int n, m, k; // k为得到核酸结果需要的时间
    scanf("%d %d %d", &n, &m, &k);

    int t, c;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &t, &c);
        // 在时间t-k-c+1和t-k之间做核酸检测是有效的
        for (int j = max(0, t - k - c + 1); j <= t - k; j++)
            num_satisfied[j]++;
    }

    int q;
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &q);
        printf("%d\n", num_satisfied[q]);
    }
}