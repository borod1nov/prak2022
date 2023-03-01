#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 7

int chpids[N];
int fd[2];

void handler1(int s)
{
    int mypid = getpid();
    printf("%d got SIGUSR1\n", mypid);
    write(fd[1], &mypid, sizeof(int));
    kill(getppid(), SIGUSR2);
    close(fd[0]);
    close(fd[1]);
    exit(1);
}

void handler2(int s)
{
    int chpid;
    read(fd[0], &chpid, sizeof(int));
    printf("got SIGUSR2 from %d\n", chpid);
    for (int i = 0; i < N; i++)
        if (chpids[i] == chpid) 
            chpids[i] = 0;
}

int sum(int* a)
{
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans+= a[i];
    }
    return ans;
}

int main()
{
    int parent = getpid();
    for (int i = 0; i < N; i++)
    {
        if (getpid() == parent)
        {
            pipe(fd);
            int pid = fork();
            if (pid == 0)
            {
                //child
                signal(SIGUSR1, handler1);
                int mypid = getpid();
                write(fd[1], &mypid, sizeof(int));
                for(;;);
            }
            else
            {
                //parent
                int chpid = getpid();
                read(fd[0], &chpid, sizeof(int));
                chpids[i] = chpid;
            }
        }
    }
    signal(SIGUSR2, handler2);
    for (int i = 0; i < N; i++)
    {
        //printf("sent: %d\n", chpids[i]);
        kill(chpids[i], SIGUSR1);
    }
    while (sum(chpids))
    {
        ;
    }
    for (int i = 0; i < N; i++)
    {
        printf("%d ", chpids[i]);
    }
    return 0;
}
