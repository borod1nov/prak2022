#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        pid = fork();
        if (pid == 0)
        {
            //grandchild
            printf("3 pid %d ppid %d\n", getpid(), getppid());
        }
        else
        {
            //child
            wait(NULL);
            printf("2 pid %d ppid %d\n", getpid(), getppid());
        }
        
    }
    else
    {
        //parent
        wait(NULL);
        printf("1 pid %d ppid %d\n", getpid(), getppid());
    }
    return 0;
}
