#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int reverse(int num){
    int rev = 0;
    while(num>0){
        rev = rev*10 + num%10;
        num/=10;
    }
    return rev;
}

void concat(char*s,int addd){
    int n = strlen(s);
    int i = n;
    addd = reverse(addd);
    while(addd>0){
        s[i++] = (addd%10+'0');
        addd/=10;
    }
    s[i] = '\0';
}

int main(){
    int fwd[2];
    pipe(fwd);
    char s[100] = "Hello ";
    pid_t pid = fork();
    
    if(pid > 0){
        concat(s,pid);
        write(fwd[1],s,sizeof(s));
        
        wait(NULL);
        char aux[100];
        read(fwd[0],aux,sizeof(aux));
        printf("%s\n",aux);
    }else{
    
        char aux[100];  
        read(fwd[0],aux,sizeof(aux));

        printf("%s\n",aux);
        concat(s,getppid());
        write(fwd[1],s,sizeof(s));
        exit(1);
    }
}
