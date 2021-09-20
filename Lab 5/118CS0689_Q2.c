#include <stdio.h> 
#include <pthread.h> 
#include<stdlib.h>
#define MAX 10 
#define THREAD_MAX 4 
int a[MAX]; 
int part = 0;
typedef struct dp0409{
	int low,high;
} limits;
void merge(int low, int mid, int high) { 
    int* left = (int*)malloc(sizeof(int)*(mid - low + 1)); 
    int* right = (int*)malloc(sizeof(int)*(high-mid));
	int n1 = mid - low + 1, n2 = high - mid, i, j; 
	for (i = 0; i < n1; i++) 
        left[i] = a[i + low]; 
  	for (i = 0; i < n2; i++) 
        right[i] = a[i + mid + 1]; 
  
    int k = low; 
    i = j = 0; 
  	while (i < n1 && j < n2) { 
        if (left[i] <= right[j]) 
            a[k++] = left[i++]; 
        else
            a[k++] = right[j++]; 
    }
	while (i < n1) { 
        a[k++] = left[i++]; 
    } 
  	while (j < n2) { 
        a[k++] = right[j++]; 
    } 
}   
void sort(void* limita){
	limits* limit = (limits*)limita;
	int low = limit->low;
	int high = limit->high;
	if(low>=high)
		return;
	pthread_t left_thread,right_thread;	
	limits* left_limit = (limits*)malloc(sizeof(limits));
	limits* right_limit = (limits*)malloc(sizeof(limits));
	int mid = (low+high)/2;
	left_limit->low = low;
	right_limit->high = high;
	left_limit->high = mid;
	right_limit->low = mid+1;
	pthread_create(&left_thread,NULL,sort,(void*)left_limit);
	pthread_create(&right_thread,NULL,sort,(void*)right_limit);
	pthread_join(left_thread,NULL);
	pthread_join(right_thread,NULL);
	merge(low,mid,high);
	
}
int main(){
	int i;
	for(i=0;i<MAX;i++)
		scanf("%d",&a[i]);
	limits* limit = (limits*)malloc(sizeof(limits));
	limit->high = MAX-1;
	limit->low = 0;
	sort(limit);
	for(i=0;i<MAX;i++)
		printf("%d ",a[i]);
	printf("\n");
}