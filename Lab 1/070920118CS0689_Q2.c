#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int func(const char *ch) {
	
    printf("This is %s whose pid is:%d  and it's ppid is %d\n", ch, getpid(), getppid() );
    
    return 1;
}


int chain(int n) 
{
    if (n == 0)
    { 
        return 0;
    }
    
    int pid = fork();
	 
    if (pid == -1) {
        exit(0);
    }
    
    if (pid==0) { 
        func("child process");
        n = n-1;
        chain(n);//recursive call for chain formation
        
        exit(0);
    }
    else {
       wait(NULL);
    } 
    
    return 0;   
}


int main(){
	
int n;
scanf("%d",&n);
chain(n);

return 0 ;
}#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int func(const char *ch) {
	
    printf("This is %s whose pid is:%d  and it's ppid is %d\n", ch, getpid(), getppid() );
    
    return 1;
}


int chain(int n) 
{
    if (n == 0)
    { 
        return 0;
    }
    
    int pid = fork();
	 
    if (pid == -1) {
        exit(0);
    }
    
    if (pid==0) { 
        func("child process");
        n = n-1;
        chain(n);//recursive call for chain formation
        
        exit(0);
    }
    else {
       wait(NULL);
    } 
    
    return 0;   
}


int main(){
	
int n;
scanf("%d",&n);
chain(n);

return 0 ;
}
