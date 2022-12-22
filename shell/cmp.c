#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv) 
{
    FILE* f;
    char* p;
    char c1;
    char c2;
    int linepos, nline;
    if (argc <= 2)
    {
        printf("Error: enter 2 filenames\n");
        return 0;
    }
    if (argc > 3)
    {
        printf("Error: too many arguments\n");
        return 0;
    }
    FILE* f1 = fopen(argv[1], "r");
    FILE* f2 = fopen(argv[2], "r");
    if ((f1 == NULL) || (f2 == NULL))
    {
        printf("Error: cannot open file\n");
        return 0;
    }
    c1 = fgetc(f1);
    c2 = fgetc(f2);
    linepos = 1;
    nline = 1;
    while ((c1 != EOF) && (c2 != EOF) && (c1 == c2))
    {
        if (c1 == '\n')
            nline++;
        linepos++;
        c1 = fgetc(f1);
        c2 = fgetc(f2);
    }
    if (c1 != c2)
        printf("%s differs from %s: line %d char %d\n", argv[1], argv[2], nline, linepos);
    fclose(f1);
    fclose(f2);
    return 0;
}