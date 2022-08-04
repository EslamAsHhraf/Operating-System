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
struct msgbuff
{
    long mtype;
    char mtext[256];
    long id;
};
      int up, send_val,rec_val,down;
int main()
{
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
    struct msgbuff message,message2;
  message.mtype = getpid()%10000; 
  message.id=getpid();

    while(1)
    {
    char str[256];
    scanf("%[^\n]%*c", str);
    strcpy(message.mtext, str);
memset(str, 0, sizeof (str));
    send_val = msgsnd(up, &message, sizeof(message),!IPC_NOWAIT);

    if (send_val == -1)
        {
            perror("Errror in send");
         exit(-1);
        }

        rec_val = msgrcv(up, &message, sizeof(message),  message.mtype, !IPC_NOWAIT);
         if (rec_val == -1)
        {
            perror("Error in receive");
             exit(-1);
        }
        printf("\nMessage reverse: %s\n", message.mtext);
      memset(message2.mtext, 0, sizeof (message2.mtext));
      memset(message.mtext, 0, sizeof (message.mtext));
    }

    return 0;
}