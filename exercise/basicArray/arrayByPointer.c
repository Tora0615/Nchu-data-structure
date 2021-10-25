#include <stdio.h>
#include <stdlib.h>
#define ROW 10
#define COL 10


int main(int argc, char const *argv[]) {

  // 以一維陣列儲存二維陣列
  int *p = (int*) malloc (ROW * COL * sizeof(int));
  if (!p){
    printf("memory allocation failed\n");
    exit(1);
  }

  int i;
  int j;
  int count = 0;
  for (int i=0;i<ROW;i++){
    for (int j=0;j<COL;j++){
      *(p + i*ROW + j) = count;
      count++;
    }
  }

  for (int i=0;i<ROW;i++){
    for (int j=0;j<COL;j++){
      printf("%d\t", *(p + i*ROW + j));
    }
    printf("\n");
  }


  // 以指標陣列的每個元素指向數個一維陣列的起始位置
  // 待補
  // int **ptrArr = (int **) malloc (sizeof(int*) * ROW);
  // for (int i = 0; i<ROW; i++){
  //   *(ptrArr+i) = (int *) malloc (sizeof(int) * COL);
  // }

  return 0;
}
