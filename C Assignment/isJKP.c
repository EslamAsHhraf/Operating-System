#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sol(char* s1, int n1,char* s2,int n2) {

    if(n1==n2)
        return 0;
    int temp = 0;
    for (int i = 0;i<n1; i++)
    {
        if(s1[i]==s2[temp])
            temp++;
        if(temp==n2)
            return 1;
    }

    return 0;
}

int main(int argc, char **argv) {
/*	argc: Number of arguments passed to the main from the terminal. 
	argv: The actual arguments passed to the main from the terminal. 
	For example: Suppose you want to run that toy example that adds three numbers. 
	However, you do not want these inputs to be supplied by the user using scanf at runtime.
	Instead you want to supply them from the terminal as follows:
	gcc example.c -o example
	./example 2 3 1 
 	 
	This run command "./example 2 3 1" will be passed as follows to the main function 
	int main(4, {"example", "2", "3", "1"})
	Here, argc is the number of parameters in argv. 
	argv[0] = "example" --> The name of the out file generated from the compile step. 
	argv[1] = "2" --> The first parameter. 
	argv[2] = "3" --> The second parameter. 
	argv[3] = "1" --> The third parameter. 

	The main function then should return 6 which is the addition of 2+3+1.
*/

	/* First, check the number of arguments */ 
	// Change this number according to the number of parameters you expect to receive. In this example, we expect to receive 4 parameters.
	if (argc<3) {	 
		printf("Too few arguments. Exiting!\n");
		exit(1);
	}
	
	/* We will pass argv[1], argv[2], argv[3] to the function compute. We usually ignore argv[0] unless we want to do something with the C-file name */
	/* Note that argv[1], argv[2] and argv[3] are strings. Therefore, we have to convert them to integers using (atoi) if we want to use them as integers. If we want to use them as strings, then you do not have to convert them */
    char *s1 =  (argv[1]);
    char *s2 =  (argv[2]);
    int n1 = strlen(s1);
    int n2 = strlen(s2);
    for(int i = 0; s1[i]; i++){
  s1[i] = tolower(s1[i]);
}
    for(int i = 0; s2[i]; i++){
  s2[i] = tolower(s2[i]);
}
    if(n1>n2)
        printf("%d\n", sol(s1,n1,s2,n2)); 
    else
        printf("%d\n", sol(s2, n2, s1, n1));
    return 0; 
}
