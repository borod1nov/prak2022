#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// pr1 < f1.dat | pr2 > f2.dat && pr3
//argv: [pr1, pr1.dat, pr2, f2.dat. pr3]
   
int main(int argc, char *argv[])
{
    pid_t pr1, pr2, pr3;
    int status;
    int fd[2];
    pipe(fd);
    pr1 = fork();
    if(pr1 == 0)
    {
        int f1 = open("f1.dat", O_RDONLY);
        dup2(f1, 0);
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        close(f1);
        execlp(argv[1], argv[1], (char*)0);
        exit(1);
    }
    pr2 = fork();
    if(pr2 == 0)
    {
        int f2 = open(argv[4], O_WRONLY | O_CREAT, 0666);
        dup2(fd[0], 0);
        dup2(f2, 1);
        close(f2);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[3], argv[3], (char*)0);
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pr2, &status, 0);
    wait(NULL);
    if(WIFEXITED(status) && (WEXITSTATUS(status) == 0))
    {
        pr3 = fork();
        if(pr3 == 0)
        {
            execlp(argv[5], argv[5], (char*)0);
            exit(1);
        }
        wait(NULL);
    }
    exit(0);
}
