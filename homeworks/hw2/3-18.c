// 3.18. Подсчитать количество натуральных чисел n ( 111 ≤ n ≤ 999 ), в
// записи которых есть две одинаковые цифры.

#include <stdio.h>
#include <math.h>

int main(void)
{
    int count = 0;
    for (int i = 111; i <= 999; i++)
    {
        if (((i / 100) == (i % 100 / 10)) || 
            ((i / 100) == (i % 10)) || 
            ((i % 100 / 10) == (i % 10)))
            count += 1;
    }
    printf("%d\n", count);
    return 0;
}