#include <bits/stdc++.h>
using namespace std;

int main()
{
    string chess[100][8];
    int count[100];
    int n;
    bool flag = true;

    scanf("%d", &n);
    cin.get();
    for (int i = 0; i < n; i++)
    {
        count[i] = 1;
        for (int j = 0; j < 8; j++)
            getline(cin, chess[i][j]);
        for (int k = i - 1; k >= 0; k--) // 检查之前的所有棋盘
        {
            flag = true;
            for (int j = 0; j < 8; j++) // 检查每个棋盘的某一行是否相同
                if (chess[i][j] != chess[k][j])
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