#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv) 
{
    FILE* f;
    char* p;
    char c;
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
    FILE* f2 = fopen(argv[2], "w");
    if ((f1 == NULL) || (f2 == NULL))
    {
        printf("Error: cannot open file\n");
        return 0;
    }
    c = fgetc(f1);
    while(c != EOF)
    {
        fputc(c, f2);
        c = fgetc(f1);
    }
    fclose(f1);
    fclose(f2);
    return 0;
}