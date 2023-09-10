#include <bits/stdc++.h>
#include <vector>
using namespace std;

int main()
{
    int n, d;
    scanf("%d%d", &n, &d);

    vector<vector<int>> Q(n, vector<int>(d));
    vector<vector<int>> K(n, vector<int>(d));
    vector<vector<int>> V(n, vector<int>(d));
    vector<int> W(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            scanf("%d", &Q[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            scanf("%d", &K[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            scanf("%d", &V[i][j]);
    for (int i = 0; i < n; i++)
        scanf("%d", &W[i]);

    vector<vector<long long>> res(n, vector<long long>(d));
    vector<vector<long long>> tmp_small(d, vector<long long>(d));

    // Q = W · Q
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            Q[i][j] *= W[i];

    // KT × V
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            for (int k = 0; k < n; k++)
                tmp_small[i][j] += K[k][i] * V[k][j];

    // Q × (KT × V)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            for (int k = 0; k < d; k++)
                res[i][j] += Q[i][k] * tmp_small[k][j];

    // 输出结果
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            printf("%lld%c", res[i][j], j == d - 1 ? '\n' : ' ');
}