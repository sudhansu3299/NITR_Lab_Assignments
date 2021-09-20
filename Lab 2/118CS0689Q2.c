#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int fwd[2];
char line[20];
char result[20];

void processChain(int number,int count,int num){
    if(number<=count){
        num++;
        printf("%d\n",num);
        return;
    }else{
        pipe(fwd);
        if(fork()==0){
            close(fwd[1]);
            read(fwd[0],line,20);
            processChain(number,count+1,atoi(line));
        }else{
           close(fwd[0]);
           num++;
           sprintf(result, "%d", num);
            write(fwd[1],result,20);
            wait(NULL);
            exit(0);
        }
    }
}
int main(){
	
    int num,input;
    printf("Enter number of process: ");
    scanf("%d",&num);
    printf("Enter input number: ");
    scanf("%d",&input);
    
    processChain(num,1,input);
    return 0;
}
