#include <bits/stdc++.h>
using namespace std;

struct roaming_data
{
    int u, r, d;

    roaming_data(int d, int u, int r)
    {
        this->u = u;
        this->r = r;
        this->d = d;
    }
    roaming_data() {}
};

set<pair<int, int>> affect_region; // 储存地址和时间
vector<roaming_data> items;

int main()
{
    int n;
    int ri, mi, pij;
    int d, u, r;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {

        for (set<pair<int, int>>::iterator iter = affect_region.begin(); iter != affect_region.end();)
        {
            const pair<int, int> &r = *iter;
            if (i >= r.second + 7)
                iter = affect_region.erase(iter);
            else
                iter++;
        }

        scanf("%d %d", &ri, &mi);
        for (int j = 0; j < ri; j++)
        {
            scanf("%d", &pij);
            for (int k = 0; k < 7; k++) // 输入风险地区信息
                affect_region.insert({pij, i + k});
        }

        // printf("DEBUG: affect_region");
        // for (pair<int, int> r : affect_region)
        //     printf("(%d %d) ", r.first, r.second);
        // printf("\n");

        for (int j = 0; j < mi; j++)
        {
            scanf("%d %d %d", &d, &u, &r); // 输入漫游数据信息
            items.push_back(roaming_data(d, u, r));
        }

        // for (roaming_data item : items)
        //     printf("DEBUG: day=%d, user=%d, region=%d\n", item.d, item.u, item.r);

        printf("%d ", i);

        vector<roaming_data> update_items;
        set<int> affect_users;
        for (roaming_data item : items)
        {
            bool flag = true;
            if (i - item.d >= 7)
                continue;
            for (int j = item.d; j <= i; j++) // 考虑用户到达当地至今日，该地区是否一直处于高风险状态
                if (affect_region.count({item.r, j}) == 0)
                {
                    flag = false;
                    break;
                }

            if (flag)
            {
                update_items.push_back(item);
                affect_users.insert(item.u);
            }
        }
        items.clear();
        items = update_items;
        
        for (int u : affect_users)
            printf("%d ", u);
        printf("\n");
    }
}