#include <stdio.h>

void swap(int* a,int* b)
{
    (*a) ^= (*b);
    (*b) ^= (*a);
    (*a) ^= (*b);
}

int main(void)
{
    for (i=0; i<15; i++){
        if (i & 1)
            swap(&a[0], &a[1]);
        else if (i & 3)
            swap(&a[1], &a[2]);
        else if (i & 7)
            swap(&a[3], &a[0]);
        printf("%d,%d,%d,%d\n", a[0], a[1], a[2], a[3]);
    }
    return 0;
}
