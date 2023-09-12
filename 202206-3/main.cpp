#include <bits/stdc++.h>
using namespace std;

struct role
{
    char name[10];               // 角色名称
    int nv = 0;                  // 角色有的操作数量
    char oprt[400][10];          // 操作的名称
    int no = 0;                  // 资源种类的数量
    char resource_cate[400][10]; // 资源种类的名称
    int nn = 0;                  // 资源名称的数量
    char resource_name[400][10]; // 资源名称
};

struct role_relate
{
    char role_name[10];      // 角色名称
    int ns;                  // 授权对象的数量
    char cha[400];           // 表示应该是用户还是用户组，取值为u或者g
    char user_name[400][10]; // 用户或者用户组名称
};

struct user
{
    char name[10];
};

role r[500];
role_relate item[500];

int main()
{
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i < n; ++i)
    {
        scanf("%s", r[i].name);
        scanf("%d", &(r[i].nv));
        for (int j = 0; j < r[i].nv; ++j)
            scanf("%s", r[i].oprt[j]);
        scanf("%d", &(r[i].no));
        for (int j = 0; j < r[i].no; ++j)
            scanf("%s", r[i].resource_cate[j]);
        scanf("%d", &(r[i].nn));
        for (int j = 0; j < r[i].nn; ++j)
            scanf("%s", r[i].resource_name[j]);
    }

    for (int i = 0; i < m; ++i)
    {
        scanf("%s", item[i].role_name);
        scanf("%d", &(item[i].ns));
        for (int j = 0; j < item[i].ns; ++j)
            scanf("%c %s", &(item[i].cha), item[i].user_name);
    }

    for (int i = 0; i < q; ++i)
    {
    }
}