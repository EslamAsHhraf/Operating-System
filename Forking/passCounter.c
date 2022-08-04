#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int* create_grade(FILE * File, int n)
{
    int g1,g2,i=0;
    int* temp= malloc(n* sizeof(int));
    while(!feof (File))
    {
         fscanf(File, "%d %d", &g1, &g2);
         temp[i]=g1+g2;
         i++;
    }
    return temp;
}
int main(int argc, char **argv) {
   FILE* ptr;
   int * grades;
   int pid,n,i,j=0,count=0,collection,status,t,end=0;
	if (argc<4) {
		printf("Too few arguments. Exiting!\n");
		exit(1);
	}
    char *file =  argv[1];
    int num_TA =  atoi(argv[2]);
    int Pass_Garde= atoi(argv[3]);
    ptr = fopen(file, "r");
    fscanf (ptr, "%d", &n);
    collection = n / num_TA;
    grades= create_grade(ptr,  n);
    int * child=malloc( num_TA*sizeof(int));
  for(i=0;i<(num_TA);i++)
  {
       child[i] = fork();
        if (  child[i]  == -1) {
            printf("Error with creating process\n");
            return 2;
        }
        if(child[i] ==0)
        {
             j=i*collection;
            if(i==(num_TA-1))
            {
             end = n;
            }
            else
                end+=collection;
            break;
        }
        end+=collection;
  }

    if(i==num_TA)
    {
        for(i=0;i<(num_TA);i++)
        {
            waitpid( child[i] ,&status,0);
                if(WIFEXITED(status));
                    printf("%d ", WEXITSTATUS(status));

        }
    }
    else{
          for (j; j <end ;j++)
            {
                if(grades[j]>=Pass_Garde)
                    count++;
            }
            exit(count);
    }
    free(grades);
    printf("\n");
    fclose (ptr);
    return 0;
}
