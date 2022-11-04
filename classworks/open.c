#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define N 1024

int readline(char* buf, int fd)
{
    char c;
    read(fd, &c, 1);
    int flag = 0;
    while ((c != '\n') && ( c != '\0'))
    {
        
        flag = 1;//printf("%c", c);
        //fflush(stdout);
        *buf = c;
        buf++;
        read(fd, &c, 1);
    }
    *buf = '\n';
    buf++;
    *buf = '\0';
    return flag ;
}

int main(int argc, char** argv)
{
    int f, f1, f2;
    f = open(argv[1], O_RDONLY, 0666);
    f1 = open(argv[2], O_RDWR | O_CREAT, 0666);
    f2 = open(argv[3], O_RDWR | O_CREAT, 0666);
    char buf[N];
    int res;
    for (int i = 0; i < 3; i++)
    {
        readline(buf, f);
        //printf("%s\n", buf);
        write(f1, buf, strlen(buf));
    }
    while ((res = readline(buf, f)) != 0)
    {
        
        write(f2, buf, strlen(buf));
        //readline(buf, f);
    }
}
