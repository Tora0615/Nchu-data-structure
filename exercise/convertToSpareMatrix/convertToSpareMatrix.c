#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define ROW 4
#define COL 4

int array[ROW * COL] = {0,0,1,0,1,0,1,1,0,1,0,1,1,1,0,1};

// 印出 array
void printArr (int* arr, int row, int col){
  int i,j ;
  for (i = 0; i < row; i++) {
    for(j = 0; j < col; j++){
      printf("%d\t", *(arr + i*row + j) );
    }
    printf("\n");
  }
  printf("\n");
}

// 印出第一行的基本資訊 (row, col, value)
int getItemCount(int* arr, int row, int col){
  int count = 0;
  for (int i = 0; i < row*col; i++) {
    if( *(arr + i) == 1 ){
      count++;
    }
  }
  return count;
}

// 印出非零項的位置與值
void getItemPosition(int* arr, int row, int col){
  int count = 0, i=0, j=0;
  for (i = 0; i < row; i++) {
    for(j = 0; j < col; j++){
      if( *(arr + i*row + j) != 0 ){
        printf("arr[%d]\t%d\t%d\t%d\n", ++count, i, j, *(arr + i*row + j) );
      }
    }
  }
}

void toSpareMatrix (int* arr, int row, int col){
  printf("\trow\tcol\tvalue\n");
  printf("arr[0]\t%d\t%d\t%d\n",row,col,getItemCount(array,ROW,COL));
  getItemPosition(array,ROW,COL);
}

int main (void){
  printArr(array,ROW,COL);
  toSpareMatrix(array,ROW,COL);
  return 0;
}
