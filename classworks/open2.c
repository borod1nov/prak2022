#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define N 4

int readline(char* buf, int fd, int n)
{
    char c;
    int i = 0;
    int endofline = 0;
    int endflag = 1;
    while ((i < n) && (endflag > 0))
    {
        if (c == '\n')
        {
            endofline = 1;
            break;
        }
        endflag = read(fd, &c, sizeof(char));
        if (c != '\n')
        {
            buf[i] = c;
            i++;
        }
    }
    if (!endofline)
    {
        while ((c != '\n') && (endflag))
        {
            endflag = read(fd, &c, sizeof(char));
        }
    }
    buf[i] = '\0';
    return endflag;
}

int main(int argc, char** argv)
{
    int f, f1, f2;
    f1 = open("a.txt", O_RDONLY, 0666);
    f2 = open("b.txt", O_WRONLY |O_CREAT, 0666);
    char buf[N + 2];
    int res = 0;
    while ((res = readline(buf, f1, N)) > 0)
        printf("%s\n", buf);
        //write(f2, buf, N + 1);
    close(f1);
    close(f2);
}
