#include <stdio.h>
#include <stdlib.h>


// 最基礎的 malloc，沒有無法指派記憶體時的防呆

int main(int argc, char const *argv[]) {
  //宣告變數與對應型態的指標變數
  int *intptr;
  float *floatptr;

  // 動態記憶體配置
  intptr = (int *)malloc(sizeof(int));
  floatptr = (float *)malloc(sizeof(float));

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
