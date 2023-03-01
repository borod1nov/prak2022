//3.34. Распечатать первые n чисел Фибоначчи ( f0 = 1; f1 = 1; fk+1 = fk-1 + fk ;
// k = 1, 2, 3,...)

#include <stdio.h>

int main(void)
{
    int n, fib0 = 1, fib1 = 1;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        fib1 += fib0;
        fib0 = fib1 - fib0;
        printf("fib № %d: %d\n", i, fib0);
    }
    return 0;
}