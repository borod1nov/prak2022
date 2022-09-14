//3.22. Определить, верно ли, что куб суммы цифр натурального числа n
//равен n^2 .

#include <stdio.h>

int main(void)
{
    int n, k, sum = 0;
    scanf("%d", &n);
    k = n;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    if (sum * sum * sum == k * k)
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}