#include <stdio.h>
#include <stdlib.h>


// 稍微進階的 malloc，在無法指派記憶體時會顯示錯誤

int main(int argc, char const *argv[]) {
  //宣告變數與對應型態的指標變數
  int *intptr;
  float *floatptr;

  // 動態記憶體配置 + malloc 偵測 - A
  if((intptr = (int *)malloc(sizeof(int))) == NULL ||
  (floatptr = (float *)malloc(sizeof(float))) == NULL){
    printf("malloc failed\n");
    // 程式退出執行
    exit(EXIT_FAILURE);
    // EXIT_SUCCESS 為 0 ; EXIT_FAILURE 為 1
  }

  // 動態記憶體配置 + malloc 偵測 - B
  // 另一種寫法
  // if(!(intptr = (int *)malloc(sizeof(int))) ||
  // !( floatptr = (float *)malloc(sizeof(float)) ) ){
  //   printf("malloc failed\n");
  //   exit(EXIT_FAILURE);
  // }

  // 賦值
  *intptr = 1234;
  *floatptr = 12.34;

  printf("basic malloc called\n");
  printf("int : %d\n", *intptr);
  printf("float : %f\n", *floatptr);

  // 釋放記憶體
  free(intptr);
  free(floatptr);
  return 0;
}
