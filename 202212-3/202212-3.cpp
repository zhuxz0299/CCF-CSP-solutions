#include <bits/stdc++.h>
using namespace std;

int Q[8][8] = {0};          // 量化矩阵
int M[8][8] = {0};          // 图像矩阵
double transformed_M[8][8]; // 经过余弦变换之后的图像矩阵
const double pi = acos(-1);

void scan_data(int n);
void print_matrix(int matrix[][8]);
void print_matrix(double matrix[][8]);
void quantify_matrix();
double alpha(int u);
void transform_matrix();

int main()
{
    int n, T;

    for (int i = 0; i < 8; ++i) // 读取量化矩阵
        for (int j = 0; j < 8; ++j)
            scanf("%d", &(Q[i][j]));
    scanf("%d", &n); // 扫描数据的个数
    scanf("%d", &T); // 要进行的任务
    scan_data(n);    // 读取压缩后的矩阵

    switch (T)
    {
    case 0:
        break;
    case 1:
        quantify_matrix();
        break;
    case 2:
        quantify_matrix();
        transform_matrix();
        break;
    default:
        printf("DEBUG: get invalid T!");
        break;
    }

    print_matrix(M);
}

void scan_data(int n)
{
    for (int i = 0, p = 0, q = 0; i < n; i++)
    {
        scanf("%d", &(M[p][q]));
        // printf("DEBUG: M[%d][%d]=%d ", p, q, M[p][q]);
        if ((p + q) % 2 == 1)
        {
            if (p == 7)
                q++;
            else if (q == 0)
                p++;
            else
                q--, p++;
        }
        else
        {
            if (p == 0)
                q++;
            else if (q == 7)
                p++;
            else
                q++, p--;
        }
    }
}

void print_matrix(int matrix[][8])
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void print_matrix(double matrix[][8])
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
            printf("%.2lf\t", matrix[i][j]);
        printf("\n");
    }
}

void quantify_matrix()
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            M[i][j] *= Q[i][j];
}

double alpha(int u)
{
    return u == 0 ? sqrt((double)1.0 / 2.0) : 1;
}

void transform_matrix()
{

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
        {
            transformed_M[i][j] = 0;
            for (int u = 0; u < 8; ++u)
                for (int v = 0; v < 8; ++v)
                {
                    transformed_M[i][j] += alpha(u) * alpha(v) * M[u][v] * cos(pi / 8 * (i + (double)1.0 / 2.0) * u) * cos(pi / 8 * (j + (double)1.0 / 2.0) * v);
                    // if (i == 0 && j == 1)
                    // {
                    //     printf("alpha(%d)=%.2lf, alpha(%d)=%.2lf\t", u, alpha(u), v, alpha(v));
                    //     printf("M[%d][%d]=%d\t", u, v, M[u][v]);
                    //     printf("cos(pi/8*(%d+1/2)*%d)=%.2lf, cos(pi/8*(%d+1/2)*%d)=%.2lf\t", i, u, cos(pi / 8 * (i + 1.0 / 2.0) * u), j, v, cos(pi / 8 * (j + 1.0 / 2.0) * v));
                    //     printf("transformed_M[0][0]=%.2lf\n", transformed_M[i][j]);
                    // }
                }

            transformed_M[i][j] = 1.0 / 4.0 * transformed_M[i][j];

            // printf("%.2lf\t", transformed_M[i][j]);
            // if (j == 7)
            //     printf("\n");
        }

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
        {
            M[i][j] = round(transformed_M[i][j] + 128);
            M[i][j] = min(M[i][j], 255);
            M[i][j] = max(M[i][j], 0);
        }
}

// 16 11 10 16 24 40 51 61
// 12 12 14 19 26 58 60 55
// 14 13 16 24 40 57 69 56
// 14 17 22 29 51 87 80 62
// 18 22 37 56 68 109 103 77
// 24 35 55 64 81 104 113 92
// 49 64 78 87 103 121 120 101
// 72 92 95 98 112 100 103 99
// 64
// 0
// 148 -22 -132 230 245 165 28 250 -37 -192 11 168 114 -78 -11 -253 -46 -102 11 36 -248 243 -223 177 116 59 213 -158 224 78 223 81 -230 172 120 -111 179 -99 -84 188 95 -36 -116 -249 -143 -66 -226 173 4 244 233 -100 -113 255 169 -149 -18 -28 255 148 50 142 -129 -248