#include <bits/stdc++.h>
using namespace std;

struct rectangle
{
    rectangle() {}
    rectangle(int left, int bottom, int right, int top)
    {
        this->left = left, this->right = right;
        this->bottom = bottom, this->top = top;
    }

    int get_area()
    {
        return (right - left) * (top - bottom);
    }

    void resize(int left, int bottom, int right, int top)
    {
        this->left = left, this->right = right;
        this->bottom = bottom, this->top = top;
    }
    
    int left, right, bottom, top;
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
        return 0;
    rectangle insert_r(max(r1.left, r2.left), max(r1.bottom, r2.bottom), min(r1.right, r2.right), min(r1.top, r2.top));
    return insert_r.get_area();
}

int main()
{
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    
    int left, bottom, right, top;
    int area = 0;
    rectangle new_r(0, 0, a, b), r;

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d %d", &left, &bottom, &right, &top);
        r.resize(left, bottom, right, top);
        area += insert_area(r, new_r);
    }

    printf("%d", area);
}