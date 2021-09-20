#include <stdio.h> 
#include <pthread.h> 
int n= 2;
int flag[2];
int turn; 
const int MAX = 100; 
int ans = 0; 

void lock_init() { 
	int i;
	for(i=0;i<n;i++){
		flag[i] = 0;	
	} 
	turn = 0; 
} 
void lock(int self) { 
	if(self <=n-1 && self >=0)
	{
		flag[self] = 1;
	} 

	turn = n-self; 
	if(n-1-self != self)
	{
		while (flag[n-1-self]==1 && turn==n-self) ; 

	}	
	else if(n-2-self >= 0)
	{
		while (flag[n-2-self]==1 && turn==n-self) ;
	}
} 
void unlock_thread(int self) { 
	if(self <=n && self >=0)
	{
		flag[self] = 0;
	}
} 
void* func(void *s) 
{ 
	int i = 0; 
	int self = (int*)s;
 

	lock(self); 	
	printf("Thread Entered: %d\n", self); 
	
	for (i=0; i<MAX; i++) 
		ans++; 
	
	unlock_thread(self); 
} 

int main() 
{  
	pthread_t threads[n];
	lock_init(); 
	
	void *retvals[n];
    printf("\n\n\n\n");
	int count;
	for (count = 0; count < n; count++)
	{
		if (pthread_create(&threads[count], NULL,func,(void*)count) != 0){}
	}
	for (count = 0; count < n; count++){
		if (pthread_join(threads[count], &retvals[count]) != 0){}
	}
	printf("Ans variable after each thread: %d | Ans should be : %d\n", ans, MAX*n); 

	return 0; 
} 