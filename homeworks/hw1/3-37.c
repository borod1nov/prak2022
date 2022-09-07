// 3.37. Вычислить с точностью eps > 0 значение числа e - предел последо-
// вательности { x i }при i → ∞
// x(i) = (1+1/i)^i , i = 1, 2, ...
// Считать, что требуемая точность достигнута, если | x(i) - x(i+1)| < eps.

#include <stdio.h>
#include <math.h>

int main(void)
{
    float eps, sum = 0, curr = 100, prev;
    scanf("%f", &eps);
    float i = 1;
    while (((curr - prev) >= eps) || ((prev - curr) >= eps))
    {
        prev = curr;
        float base = 1 + (1 / i);
        curr = pow(base, i);
        i++;
    }
    printf("%f\n", curr);
    return 0;
}