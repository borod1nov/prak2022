#include <stdio.h>
#include <stdlib.h>

int packer(char* srcfilename, char* dstfilename)
{
    FILE* src = fopen(srcfilename, "r");
    FILE* dst = fopen(dstfilename, "w");
    char c;
    char prev = -1;
    int count = 0;
    while ((c = getc(src)) != EOF)
    {
        if (c != prev)
        {
            
            if (prev != -1)
            {
                if (count > 1)
                {
                    putc(-count, dst);
                }
                putc(prev, dst);
            }
            count = 1;
            prev = c;
        }
        else
        {
            count+= 1;
        }
    }
    fclose(src);
    fclose(dst);
}

int unpacker(char* srcfilename, char* dstfilename)
{
    FILE* src = fopen(srcfilename, "r");
    FILE* dst = fopen(dstfilename, "w");
    char c;
    int count = 1;
    while ((c = getc(src)) != EOF)
    {
        if (c > 0)
        {
            printf("%c %d\n", c, count);
            for (int i = 0; i < count; i++)
                putc(c, dst);
            count = 1;
        }
        else
        {
            count = -c;
        }


    }
    fclose(src);
    fclose(dst);
}

int main()
{
    packer("input.txt", "packed.txt");
    unpacker("packed.txt", "output.txt");
    return 0;
}