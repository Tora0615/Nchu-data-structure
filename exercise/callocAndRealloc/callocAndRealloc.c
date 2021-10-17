#include <stdlib.h>
#include <stdio.h>

int main(){

  // malloc
  int *i;
  i = (int*)malloc(sizeof(int)*2);
  printf("malloc 後沒給初值 -> 印出雜值\n");
  printf("array[0] : %d \n",*(i+0) );
  printf("array[1] : %d \n",*(i+1) );

  // calloc is for array
  // usage : 指標變數  = calloc(陣列大小 , sizeof(資料型態))
  int *j;
  j = calloc(2, sizeof(int));
  printf("calloc 後沒給初值 -> 印出 0 值\n");
  printf("array[0] : %d\n",*(j+0));
  printf("array[1] : %d\n",*(j+1));

  // realloc is also for array
  // usage : 原指標變數  = realloc(原指標變數 , sizeof(資料型態))
  // size : new > old --> 擴大 / new < old --> 呼叫 free 縮小
  *(j+0) = 1;
  *(j+1) = 2;
  j = realloc(j, 4*sizeof(int));
  printf("array[0-1] 有初值，其他 realloc 後沒給初值\n");
  printf("array[0] : %d\n",*(j+0));
  printf("array[1] : %d\n",*(j+1));
  printf("array[2] : %d\n",*(j+2));
  printf("array[3] : %d\n",*(j+3));

  return 0;
}
