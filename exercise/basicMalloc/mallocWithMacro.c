#include <stdio.h>
#include <stdlib.h>
#define MALLOC(ptrVar,size){ \
  if(!(ptrVar = malloc(size))){ \
    printf("malloc failed\n"); \
    exit(EXIT_FAILURE); \
  } \
}



int main(int argc, char const *argv[]) {
  int *intptr;
  float *floatptr;

  // 動態記憶體配置
  MALLOC(intptr,sizeof(int));
  MALLOC(floatptr,sizeof(float));

  // 賦值
  *intptr = 1234;
  *floatptr = 12.34;

  printf("malloc with Macro called\n");
  printf("int : %d\n", *intptr);
  printf("float : %f\n", *floatptr);

  // 釋放記憶體
  free(intptr);
  free(floatptr);
  return 0;
}
