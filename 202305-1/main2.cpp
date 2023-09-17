#include <bits/stdc++.h>
using namespace std;

int main()
{
    char chess[100][8][10];
    int count[100];
    int n;
    bool flag = true;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        count[i] = 1;
        for (int j = 0; j < 8; j++)
        {
            scanf("%s", chess[i][j]);
            // printf("%s", chess[i][j]);
        }
        for (int k = i - 1; k >= 0; k--) // 检查之前的所有棋盘
        {
            flag = true;
            for (int j = 0; j < 8; j++) // 检查每个棋盘的某一行是否相同
                // if (chess[i][j] != chess[k][j])
                if (strcmp(chess[i][j], chess[k][j]) != 0)
                {
                    flag = false;
                    break;
                }
            if (flag)
            {
                count[i] = count[k] + 1;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", count[i]);
}