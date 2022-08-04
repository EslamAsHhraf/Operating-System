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

char* message,*message2;
int  sem1,sem2,shmid,sem3;
void writer()
{
   
    message = shmat(shmid, (void *)0, 0);
    if (message == -1)
    {
        perror("Error in attach write Client\n");
        exit(-1);
    }
    char str[256];
    scanf("%[^\n]%*c", str);
   
    down(sem3);
    printf("Start\n");
    strcpy(message, str);
    memset(str, 0, sizeof (str));
     shmdt(message);
      up(sem1);
}

void reader()
{
    down(sem2);
    message = shmat(shmid, (void *)0, 0);
    if (message == -1)
    {
        perror("Error in attach in read client");
        return;
    }
    printf("\nMessage reverse: %s\n", message);
    memset(message, 0, sizeof (message));
    shmdt(message);
}

int main()
{
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


    while(1){
         
        writer();
        reader();
          up(sem3);   
    }
  
    return 0;
}
