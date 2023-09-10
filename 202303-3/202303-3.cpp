#include <bits/stdc++.h>
using namespace std;

struct user_attr
{
    int label = 0; // 属性的编号
    int value = 0; // 属性的值
};

struct user
{
    int dn = 0;
    int attr_num = 0;
    user_attr attr[500];
};

user usr[2500];          // 定义用户
string expr[500];        // 定义表达式
vector<int> matched_usr; // 用于储存最终输出的用户
int n, m;                // n为用户的数量，m为表达式的数量

vector<int> translate_base_expr(string expr);                  // 处理简单语句
vector<int> translate_expr(string expr);                       // 处理一般语句
bool match_expr(int usr, int label, int value, bool positive); // 判断某个用户的某个属性是否具有该值
vector<int> get_union(const vector<int> &vec1, const vector<int> &vec2);
vector<int> get_intersection(vector<int> vec1, vector<int> vec2);

int main()
{
    int attr_num;               // 要输入的属性值的个数
    scanf("%d", &n);            // 输入用户的数目
    for (int i = 0; i < n; i++) // 输入用户的dn值和属性
    {
        scanf("%d%d", &(usr[i].dn), &(usr[i].attr_num));
        for (int j = 0; j < usr[i].attr_num; j++)
            scanf("%d%d", &(usr[i].attr[j].label), &(usr[i].attr[j].value));
    }

    scanf("%d", &m);
    cin.get();
    for (int i = 0; i < m; i++)
        getline(cin, expr[i]);

    for (int i = 0; i < m; i++)
    {
        matched_usr = translate_expr(expr[i]);
        sort(matched_usr.begin(), matched_usr.end());
        for (int usr_dn : matched_usr)
            printf("%d ", usr_dn);
        printf("\n");
    }
}

bool match_expr(int usr_id, int label, int value, bool positive) // 这里的usr_id和dn不同
{
    int left = 0, right = usr[usr_id].attr_num - 1;
    int i = (left + right) / 2;
    while (true)
    {
        if (usr[usr_id].attr[i].label == label) // 找到正确的attr了
            break;
        else if (usr[usr_id].attr[i].label > label)
            right = i - 1;
        else
            left = i + 1;
        if (left > right) // 该用户没有该属性
            return false;
        i = (left + right) / 2;
    }

    if (positive)
    {
        if (usr[usr_id].attr[i].value == value)
            return true;
        else
            return false;
    }
    else
    {
        if (usr[usr_id].attr[i].value == value)
            return false;
        else
            return true;
    }
}

vector<int> translate_base_expr(string expr)
{
    vector<int> selected_usr;
    selected_usr.reserve(2500);
    bool positive, overturn = false; // overturn决定现在在读取label还是value
    int value = 0, label = 0;
    for (int i = 0; i < expr.length(); ++i) // 处理base_expr，读取label和value
        if (expr[i] >= '0' && expr[i] <= '9')
        {
            if (overturn)
                value = value * 10 + (expr[i] - '0');
            else
                label = label * 10 + (expr[i] - '0');
        }
        else
        {
            overturn = true;
            if (expr[i] == ':')
                positive = true;
            else if (expr[i] == '~')
                positive = false;
            else
                printf("DEBUG: something go wrong in operater!\n");
        }

    // printf("DEBUG: label=%d, value=%d, positive=%d\n", label, value, positive);

    for (int i = 0; i < n; i++)
        if (match_expr(i, label, value, positive))
            selected_usr.push_back(usr[i].dn);
    return selected_usr;
}

vector<int> translate_expr(string expr)
{
    vector<int> selected_usr;
    selected_usr.reserve(2500);
    bool vec_union; // 如果是|，则就是union；如果是&，则为intersection
    int left_brac_cnt = 0;
    int second_expr_start, second_expr_len, first_expr_len, first_expr_start = 2;

    if (expr[0] != '&' && expr[0] != '|')
        return translate_base_expr(expr);
    if (expr[0] == '&')
        vec_union = false;
    else if (expr[0] == '|')
        vec_union = true;

    for (int i = 2; i < expr.length(); i++)
        if (expr[i] == '(')
            left_brac_cnt++;
        else if (expr[i] == ')')
            if (left_brac_cnt > 0)
                left_brac_cnt--;
            else if (left_brac_cnt == 0 && expr[i + 1] == '(')
                second_expr_start = i + 2;
            else
                printf("DEBUG: something went wrong in bracket paring!\n");

    first_expr_len = (second_expr_start - 2) - first_expr_start;
    second_expr_len = (expr.length() - 1) - second_expr_start;

    string sub_expr1 = expr.substr(first_expr_start, first_expr_len);
    string sub_expr2 = expr.substr(second_expr_start, second_expr_len);

    // printf("DEBUG: expr=%s\n", expr.c_str());

    // printf("DEBUG: firtst_expr_start=%d, first_expr_len=%d, second_expr_start=%d, second_expr_len=%d\n", first_expr_start, first_expr_len, second_expr_start, second_expr_len);

    vector<int> selected_usr1 = translate_expr(sub_expr1);
    vector<int> selected_usr2 = translate_expr(sub_expr2);

    // printf("DEBUG: sub_expr1=%s\n", sub_expr1.c_str());
    // printf("DEBUG: selected_usr1=");
    // for (int usr1 : selected_usr1)
    //     printf("%d ", usr1);
    // printf("\n");
    // printf("DEBUG: sub_expr2=%s\n", sub_expr2.c_str());
    // printf("DEBUG: selected_usr2=");
    // for (int usr2 : selected_usr2)
    //     printf("%d ", usr2);
    // printf("\n");

    if (vec_union)
        return get_union(selected_usr1, selected_usr2);
    else
        return get_intersection(selected_usr1, selected_usr2);
}

vector<int> get_union(const vector<int> &vec1, const vector<int> &vec2)
{
    vector<int> result;
    result.reserve(vec1.size() + vec2.size());

    result.insert(result.end(), vec1.begin(), vec1.end());
    result.insert(result.end(), vec2.begin(), vec2.end());

    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());

    return result;
}

vector<int> get_intersection(vector<int> vec1, vector<int> vec2)
{
    vector<int> result;
    result.reserve(min(vec1.size(), vec2.size()));
    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());

    int pointer1 = 0, pointer2 = 0;
    while (pointer1 < vec1.size() && pointer2 < vec2.size())
    {
        if (vec1[pointer1] == vec2[pointer2])
        {
            result.push_back(vec1[pointer1]);
            pointer1++;
            pointer2++;
        }
        else if (vec1[pointer1] > vec2[pointer2])
            pointer2++;
        else
            pointer1++;
    }
    return result;
}