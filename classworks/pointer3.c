
#include <stdio.h>

void move(int* a, int n, int m)
{
    for (int j = 0; j < m; j++) 
        for (int i = n - 1; i > 0; i--)
        {
            int tmp = *(a + i - 1);
            *(a + i - 1) = *(a + i);
            *(a + i) = tmp;
        }
}

int main(int argc, char **argv)
{
    int a[5] = {1, 2, 3, 4, 5};
    move(a, 5, 2);
    for (int i = 0; i < 5; i++)
        printf("%d ", a[i]);
    return 0;
}

