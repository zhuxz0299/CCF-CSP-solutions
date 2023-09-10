#include <bits/stdc++.h>
using namespace std;

struct node
{
    int time, finish_time; // time 表示完成这个科目的时间，finish_time 表示完成这个任务加上后面所有任务的时间
    int start_time = 1;    // 最早的开始的时间
    node *depend = nullptr;
};

int main()
{
    int n, m;
    int pre, time;
    bool pass = true; // 表示是否能完成所有科目，如果能，pass为true
    node sub[105];
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &pre);
        if (pre != 0)
            sub[i].depend = &sub[pre];
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &time);
        sub[i].time = time;
        if (sub[i].depend) // 更新start_time
            sub[i].start_time = sub[i].depend->start_time + sub[i].depend->time;

        sub[i].finish_time = time; // 初始化finish_time
    }
    for (int i = m; i >= 1; i--)                                                       // 更新 finish_time
        if (sub[i].depend && pass)                                                     // 如果某个结点有父节点而且有必要计算
            if (sub[i].depend->finish_time < sub[i].depend->time + sub[i].finish_time) // 如果这条线路是最慢的
            {
                sub[i].depend->finish_time = sub[i].depend->time + sub[i].finish_time; // 更新
                if (sub[i].depend->finish_time > n)                                    // 超过总时间了
                    pass = false;
            }
    for (int i = 1; i <= m; i++)
        printf("%d ", sub[i].start_time);
    printf("\n");
    if (pass)
        for (int i = 1; i <= m; i++)
            printf("%d ", n - sub[i].finish_time + 1);
    printf("\n");

    // for (int i = 1; i <= m; i++)
    //     printf("DEBUG: sub[%d].time=%d, sub[%d].start_time=%d\n", i, sub[i].time, i, sub[i].start_time);
}