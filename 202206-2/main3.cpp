#include <bits/stdc++.h>
using namespace std;

const long long base = 1000000000;
struct point
{
    int x, y;
};

point tree[1000];
set<long long> tree_to_num;
int treasure[50][50];

bool have_tree(long long num_compare, int n);
bool is_possible_point(int x, int y, int n, int S);

int main()
{
    int n, L, S;
    scanf("%d %d %d", &n, &L, &S);
    int possible_point = 0;     // 可能的藏宝的地点的数量
    for (int i = 0; i < n; ++i) // 读取绿化图中所有的树
    {
        scanf("%d %d", &(tree[i].x), &(tree[i].y));
        tree_to_num.insert(tree[i].x * base + tree[i].y);
    }

    for (int i = 0; i <= S; ++i) // 读取藏宝图
        for (int j = 0; j <= S; ++j)
            scanf("%d", &(treasure[S - i][j]));

    for (int i = 0; i < n; ++i)
    {
        if (tree[i].x + S > L || tree[i].y + S > L) // 不能超出边界
            continue;
        if (is_possible_point(tree[i].x, tree[i].y, n, S))
            ++possible_point;
    }

    printf("%d\n", possible_point);

    return 0;
}

bool is_possible_point(int x, int y, int S) // 判断x，y这个点是不是可能的藏宝点
{
    long long num_compare;
    for (int i = 0; i <= S; ++i)
        for (int j = 0; j <= S; ++j)
        {
            num_compare = (x + i) * base + (y + j);
            if (treasure[i][j] && tree_to_num.count(num_compare) == 0)
                return false;
            if (!treasure[i][j] && tree_to_num.count(num_compare))
                return false;
        }
    return true;
}