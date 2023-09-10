#include <bits/stdc++.h>
using namespace std;

struct point
{
    point() {}
    point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int x, y;
};

struct rectangle
{
    rectangle() {}
    rectangle(point lb, point rt)
    {
        this->lb = lb;
        this->rt = rt;
        this->left = lb.x, this->right = rt.x;
        this->top = rt.y, this->bottom = lb.y;
        this->lt = point(this->left, this->top);
        this->rb = point(this->right, this->bottom);
    }
    point lt, rt, lb, rb;
    int left, right, top, bottom;
};

bool is_insert(rectangle r1, rectangle r2)
{
    if (r1.left >= r2.right || r2.left >= r1.right || r1.bottom >= r2.top || r2.bottom >= r1.top)
        return false;
    return true;
}

int insert_area(rectangle r1, rectangle r2)
{
    if (!is_insert(r1, r2))
        return false;
    point lb(max(r1.left, r2.left), max(r1.bottom, r2.bottom));
    point rt(min(r1.right, r2.right), min(r1.top, r2.top));
    rectangle r_insert(lb, rt);
    return (r_insert.right - r_insert.left) * (r_insert.top - r_insert.bottom);
}

int main()
{
    int n, a, b;
    int left, right, top, bottom;
    scanf("%d %d %d", &n, &a, &b);
    int area = 0;
    rectangle new_r(point(0, 0), point(a, b));
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d %d", &left, &bottom, &right, &top);
        rectangle r(point(left, bottom), point(right, top));
        area += insert_area(new_r, r);
    }
    printf("%d", area);
}