#include <stdio.h>
enum opr
{
    op_add,
    op_sub,
    op_mul,
    op_div,
    op_err = -1
};
char oprStr[]="+-*/";
inline int cmpOpr(enum opr a, enum opr b)
{
    if (a == op_err || (a < op_mul && b >= op_mul))
        return -1;
    if (b == op_err || (b < op_mul && a >= op_mul))
        return 1;
    return 0;
}

struct exp
{
    char str[24];
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

inline int isGoal(float x,float goal)
{
    return (goal - 0.000001 < x &&
            x < goal + 0.000001);
}

struct exp6 calc2(int a, int b)
{
    struct exp6 ret;
    int i = 0,c=0;
    float r;
    enum opr op;
    for (i=0; i<4; i++)
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
        case op_div:
            if (b != 0.0)
                r = (float)a / (float)b;
            else
                op = op_err;
            break;
        default:
            break;
        }


        if (op != op_err)
        {
            ret.d[c].r = r;
            sprintf(ret.d[c].str,"%d%c%d",a,oprStr[i],b);
            c++;
        }
    }
    ret.c = c;
    return ret;
}
struct exp6 calc2g(int a, int b, float goal)
{
    struct exp6 ret;
    int i = 0,c=0;
    float r;
    enum opr op;
    for (i=0; i<4; i++)
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
        case op_div:
            if (b != 0.0)
                r = (float)a / (float)b;
            else
                op = op_err;
            break;
        default:
            op = op_err;
            break;
        }


        if (op != op_err && isGoal(r, goal))
        {

            ret.d[c].r = r;
            sprintf(ret.d[c].str,"%d%c%d",a,oprStr[i],b);
            c++;
        }
    }
    ret.c = c;
    return ret;
}

void calc4ee_(struct exp ea, enum opr opr, struct exp6 eb)
{
    int c;
    float r,a,b;

    if (eb.c == 0) return;

    for (c = 0; c < eb.c; c++)
    {
        a = ea.r;
        b = eb.d[c].r;
        switch (opr)
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
        case op_div:
            if (b != 0.0)
                r = (float)a / (float)b;
            else
                r = 0;
            break;
        default:
            r = 0;
            break;
        }


        if (isGoal(r, 24))
        {
            printf("(%s)%c(%s)=24\t",ea.str,oprStr[opr],eb.d[c].str);
        }
    }
}
void calc4ee(struct exp6 left, int r1, int r2)
{
    struct exp6 ret;
    int i = 0,c;
    float r;
    enum opr op;
    for (c = 0; c < left.c; c++)
    {
        for (i = 0; i < 4; i++)
        {
            op = i;
            switch (op)
            {
            case op_add:
                r = 24.0 - left.d[c].r;
                ret = calc2g(r1, r2, r);
                calc4ee_(left.d[c], op, ret);
                break;
            case op_sub:
                r = left.d[c].r - 24;
                ret = calc2g(r1, r2, r);
                calc4ee_(left.d[c], op, ret);
                break;
            case op_mul:
                if (left.d[c].r != 0.0)
                {
                    r = 24 / left.d[i].r;
                    ret = calc2g(r1, r2, r);
                    calc4ee_(left.d[c], op, ret);
                }
                break;
            case op_div:
                r = left.d[c].r / 24;
                ret = calc2g(r1, r2, r);
                calc4ee_(left.d[c], op, ret);
                break;
            default:
                break;
            }
        }
    }
}

void solve(int a, int b, int c, int d)
{
    struct exp6 left = calc2(a,b);
    calc4ee(left, c, d);
}

int main(void)
{
    int i,i2,i3,i4;
    int a[4] = {1,2,3,4};

    printf("24 point solver by SkyWolf (hejun442001 at 126 dot com).\n");
    do
    {
        printf("Input 4 numbers between 1 and 13 (split by space.example:1 13 5 10):\n");
        scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);
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
                    printf("\n%d,%d,%d,%d:\n", a[i], a[i2], a[i3], a[i4]);
                    solve(a[i], a[i2], a[i3], a[i4]);
                }
            }
        }
    return 0;
}
