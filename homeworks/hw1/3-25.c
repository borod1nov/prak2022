// 3.25. Для данного вещественного положительного числа a найти наи-
// меньшее целое положительное n такое, что 1 + 1/2 +1/3+ ... + 1/n > a.

#include <stdio.h>
#include <math.h>

int main(void)
{
    float a, sum = 0, n = 1;
    scanf("%f", &a);
    while (sum < a)
    {
        sum += 1 / n;
        n += 1;
    }
    n -= 1;
    printf("%d\n", (int)n);
    return 0;
}