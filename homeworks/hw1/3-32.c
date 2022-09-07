// 3.32. Распечатать первые n простых чисел ( p - простое число, если
// p >= 2 и делится только на 1 и на себя).

#include <stdio.h>

int main(void)
{
    int i = 2, n, count = 0;
    scanf("%d", &n);
    while (count < n)
    {
        int is_prime = 1;
        for (int j = 2; j < i; j++)
            if (i % j == 0)
                is_prime = 0;
        if (is_prime == 1)
        {
            count ++;
            printf("%d ", i);
        }
        i++;
    }
    printf("\n");
    return 0;
}