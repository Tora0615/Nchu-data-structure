#include <stdio.h>
#include <stdlib.h>
#define ROW 4
#define COL 4

int array[ROW*COL] = {0,0,1,0,1,0,1,1,0,1,0,1,1,1,0,1};

void printArr (int arr[], int row, int col){   // int* arr == int arr[]
  int i,j ;
  for (i = 0; i < row; i++) {
    for(j = 0; j < col; j++){
      printf("%d", *(arr + i*row + j) );
    }
    printf("\n");
  }
}

int main (void){
  printArr(array,ROW,COL);  // array 是直接傳位置 (一階指標)
  return 0;
}
