#include <bits/stdc++.h>
#include <vector>
using namespace std;

int n, m, k;
vector<int> times;
vector<int> com_resources;

bool satisfy(int guess_time) // 手上的资源足够让总时间减少到guess_time
{
    long long require_resource = 0;
    for (int i = 0; i < n; i++)
    {
        if (times[i] <= guess_time)
            continue;
        require_resource += (times[i] - guess_time) * com_resources[i];
    }
    if (require_resource <= m)
        return true;
    else
        return false;
}

int main()
{
    int time, com_resource;
    int max_time = 0;

    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) // 读取数据，并且获得最长时间
    {
        scanf("%d %d", &time, &com_resource);
        if (time > max_time)
            max_time = time;
        times.push_back(time);
        com_resources.push_back(com_resource);
    }

    if (satisfy(k))
    {
        printf("%d", k);
        return 0;
    }

    int left_bound = k, right_bound = max_time;
    int guess_time = (left_bound + right_bound) / 2;
    // printf("left_bound=%d, right_bound=%d\n", left_bound, right_bound);
    while (left_bound < right_bound)
    {
        if (satisfy(guess_time))
            right_bound = guess_time;
        else
            left_bound = guess_time + 1;
        guess_time = (left_bound + right_bound) / 2;
        // printf("left_bound=%d, right_bound=%d\n", left_bound, right_bound);
    }
    printf("%d", guess_time);
    return 0;
}