#include <bits/stdc++.h>
using namespace std;

set<pair<int, int>> trees;
int treasure[55][55];
bool is_possible_point(pair<int, int> tree, int S);

int main()
{
    int n, L, S;
    int x, y;
    scanf("%d %d %d", &n, &L, &S);
    int possible_point = 0;     // 可能的藏宝的地点的数量
    for (int i = 0; i < n; ++i) // 读取绿化图中所有的树
    {
        scanf("%d %d", &x, &y);
        trees.insert(make_pair(x, y));
    }

    for (int i = 0; i <= S; ++i) // 读取藏宝图
        for (int j = 0; j <= S; ++j)
            scanf("%d", &(treasure[S - i][j]));

    for (pair<int, int> tree : trees)
    {
        // printf("DEBUG: x=%d, y=%d\n", tree.first, tree.second);

        if (tree.first + S > L || tree.second + S > L) // 不能超出边界
            continue;
        if (is_possible_point(tree, S))
            possible_point++;
    }

    printf("%d\n", possible_point);

    return 0;
}

bool is_possible_point(pair<int, int> tree, int S)
{
    for (int i = 0; i <= S; i++)
        for (int j = 0; j <= S; j++)
            if (trees.count(make_pair(tree.first + i, tree.second + j)) ^ treasure[i][j]) // 这里没问题
                return false;
    return true;
}