#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>
#include <math.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/sem.h>
union Semun
{
    int val;               /* value for SETVAL */
    struct semid_ds *buf;  /* buffer for IPC_STAT & IPC_SET */
    ushort *array;         /* array for GETALL & SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
    void *__pad;
};

void down(int sem)
{
    struct sembuf p_op;
    p_op.sem_num = 0;
    p_op.sem_op = -1;
    p_op.sem_flg = !IPC_NOWAIT;

    if (semop(sem, &p_op, 1) == -1)
    {
        perror("Error in down()");
        exit(-1);
    }
}

void up(int sem)
{
    struct sembuf v_op;
    v_op.sem_num = 0;
    v_op.sem_op = 1;
    v_op.sem_flg = !IPC_NOWAIT;

    if (semop(sem, &v_op, 1) == -1)
    {
        perror("Error in up()");
        exit(-1);
    }
}
void reverse(char* msg, char* reversed) {
int i;
for (i=0; i<strlen(msg); ++i)
reversed[i] = msg[strlen(msg) - i - 1];
}

void handler(int signum);
  char* message,*message2;
  int  sem1,sem2,shmid,sem3;
void writer()
{
      message= shmat(shmid, (void *)0, 0);
    if (message == -1)
    {
        perror("Error in attach in Server write");
        return;
    }
     char temp[256];
        reverse(message2,temp);
        message=  message2; 
        strcpy(message, temp);
         printf("Reverse massgae : %s\n",temp);
         memset(temp ,0, sizeof (temp));
         shmdt(message);
         up(sem2);
}

void reader()
{

     down(sem1);
   message= shmat(shmid, (void *)0, 0);
    if (message == -1)
    {
        perror("Error in attach in server read");
       return;
    }
        message2=  message; 
    shmdt(message);

}

int main()
{
      signal(SIGINT,handler);
    union Semun semun;
    union Semun semun2;
     key_t key_id1,s1,s2,s3;
    key_id1=ftok("keyfile",65);
    s1=ftok("keyfile",66);
    s2=ftok("keyfile",67);
    s3=ftok("keyfile",68);

   shmid=shmget(key_id1,257,IPC_CREAT|0666);
    if (shmid == -1 )
    {
        perror("Error in create");
        exit(-1);
    }
     sem1 = semget(s1, 1, 0666 | IPC_CREAT);
     sem2 = semget(s2, 1, 0666 | IPC_CREAT);
    sem3=semget(s3, 1, 0666 | IPC_CREAT);
    
    if (sem1 == -1 || sem2 == -1||sem3 == -1)
    {
        perror("Error in create Semaphores");
        exit(-1);
    }
    semun.val = 0; /* initial value of the semaphore, Binary semaphore */
    semun2.val = 1; /* initial value of the semaphore, Binary semaphore */
    if (semctl(sem1, 0, SETVAL, semun) == -1 || semctl(sem2, 0, SETVAL, semun) == -1 ||semctl(sem3, 0, SETVAL, semun2) == -1 )
    {
        perror("Error in semctl");
        exit(-1);
    }

    while(1){
        reader();
            writer();
    }
  
    return 0;
}

void handler(int signum)
{
    shmctl(shmid, IPC_RMID, (struct shmid_ds *)0);
    semctl(sem1,0,IPC_RMID,0);
    semctl(sem2,0,IPC_RMID,0);
     semctl(sem3,0,IPC_RMID,0);
    void handler(int signum);
    exit(0);
}
