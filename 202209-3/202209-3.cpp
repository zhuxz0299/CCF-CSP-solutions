#include <bits/stdc++.h>
using namespace std;

struct region
{
    int id = 0, date = -10; // id 为地区的编号，date 为最近的成为风险地区的日期
};

struct user
{
    int id = 0, date = -10; // id 为人员编号，date 为到的高风险区域刚刚有风险的日期(取最近的)
};

region re[7000 + 2]; // 由于一个高风险周期为7天，每天最多1000条信息，因此最多考虑7000个地区。对于7天内一个地区重复成为高风险的情形，重新存一个re就行，原来的那个就先放着，不影响对于有风险的用户的判断。
user usr[7000 + 2];

int main()
{
    int n;          // n 为总天数
    int r_num, m;   // r 为某日接收到的风险地区的数量，m 为某日接收到的漫游数据的数量
    int p, d, u, r; // p：刚有风险的地区id，d：漫游信息产生的日期，u：用户id，r：地区id
    scanf("%d", &n);
    for (int i = 0; i < n; i++) // 假设现在是第 i 天
    {
        scanf("%d %d", &r_num, &m);
        int pointer = 0;                // 用于遍历地区数组
        for (int j = 0; j < r_num; j++) // 输入风险地区
        {
            scanf("%d", &p);
            while (re[pointer].id != 0 && i - re[pointer].date < 7) // 假如一个地区元素还没有被用过，或者这个地区按照日期已经不是高风险了，那么这个地区元素可以被使用
                pointer++;
            re[pointer].id = p, re[pointer].date = i;
        }
        pointer = 0; // 还可以用来遍历人员数组
        for (int j = 0; j < m; j++)
        {
            scanf("%d %d %d", &d, &u, &r);
            if (i - d >= 7 || d < 0) // 7天之前的数据不用管，时间在0之前的也不用管，因为在之前也不知道有没有高风险地区
                continue;
            while (usr[pointer].id != 0 && i - re[pointer].date < 7) // 假如一个人员元素还没被用过，或者这个人员按照日期已经不是高风险了，这个人员元素可以被使用
                pointer++;
            for (int k = 0; k < 7000; k++) // 先找一下自己看看在不在上面
                if (usr[k].id == u)
                    pointer = k;
            for (int k = 0; k < 7000; k++) // 遍历所有的地区，看看有没有该人员到访过的
            {
                if (r == re[k].id && i - re[k].date < 7 && d >= re[k].date) // 如果到访过，而且这个地区在到访时为高风险，而且这个地区到现在依然是高风险，那么该人员成为高风险
                {
                    usr[pointer].id = u;                                    // 记录下这个人员
                    usr[pointer].date = max(usr[pointer].date, re[k].date); // 某个地区可能多次成为高风险地区，记录最近的那次时间
                }
            }
        }
        // 以下输出第i天的高风险人员
        printf("%d ", i);
        for (int j = 0; j < 7000; j++)
            if (usr[j].id != 0 && i - usr[j].date < 7)
                printf("%d ", usr[j].id);
        printf("\n");
    }
}