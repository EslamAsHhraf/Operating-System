 
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
void handler(int signum);
int * child;
int main(int argc, char **argv) {
    int i=0,j=0,end=0,status,pid;
	if (argc<1) {
		printf("Too few arguments. Exiting!\n");
		exit(1);
	}
	 signal( SIGUSR1, handler);
	int target=atoi(argv[1]);
	int * array= malloc((argc-2) * sizeof(int));
    int n=argc-2;
  for(i=0;i<n;i++)
  {
      array[i]=atoi(argv[i+2]);
  }
 printf("I am the parent, my pid = %d \n", getpid());
 child=malloc( 2*sizeof(int));
 for(i=0;i<2;i++)
  {
      child[i]=fork();
       if(child[i] ==0)
        {
            if(i==0)
            {
                printf("I am the first child, pid = %d ppid= %d \n", getpid(),getppid());
                end=ceil(n/2);
            }
            else
            {
                 printf("I am the second child, pid = %d ppid= %d \n", getpid(),getppid());
                j=ceil(n/2);
                end=n;
            }
            break;
        }
  }
   if(i==2)
     {
         sleep(5);
        for(i=0;i<2;i++)
        {
             waitpid( child[i] ,&status,0);
                if(WIFEXITED(status));
                    printf("A child with pid %d terminated with exit code %d\n", child[i], WEXITSTATUS(status));
        }
        printf("value not found \n");
     }
     else
     {
            for (j; j <end ;j++)
             {
                 if(array[j]==target)
                 {
                     kill(getppid(), SIGUSR1);
                      exit(j);
                 }
             }
             sleep(3);
           printf("Child %d terminates\n",i+1);
           exit(0);
     }
    return 0;
}
void handler(int signum)
{
int pid, stat_loc;
   pid = wait(&stat_loc);
 if(WIFEXITED(stat_loc))
 {
     if(pid==child[0])
         printf("child 1: value found at position %d\n", stat_loc>>8);
     else
        printf("child 2: value found at position %d\n", stat_loc>>8);

 killpg(getpgrp(), SIGKILL);

}
      void handler(int signum);
}
/* a) parent

b) becuse the child who found value sent signal and then sent exit and paretn wait exit code so it always handle

*/
