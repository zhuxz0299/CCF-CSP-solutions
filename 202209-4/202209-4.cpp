#include <bits/stdc++.h>
using namespace std;

int vote[100000 + 5] = {0}; // 记录每个选手的得票数

void canvass()
{
    int x, l, r;
    scanf("%d %d %d", &l, &r, &x);
    vote[x] += r - l;
    vote[0] -= r - l;
}

void transfer()
{
    int x, w;
    scanf("%d %d", &x, &w);
    vote[w] += vote[x];
    vote[x] = 0;
}

void exchange()
{
    int x, w;
    scanf("%d %d", &x, &w);
    int temp = vote[x];
    vote[x] = vote[w];
    vote[w] = temp;
}

void get_vote()
{
    int w;
    scanf("%d", &w);
    printf("%d\n", vote[w]);
}

void announce_champion(int n, int m)
{
    if (vote[0] == n)
        printf("%d\n", 0);
    else
    {
        int max = 0, cham = 0;
        for (int i = 1; i <= m; i++)
        {
            if (vote[i] > max)
            {
                max = vote[i];
                cham = i;
            }
        }
        printf("%d\n", cham);
    }
}

int main()
{
    int n, m, q;   // n 为投票者数量，m 为作品数量，q 为事件发生次数
    int event = 0; // 时间的种类
    scanf("%d %d %d", &n, &m, &q);
    vote[0] = n; // 初始化投票数，一开始大家都没有投票

    for (int i = 0; i < q; i++)
    {
        scanf("%d", &event);
        switch (event)
        {
        case 1:
            canvass();
            break;
        case 2:
            transfer();
            break;
        case 3:
            exchange();
            break;
        case 4:
            get_vote();
            break;
        case 5:
            announce_champion(n, m);
            break;
        default:
            break;
        }
    }
}