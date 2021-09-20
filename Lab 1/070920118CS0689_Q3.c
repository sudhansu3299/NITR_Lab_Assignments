#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>


void buildTree(int N,int D,int currHeight){
    if(currHeight >= D){
        return;
    }else{
        
        printf("The %d process is at height of %d whose parent is at %d\n",getpid(),currHeight ,getppid());   
        for(int i=0;i<N;i++){
            pid_t pid = fork();
            if(pid == 0){
            	
                //recursive function call
                buildTree(N,D,currHeight +1);       
            }
            else{
            	//process is waiting...
                waitpid(pid,0,0);
                exit(0);
            }
        }
    }
}
int main(){
    int N,D;    
    scanf("%d%d",&N,&D);
    buildTree(N,D,0);
}
