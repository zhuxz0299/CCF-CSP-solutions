#include <bits/stdc++.h>
using namespace std;

int num_unzip = 0; // 表示已经解压缩的字节数
char unzip_data[1 << 22];

void get_character(char &c)
{
    c = '\n';
    while (c == '\n')
        c = getchar();
}

void get_byte(char &c1, char &c2)
{
    get_character(c1);
    get_character(c2);
}

void print_byte(char c1, char c2)
{
    unzip_data[num_unzip * 2] = c1;
    unzip_data[num_unzip * 2 + 1] = c2;
    num_unzip++;
}

int byte_to_int(char &c1, char &c2)
{
    int n1, n2;
    n1 = c1 <= '9' ? c1 - '0' : c1 - 'a' + 10;
    n2 = c2 <= '9' ? c2 - '0' : c2 - 'a' + 10;
    return n1 * 16 + n2;
}

int read_boot_domain(int &length)
{
    char char1, char2;
    int base = 1, num_byte = 0; // base为基，num_byte为现在已经读取的字节数
    while (true)                // 读取引导区
    {
        get_byte(char1, char2);
        int num = byte_to_int(char1, char2);
        if (num < 128)
        {
            length += num * base;
            break;
        }
        length += (num - 128) * base;
        base *= 128;
        num_byte += 1;
    }
    return num_byte + 1; // 在break的地方还要加1
}

int read_literal(int type)
{
    int l = 0, extend_type = 0; // l是字面量的长度，extend_type是表示后面有几个字节用来存储字面量长度
    char c1, c2;
    // 获得字面量长度
    if (type / 4 <= 59)
        l = type / 4 + 1;
    else
    {
        extend_type = type / 4 - 59;
        int base = 1;
        for (int i = 0; i < extend_type; i++)
        {
            get_byte(c1, c2);
            l += byte_to_int(c1, c2) * base;
            base *= 256;
        }
        l += 1;
    }
    // 读取字面量
    for (int i = 0; i < l; i++)
    {
        get_byte(c1, c2);
        print_byte(c1, c2);
    }
    // printf("DEBUG:l=%d\n", l);
    return l + extend_type + 1; // 返回的数表示这个元素占用的字节数
}

void read_trace_helper(int o, int l)
{
    int start_point = num_unzip - o;
    if (o >= l)
        for (int i = 0; i < l; i++)
            print_byte(unzip_data[(start_point + i) * 2], unzip_data[(start_point + i) * 2 + 1]);
    else
        for (int i = 0; i < l; i++)
            print_byte(unzip_data[(start_point + i % o) * 2], unzip_data[(start_point + i % o) * 2 + 1]);
}

int read_trace1(int type)
{
    char c1, c2;
    int l = (type / 4) % 8 + 4;
    int o = type / 32;
    get_byte(c1, c2);
    o = o * 256 + byte_to_int(c1, c2);
    read_trace_helper(o, l);
    // printf("DEBUG:o=%d,l=%d in read_trace1\n", o, l);
    return 2; // 返回的数表示这个元素占用的字节数
}

int read_trace2(int type)
{
    char c1, c2;
    int l = type / 4 + 1;
    get_byte(c1, c2);
    int o = byte_to_int(c1, c2);
    get_byte(c1, c2);
    o = o + byte_to_int(c1, c2) * 256;
    read_trace_helper(o, l);
    // printf("DEBUG:o=%d,l=%d in read_trace2\n", o, l);
    return 3; // 返回的数表示这个元素占用的字节数
}

int main()
{
    char char1, char2;                 // 一个字节的两个字符
    int length = 0;                    // length为原始数据的长度
    int input;                         // 输入的字节数
    scanf("%d", &input);               // 读取接下来要输入的字节数
    input -= read_boot_domain(length); // 读取引导域，获得原始数据长度

    // printf("DEBUG: the length of data is: %d\n", length);
    // printf("DEBUG: the remaining input is: %d\n", input);

    while (input > 0)
    {
        get_byte(char1, char2);
        int type = byte_to_int(char1, char2); // 读取每个元素的第一个字节
        switch (type % 4)
        {
        case 0:                          // 假如末两位为00
            input -= read_literal(type); // 元素为字面量，函数返回输入字节的个数
            // printf("DEBUG:num_unzip=%d\n", num_unzip);
            break;

        case 1: // 假如末两位为01
            input -= read_trace1(type);
            // printf("DEBUG:num_unzip=%d\n", num_unzip);
            break;

        case 2:
            input -= read_trace2(type);
            // printf("DEBUG:num_unzip=%d\n", num_unzip);
            break;

        default:
            printf("DEBUG: something went wrong!\n");
            break;
        }
    }

    // printf("DEBUG:num_unzip=%d\n", num_unzip);
    for (int i = 0; i < num_unzip; i++)
    {
        printf("%c%c", unzip_data[i * 2], unzip_data[i * 2 + 1]);
        if (i % 8 == 7)
            printf("\n");
    }

    return 0;
}