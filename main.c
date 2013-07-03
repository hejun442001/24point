#include <stdio.h>
#include <conio.h>

enum opr
{
    op_add,
    op_sub,
    op_mul,
    op_div,
    op_rsub,
    op_rdiv,
    op_err = -1
};
char oprStr[]="+-*/-/";

struct exp
{
    char str[12];
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

inline int isGoal(float x,float goal)
{
    return (int)(goal + 0.5) == (int)(x + 0.5);
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
                continue;
            break;
        default:
            continue;
            break;
        }

        ret.d[c].r = r;
        sprintf(ret.d[c].str, "%d%c%d", a, oprStr[i], b);
        c++;
    }
    ret.c = c;
    return ret;
}

struct exp36 calc3(struct exp6 ea, int b)
{
    struct exp36 ret;
    float a;
    int i = 0,c=0;
    float r;
    enum opr op;

    if (ea.c == 0) return ret;
    for (i = 0; i < ea.c; i++)
    {
        a = ea.d[i].r;
        for (op = 0; op < 6; op++)
        {
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
                r = a / b;
                break;
            case op_rsub:
                r = b - a;
                break;
            case op_rdiv:
                if (a != 0.0)
                    r = b / a;
                else
                    continue;
                break;
            default:
                continue;
            }

            ret.d[c].r = r;
            if (op == op_rdiv || op == op_rsub)
                sprintf(ret.d[c].str,"%d%c(%s)",b,oprStr[op],ea.d[i].str);
            else
                sprintf(ret.d[c].str,"(%s)%c%d",ea.d[i].str,oprStr[op],b);
            c++;
        }
    }
    ret.c = c;
    return ret;
}

void calc4enn_(struct exp ea, enum opr opr, int b)
{
    float r,a;

    a = ea.r;
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
        r = (float)a / (float)b;
        break;
    case op_rsub:
        r = b - a;
        break;
    case op_rdiv:
        if (a != 0.0)
            r = b / a;
        break;
    default:
        break;
    }

    if (isGoal(r, 24))
    {
        if (opr == op_rdiv || opr == op_rsub)
            printf("%d%c(%s)\t", b, oprStr[opr], ea.str);
        else
            printf("(%s)%c%d\t", ea.str, oprStr[opr], b);
    }
}

void calc4enn(struct exp6 left, int r1, int r2)
{
    struct exp36 ret = calc3(left, r1);
    int c;
    enum opr op;
    for (c = 0; c < ret.c; c++)
        for (op = 0; op < 6; op++)
            calc4enn_(ret.d[c], op, r2);
}
void calc4ee_(struct exp ea, enum opr opr, struct exp eb)
{
    float r,a,b;

    a = ea.r;
    b = eb.r;
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
        printf("(%s)%c(%s)\t",ea.str,oprStr[opr],eb.str);
    }

}
void calc4ee(struct exp6 left, int r1, int r2)
{
    struct exp6 ret = calc2(r1, r2);
    int i, c;
    enum opr op;

    for (i = 0; i < ret.c; i++)
        for (c = 0; c < left.c; c++)
            for (op = 0; op < 4; op++)
                calc4ee_(left.d[c], op, ret.d[i]);
}

void calc4(int a, int b, int c, int d)
{
    struct exp6 left = calc2(a,b);
    calc4ee(left, c, d);
    calc4enn(left, c, d);
}
int main(void)
{
    int i,i2,i3,i4;
    int a[4];

    printf("24 point solver by SkyWolf (hejun442001 at 126 dot com).\n");
    do
    {
        do
        {
            fflush(stdin);
            printf("Input 4 numbers between 1 and 13 (Example:1 13 5 10):");
            i = scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);
            if (i != 4)
            {
                printf("Fommat is not well (Only use numbers and spaces)! Please re-input!\n");
                continue;
            }
            for (i = 0; i < 4; i++)
                if (a[i] < 1 || a[i] > 13)
                {
                    printf("One of the numbers is not between 1 and 13! Please re-input!\n");
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
                        calc4(a[i], a[i2], a[i3], a[i4]);
                    }
                }
            }
        fflush(stdin);
        printf("\nnext?[y/n]");
        do
        {
            i = getchar();
            i2 = (i == 'y' || i == 'Y') ? 1 :
                 (i == 'n' || i == 'N') ? 0 : -1;
        }
        while (i2 >= 0);
    }
    while (i2 == 1);
    return 0;
}
