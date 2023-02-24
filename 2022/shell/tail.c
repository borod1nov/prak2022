#include <stdio.h>
#include <stdlib.h>
#define N 10

int main(int argc,char **argv) 
{
    FILE* f;
    char* p;
    char s[100];
    int n = N, npos = 0, pos = 0;
    int* a = 0;
    if  (argc <= 1)
    {
        printf("Error: enter filename\n");
        return 0;
    }
    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Error: cannot open file\n");
        return 0;
    }
    while(fgets(s, 100, f))
    {
        a = (int*)realloc(a, (npos + 1) * sizeof(int));
        a[npos] = pos;
        npos++;
        pos = ftell(f);
    }
    if(n > npos)
        n = npos;
    fseek(f, a[npos - n], SEEK_SET);
    while(fgets(s, 100, f))
    {
        printf("%s", s);
    }
    fclose(f);
    free(a);
    return 0;
}