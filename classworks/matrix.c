#include <stdio.h>
#include <stdlib.h>

double **transm(double** a, int m, int n)
{
    double** transp = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
        transp[i] = (double*)malloc(m * sizeof(double));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            transp[i][j] = a[j][i];
    return transp;
}

double **transm(double** a, int m, int n)
{
    
}

void printm(double** a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%lf ", a[i][j]);
        printf("\n");
    }
}

void main()
{
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    double** a = (double**)malloc(m * sizeof(double*));
    for (int i = 0; i < m; i++)
        a[i] = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &a[i][j]);
    double** b = transm(a, m, n);
    printm(b, n, m);
    for (int i = 0; i < m; i++)
        free(a[i]);
    free(a);
    for (int i = 0; i < n; i++)
        free(b[i]);
    free(b);
}
