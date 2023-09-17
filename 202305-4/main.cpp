#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M, K;
    int x, y, cost; // 定义输入时两个点，还有两个变电站之间的开销
    scanf("%d %d %d", &N, &M, &K);

    map<pair<int, int>, vector<vector<int>>> cost_matrix;
    vector<vector<int>> building_cost(N, vector<int>(K, 0));

    for (int i = 0; i < N; i++) // 在某座城市某个地址建厂的价格
        for (int j = 0; j < K; j++)
            scanf("%d", &(building_cost[i][j]));

    for (int i = 0; i < M; i++) // 两座城市之间的线路价格
    {
        scanf("%d %d", &x, &y);
        pair<int, int> town_pair(x, y);
        vector<vector<int>> cost(K, vector<int>(K, 0));
        for (int j = 0; j < K; j++)
            for (int k = 0; k < K; k++)
                scanf("%d", &(cost[j][k]));
        cost_matrix[town_pair] = cost;
    }
    // TODO unfinished
}