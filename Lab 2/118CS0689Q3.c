#include <stdio.h> 
#include <stdlib.h>  
#include <unistd.h>  
#include <errno.h>   
#include <sys/types.h>
#include <sys/wait.h> 


char*args[]= {"/bin/ls",NULL};
int main(){
    int x = 9;
    if(fork()>0){
        wait(NULL);
    }else{
        execv("/bin/ls",args);
        exit(1);
        printf("%d\n",x); // This should not run as the address space is changed
    }
    
}
