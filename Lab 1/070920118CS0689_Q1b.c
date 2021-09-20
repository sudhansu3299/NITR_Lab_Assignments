#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


int global;
void func(pid_t pid){
    if(pid == 0){
        printf("func() called from child\n");
    }else if(pid>=0){
        printf("func() called from parent\n");
    }
}
int main(){
	
	global = 500;
    int local=10;
    
    pid_t child = fork();
    func(child);
    
    if(child >= 0){ 
		// parent process
        printf("local variable value in parent: %d and global var value: %d\n",local,global);
    }else if(child == 0){ 
		// child Process
        printf("local variable value in child: %d and global var value: %d\n",local,global);
    }else{
        //fork() didn't happen
        printf("Forking failed...");
    }
    
}
