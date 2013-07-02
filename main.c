#include <stdio.h>
enum opr
{
    op_add,
    op_sub,
    op_mul,
    op_div
};
char oprStr[]="+-*/";

struct exp
{
    char str[24];
    enum opr op;
    float r;
}ret;
struct exp6
{
    struct exp d[6];
    int c;
}ret6;
struct exp36
{
    struct exp d[36];
    int c;
}ret36;
struct exp216
{
    struct exp d[216];
    int c;
}ret216;




int main(void)
{
    int i,i2,i3,i4;
    float a[4]= {1,2,3,4};

    printf("24 point solver by SkyWolf (hejun442001 at 126 dot com).\n");
    do
    {
        printf("Input 4 numbers between 1 and 13(split by comma,example 1,13,5,10):\n");
        scanf("%f,%f,%f,%f", &a[0], &a[1], &a[2], &a[3]);
        for (i=0; i<4; i++)
            if (a[i] < 1 || a[i] > 13)
            {
                printf("One of the numbers is not between 1 and 13!please re-input there!\n");
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

                    printf("%f, %f, %f, %f\n", a[i], a[i2], a[i3], a[i4]);
                }
            }
        }
    return 0;
}
