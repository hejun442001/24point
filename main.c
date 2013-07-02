#include <stdio.h>
enum opr
{
    op_add,
    op_sub,
    op_subr,
    op_mul,
    op_div,
    op_divr,
    op_err
};
char oprStr[]="+--*//";

struct exp
{
    char str[24];
    enum opr op;
    float r;
};
struct exp6
{
    struct exp d[6];
    int c;
};
struct exp36
{
    struct exp d[36];
    int c;
};
struct exp216
{
    struct exp d[216];
    int c;
};

struct exp6 calc2(int a, int b)
{
    struct exp6 ret;
    int i = 0,c=0;
    float r;
    enum opr op;
    for (i=0; i<6; i++)
    {
        op = i;
        switch (op)
        {
        case op_add:
            r = a + b;
            break;
        case op_sub:
            r = a - b;
            break;
        case op_mul:
            r = a * b;
            break;
        case op_subr:
            r = b - a;
            break;
        case op_div:
            if (b != 0.0)
                r = (float)a / (float)b;
            else
                op = op_err;
            break;
        case op_divr:
            if (a != 0.0)
                r = (float)b / (float)a;
            else
                op = op_err;
            break;
        default:
            break;
        }


        if (op != op_err)
        {
            ret.d[c].op = op;
            ret.d[c].r = r;
            if (op == op_subr || op == op_divr)
                sprintf(ret.d[c].str,"%d%c%d",b,oprStr[i],a);
            else
                sprintf(ret.d[c].str,"%d%c%d",a,oprStr[i],b);
            c++;
        }
    }
    ret.c = c;
    return ret;
}
void solve(int a, int b, int c, int d)
{
    struct exp6 left = calc2(a,b);
}

int main(void)
{
    int i,i2,i3,i4;
    int a[4] = {1,2,3,4};

    printf("24 point solver by SkyWolf (hejun442001 at 126 dot com).\n");
    do
    {
        printf("Input 4 numbers between 1 and 13 (split by comma,example 1,13,5,10):\n");
        scanf("%d,%d,%d,%d", &a[0], &a[1], &a[2], &a[3]);
        for (i=0; i<4; i++)
            if (a[i] < 1 || a[i] > 13)
            {
                printf("One of the numbers is not between 1 and 13! please re-input them!\n");
                break;
            }
    }
    while (i!=4);

    for (i = 0; i < 4; i++)
        for (i2 = 0; i2 < 4; i2++)
        {
            if (i == i2) continue;
            for (i3 = 0; i3 < 4; i3++)
            {
                if (i == i3 || i2 == i3) continue;
                for (i4 = 0; i4 < 4; i4++)
                {
                    if (i == i4 || i2 == i4 || i3 == i4) continue;
                    solve(a[i], a[i2], a[i3], a[i4]);
                }
            }
        }
    return 0;
}
