#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define ROWS 5
#define COLS 4

int matA[ROWS][COLS];
int matB[ROWS][COLS];
int sum[ROWS][COLS];

pthread_t threads[ROWS];

void* add_matrices(void *thread_number){
    int row = (int)thread_number;
    int col;
    for(col=0;col<COLS;col++)
        sum[row][col] = matA[row][col] +  matB[row][col];
}

int main(){
    int thread_num = 0;
    int i,j;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++){
            matA[i][j] = rand()%11;
            matB[i][j] = rand()%11;
        }
    }
    printf("first matrix:\n");
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++)
            printf("%d ",matA[i][j]);
        printf("\n");
    }
    printf("second matrix:\n");
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++)
            printf("%d ",matB[i][j]);
        printf("\n");
    }
    for(i=0;i<ROWS;i++){
        pthread_create(&threads[i],NULL,&add_matrices,(void*)thread_num);
        thread_num++;
    }
    for(i=0;i<ROWS;i++)
        pthread_join(threads[i],NULL);
        
    printf("first+second matrix:\n");
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++)
            printf("%d ",sum[i][j]);
        printf("\n");
    }
}
