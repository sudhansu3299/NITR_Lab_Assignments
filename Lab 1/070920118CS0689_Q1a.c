#include <stdio.h>
#include <unistd.h>

int main()
{

    
	printf("prog starts here:\n");
    int counter = 0;
    pid_t pid = fork();
    
	// child process begins here
    if (pid == 0)
    {
        
        int i = 0;
        for (; i < 3; ++i)
        {	
        	counter++;
            printf("child counter=%d\n", counter);
        }
    }// child ends here and parent process begins here
    else if (pid > 0)
    {

        int j = 0;
        for (; j < 3; ++j)
        {
        	counter++;
            printf("parent counter=%d\n", counter);
        }
    }
    else
    {
        // fork() failed
        printf("forking failed\n");
        return 1;
    }
    printf("prog ends here:\n");

    return 0;
}
