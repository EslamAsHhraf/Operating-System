#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

#include <ctype.h>
#include <math.h>
void handler(int signum);
struct msgbuff
{
    long mtype;
    char mtext[256];
    long id;
};
void reverse(char* msg, char* reversed) {
int i;
for (i=0; i<strlen(msg); ++i)
reversed[i] = msg[strlen(msg) - i - 1];
}

  int up, send_val,rec_val,down;
     struct msgbuff message,message2;
int main()
{
    signal( SIGINT, handler);
    key_t key_id,key_id2;

      key_id = ftok("keyfile", 65);
    up = msgget(key_id, 0666 | IPC_CREAT);
     if (up == -1)
    {
        perror("Error in create");
        exit(-1);
    }
     key_id2 = ftok("keyfile", 65);
   down = msgget(key_id2, 0666 | IPC_CREAT);
    if (down == -1)
    {
        perror("Error in create");
        exit(-1);
    }
    while(1)
    {
        /* receive all types of messages */
        rec_val = msgrcv(up, &message, sizeof(message), 0, !IPC_NOWAIT);
         if (rec_val == -1)
        {
            perror("Error in receive");
            exit(-1);
        }

        char temp[256];
        reverse(message.mtext,temp);
        strcpy(message.mtext, temp);
         printf("Reverse massgae : %s\n",temp);
        message2.mtype =  message.mtype; 
        message2.id=message.id;
    send_val = msgsnd(up, &message, sizeof(message), !IPC_NOWAIT);
    if (send_val == -1)
        {
            perror("Errror in send");
        exit(-1);
        }
         memset(message2.mtext, 0, sizeof (message2.mtext));
    memset(message.mtext, 0, sizeof (message.mtext));
      memset(temp, 0, sizeof (temp));
    }
    return 0;
}

void handler(int signum)
{
    msgctl(up, IPC_RMID, (struct msqid_ds *)0);
    msgctl(down, IPC_RMID, (struct msqid_ds *)0);
     void handler(int signum);
    exit(0);
}
