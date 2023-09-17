#include <bits/stdc++.h>
using namespace std;
// {
//     bool operator()(const task_node &node1, const task_node &node2)
//     {
//         if (node1.num_task != node2.num_task)
//             return node1.num_task < node2.num_task;
//         else
//             return node1.index < node2.index;
//     }
// };

map<int, int> node_to_area;             // 计算节点到可用区的对应
map<int, set<int>> area_to_node;        // 可用区到计算节点的对应
map<int, set<int>> application_to_area; // 某个应用在哪些可用区中
set<int> avail_area;                    // 包含计算节点的可用区
int num_task_node[1000] = {0};          // 表示一个计算节点中任务的数量

set<int> intersection(set<int> set1, set<int> set2);
set<int> exclude(set<int> set1, set<int> set2);
set<int> filter(int na, int pa, int paa, int paar);

int main()
{
    int n, m; // 计算节点数目、可用区的数目
    int g;    // 计算任务的组数
    int area; // 输入可用区时使用的变量
    int f, a, na, pa, paa, paar;
    int node_idx, min_tasks = 2000; // 选择的计算节点编号,min用于记录计算节点存储的最少任务数量

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &area);
        node_to_area[i] = area;
        area_to_node[area].insert(i);
        avail_area.insert(area);
    }

    scanf("%d", &g);
    for (int i = 0; i < g; i++)
    {
        scanf("%d %d %d %d %d %d", &f, &a, &na, &pa, &paa, &paar);
        for (int j = 0; j < f; j++)
        {
            set<int> fil_areas = filter(na, pa, paa, paar);

            // printf("DEBUG: ");
            // for (int area : fil_areas)
            //     printf("%d ", area);

            min_tasks = 2000, node_idx = 0;
            for (int area : fil_areas)
                for (int node : area_to_node[area])
                    if (num_task_node[node] < min_tasks)
                    {
                        min_tasks = num_task_node[node];
                        node_idx = node;
                    }
                    else if (num_task_node[node] == min_tasks)
                        node_idx = min(node, node_idx);
            printf("%d ", node_idx);
        }
        printf("\n");
    }

    // // DEBUG
    // std::set<int> set1 = {1, 2, 3, 4, 5};
    // std::set<int> set2 = {4, 5, 6, 7, 8};
    // for (int e : exclude(set1, set2))
    //     printf("%d ", e);
}

set<int> filter(int na, int pa, int paa, int paar)
{
    set<int> fil_area = avail_area;
    if (na != 0)
        fil_area = set<int>{na};
    if (pa != 0)
        fil_area = intersection(fil_area, application_to_area[pa]);
    if (paa != 0)
    {
        set<int> temp_ans = exclude(fil_area, application_to_area[paa]); // 执行反亲和要求
        if (temp_ans.empty() && paar == 0)                               // 假如找不到满足要求节点，同时反亲和要求不必须
            return fil_area;
        else
            return temp_ans;
    }
    return fil_area;
}

set<int> intersection(set<int> set1, set<int> set2)
{
    set<int> inter;
    for (int element : set1)
        if (set2.count(element) > 0)
            inter.insert(element);
    return inter;
}

set<int> exclude(set<int> set1, set<int> set2)
{
    set<int> ans;
    for (int element : set1)
        if (set2.count(element) == 0)
            ans.insert(element);
    return ans;
}
