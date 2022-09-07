// Для данных чисел a, b и c определить, сколько корней имеет урав-
// нение ax 2 +bx+c = 0, и распечатать их. Если уравнение имеет комплексные кор-
// ни, то распечатать их в виде v ± iw.

#include <stdio.h>
#include <math.h>

int main(void)
{
    float a, b, c, d;
    printf("Enter a: ");
    scanf("%f", &a);
    printf("Enter b: ");
    scanf("%f", &b);
    printf("Enter c: ");
    scanf("%f", &c);

    d = b * b - 4 * a * c;

    if (d == 0)
    {
        printf("\n One root: %f", (-b) / (2 * a));
    }
    else if (d > 0)
    {
        d = sqrt(d);
        printf("\n Two roots: %f, %f", (-b + d) / (2 * a), (-b - d) / (2 * a));
    }
    else
    {
        d = sqrt(-d);
        printf("\n Two roots: %f-%fi, %f+%fi", (-b) / (2 * a), d / (2 * a), (-b) / (2 * a), d / (2 * a));
    }
    printf("\n");
    return 0;
}