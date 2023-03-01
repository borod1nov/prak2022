// 3.19. Подсчитать количество натуральных чисел n ( 102 ≤ n ≤ 987 ), в
// которых все три цифры различны.

#include <stdio.h>
#include <math.h>

int main(void)
{
    int count = 0;
    for (int i = 102; i <= 987; i++)
    {
        if (((i / 100) == (i % 100 / 10)) && ((i / 100) == (i % 10)))
            count += 1;
    }
    printf("%d\n", count);
    return 0;
}