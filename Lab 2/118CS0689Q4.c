#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include<errno.h> 
#include<sys/wait.h> 

int main(){ 
    
    int arr[2]; 
  
    // using pipe for IPC 
    pipe(arr); 
  
    if(!fork()) 
    { 
        
        close(1); 
        dup(arr[1]); 
        close(arr[0]); 
		 
        execlp("ls","ls",NULL); 
    } 
    else
    { 
         
        close(0); 
        dup(arr[0]); 
        close(arr[1]); 
          
        // wc execution
        execlp("wc","wc",NULL); 
    } 
} 
