#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{


    int rc=fork();

    if (rc<0) // fork failed
    {
        fprintf(stderr, "fork failed\n");
        exit(1);

    }

    else if (rc==0) // child process
    {

        printf("Please enter your command line as you would normally do in UNIX terminal \n");
        char *args[6];

        char temp[256];
        scanf("%[^\n]s",temp);//scan til new line is detected

        char* token = strtok(temp, " "); // extract cmd
	    int i=0;
        while (token != NULL) // seperating arguments from entered string
            {
            args[i++] = token;
            token = strtok(NULL, " ");// keep extracting
            }

        args[i] = NULL; // // make last elem of array null for execvp to work 


        execvp(args[0], args);
        printf("I didn't find command called %s\n", args[0] );
    }
    else
    {

        wait(NULL);// ensuring child gets executed before parent
        printf("+++++++++++ \n");
    }

	return 0;
}
