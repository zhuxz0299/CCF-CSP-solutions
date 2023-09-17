#include <bits/stdc++.h>
using namespace std;

struct role_attr
{
    set<string> oprt;          // 操作类型
    set<string> resource_cate; // 资源种类
    set<string> resource_name; // 资源名称
};

map<string, role_attr> role;   // 角色，key为名称，value为属性
map<string, set<string>> user; // 用户，key为名称，value为绑定的角色名称的集合

bool have_access(string user_name, string oprt, string resource_cate, string resource_name);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, q;
    cin >> n >> m >> q;

    int nv, no, nn;
    string name, oprt, resource_cate, resource_name;
    for (int i = 0; i < n; ++i) // 输入角色信息
    {
        cin >> name; // 输入角色名
        // 接下来给角色各种属性
        cin >> nv;
        for (int j = 0; j < nv; ++j)
        {
            cin >> oprt;
            role[name].oprt.insert(oprt);
        }
        cin >> no;
        for (int j = 0; j < no; ++j)
        {
            cin >> resource_cate;
            role[name].resource_cate.insert(resource_cate);
        }
        cin >> nn;
        for (int j = 0; j < nn; ++j)
        {
            cin >> resource_name;
            role[name].resource_name.insert(resource_name);
        }
    }

    int ns;
    string role_name, user_name;
    for (int i = 0; i < m; ++i) // 进行角色关联
    {
        cin >> role_name;
        cin >> ns;
        for (int j = 0; j < ns; ++j)
        {
            cin >> user_name;                  // 用户类型直接忽略
            cin >> user_name;                  // 输入用户姓名
            user[user_name].insert(role_name); // 将角色名与用户名关联
        }
    }

    int ng;
    for (int i = 0; i < q; ++i)
    {
        bool authorized = false; // 某个用户是否被授权了某种行为
        queue<string> user_list;

        cin >> user_name;
        user_list.push(user_name);
        cin >> ng;
        for (int j = 0; j < ng; ++j)
        {
            cin >> user_name;
            user_list.push(user_name);
        }
        cin >> oprt >> resource_cate >> resource_name;
        while (!user_list.empty())
        {
            if (have_access(user_list.front(), oprt, resource_cate, resource_name))
            {
                authorized = true;
                break;
            }
            user_list.pop();
        }
        if (authorized)
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
}

bool have_access(string user_name, string oprt, string resource_cate, string resource_name)
{
    for (string role_name : user[user_name])
    {
        if (role[role_name].oprt.count(oprt) || role[role_name].oprt.count("*"))
            if (role[role_name].resource_cate.count(resource_cate) || role[role_name].resource_cate.count("*"))
                if (role[role_name].resource_name.count(resource_name) || role[role_name].resource_name.empty())
                    return true;
    }
    return false;
}