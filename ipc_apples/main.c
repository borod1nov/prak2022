#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#define NMAX 20

struct sembuf up = {0, 1, 0};
struct sembuf down = {0, -1, 0};

void play()
{
    srand(time(NULL) + getpid());
    sleep(2 + rand() % 5);
}

void take_apple(char* addr, int semid)
{
    int i = 0;
    semop(semid, &down, 1);
    while (addr[i] == 0)
        i++;
    addr[i] = 0;
    printf("Child %d takes an apple\n", getpid());
    semop(semid, &up, 1);
    fflush(stdout);
}

void init_addr(char* addr)
{
    for (int i = 0; i < NMAX; i++)
        addr[i] = 0;
}

int is_empty(char* addr)
{
    for (int i = 0; i < NMAX; i++)
    {
        if (addr[i] != 0)
            return 0;
    }
    return 1;
}

void put_apples(char* addr, int semid)
{
    srand(time(NULL));
    int num_of_apples = 1 + rand() % 5;
    semop(semid, &down, 1);
    for (int i = 0; i < num_of_apples; i++)
    {
        addr[i] = 'a';
    }
    printf("Mother puts %d apples\n", num_of_apples);
    semop(semid, &up, 1);
}

int main(int argc, char** argv)
{
    int n, max_time, shmid, semid, parent_pid;
    n = atoi(argv[1]);
    max_time = atoi(argv[2]);
    parent_pid = getpid();
    int pids[n];

    key_t key = ftok("/usr", 0);

    semid = semget(key, 1, 0666 | IPC_CREAT);
    semctl(semid,0,SETVAL, (int) 1);

    shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
    char* addr = shmat(shmid, NULL, 0);

    init_addr(addr);
    put_apples(addr, semid);
    for (int i = 0; i < n; i++)
    {
        if (parent_pid == getpid())
        {
            int pid = fork();
            if (pid > 0)
            {
                pids[i] = pid;
            }
            else
            {
                while(1)
                {
                    play();
                    if (!is_empty(addr))
                        take_apple(addr, semid);
                }
            }
        }
    }

    time_t start_time = time(NULL);
    time_t curr_time = time(NULL);
    while (difftime(curr_time, start_time) < max_time)
    {
        usleep(1000);
        if (is_empty(addr))
        {
            put_apples(addr, semid);
        }
        curr_time = time(NULL);
    }

    for (int i = 0; i < n; i++)
    {
        kill(pids[i], SIGKILL);
        printf("Child %d has finished playing\n", pids[i]);
    }

    printf("Mother has finished playing\n");
    semctl(semid, 0, IPC_RMID, (int) 0);
    shmdt(addr);
    shmctl(shmid, IPC_RMID, NULL);
}
