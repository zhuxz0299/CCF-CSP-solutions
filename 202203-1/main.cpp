#include <bits/stdc++.h>
using namespace std;

bool assigned[100005] = {false};

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int left, right;
    int count = 0; // 记录右值未被初始化的次数

    assigned[0] = true; // 已知量
    for (int i = 0; i < k; i++)
    {
        scanf("%d %d", &left, &right);
        if (!assigned[right])
            count++;
        assigned[left] = true;
    }

    printf("%d\n", count);
}