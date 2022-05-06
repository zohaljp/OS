#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
int main (int argc, char *argv[])
{
	printf("Please enter your command line as you would normally do in UNIX terminal \n");

        char temp[256];
        char* args1[8];// argument array for first exec call
        char* args2[8];// argument array for 2nd exec call
        scanf("%[^\n]s",temp);// scan input
        

        char* part1=strtok(temp,"|"); // input before the "|" 
        char* part2=strtok(NULL, "\n"); // input after the "|"
       

        // we need to adjust part 1 and part 2 and insert them as arguments in the argument arrays to accommodate for spaces
        // this was not specified in the assignment, but the unix bash terminal behaves this way and we are asked to mimic its behavior
        int i =0;
        int j=0;
        char space[] = " ";
        char *chlada = strtok(part1, space); // extract first element
        while(chlada != NULL)
        {
            args1[i++] = chlada;

            chlada = strtok(NULL, space); // keep tokening until we finish the input
        }
        args1[i] = NULL; // terminate array of arguments
        // now we have all the arguments for the first exec which is going to be execvp



        char *chlada1 = strtok(part2, space); // same as  above for part 2 to be arguments for args2


        while(chlada1 != NULL) // same as  above for part 2 to be arguments for args2
        {
            args2[j++] = chlada1; 

            chlada1 = strtok(NULL, space);
        }
        args2[j] = NULL; // same as  above for part 2 to be arguments for args2

        // now we can open a pipe and fork processes to mimic the behavior of the operator "|"

        int fd[2];// fd[0] is for reading from the pipe and fd[1] s for writing

        if(pipe(fd) == -1)
        {
            printf("pipe failed");
            exit(1);
        }

        int rc=fork();

        if (rc<0) // fork failed
        {
            fprintf(stderr, " 1st fork failed\n");
            exit(1);

        }

        else if (rc==0) // 1st child process- the one that will give its output as input for the second command
        {

            dup2(fd[1], STDOUT_FILENO); // redirect output to point to pipe and write in pipe
            close(fd[0]);
            close(fd[1]);

            execvp(args1[0], args1);

        }

        int rc2=fork(); // second fork


        if(rc2 <0)
        {
            fprintf(stderr, " 2nd fork failed\n");
            exit(1);

        }


        else if(rc2 == 0) // second fork is succesful
        {
            dup2(fd[0], STDIN_FILENO); // allow reading from pipe
            close(fd[0]); 
            close(fd[1]);
            execvp(args2[0], args2); 
        }


        else // parent process 
        {
        
            close(fd[0]);
            close(fd[1]);
            wait(NULL);//
            wait(NULL);
            printf("+++++++++++ \n");
        }


   return 0;
}