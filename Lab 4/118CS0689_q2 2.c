#include <pthread.h> 
#include<stdio.h>
#include<stdlib.h>

#define MAX 4 
#define MAX_THREAD 4 

int matA[MAX][MAX],matB[MAX][MAX],matC[MAX][MAX]; 
int step_count = 0; 

void* multi(void* arg) 
{ 

    int curr = step_count++;
	int i,j,k; 
    for (i = curr * MAX / 4; i < (curr + 1) * MAX / 4; i++) 
        for (j = 0; j < MAX; j++)  
            for (k = 0; k < MAX; k++)  
                matC[i][j] += matA[i][k] * matB[k][j]; 
} 

  
int main() 
{ 

    
    int i,j;
    for (i = 0; i < MAX; i++) { 
        for (j = 0; j < MAX; j++) { 
            matA[i][j] = rand() % 10; 
            matB[i][j] = rand() % 10; 
        } 

    } 
    printf("\n matrix A:\n");
    for (i = 0; i < MAX; i++) { 
        for (j = 0; j < MAX; j++)  
            printf("%d ",matA[i][j]);
        printf("\n");
    } 

  

    printf("\n matrix B:\n");
    for (i = 0; i < MAX; i++) { 
        for (j = 0; j < MAX; j++)  
            printf("%d ",matB[i][j]);
        printf("\n");
    } 
    
    pthread_t threads[MAX_THREAD]; 

    for (i = 0; i < MAX_THREAD; i++) { 

        int* p; 

        pthread_create(&threads[i], NULL, multi, (void*)(p)); 

    } 
    for (i = 0; i < MAX_THREAD; i++)  

        pthread_join(threads[i], NULL);     

  

    printf("\n A X B: \n");
    for (i = 0; i < MAX; i++) { 
        for (j = 0; j < MAX; j++)  
            printf("%d ",matC[i][j]);
        printf("\n");
    } 


    return 0; 
} 
 
