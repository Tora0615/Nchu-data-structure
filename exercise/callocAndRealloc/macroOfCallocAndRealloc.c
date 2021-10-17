#include <stdlib.h>
#include <stdio.h>

# define CALLOC(ptr, array_size ,sizeof_datatype){\
  if ( !( ptr = calloc(array_size, sizeof_datatype) ) ){\
    printf("Insufficient memory\n");\
    exit(EXIT_FAILURE);\
  }\
}

# define REALLOC(old_ptr, new_size){\
  if( !(old_ptr = realloc(old_ptr, new_size)) ){\
    printf("Insufficient memory\n");\
    exit(EXIT_FAILURE);\
  }\
}


int main(){

  printf("---- Code with Macro ----\n");

  // calloc
  int *j;

  CALLOC(j, 2, sizeof(int));

  printf("calloc 後沒給初值 -> 印出 0 值\n");
  printf("array[0] : %d\n",*(j+0));
  printf("array[1] : %d\n",*(j+1));

  // realloc
  *(j+0) = 1;
  *(j+1) = 2;

  REALLOC(j, 4*sizeof(int));

  printf("array[0-1] 有初值，其他 realloc 後沒給初值\n");
  printf("array[0] : %d\n",*(j+0));
  printf("array[1] : %d\n",*(j+1));
  printf("array[2] : %d\n",*(j+2));
  printf("array[3] : %d\n",*(j+3));

  return 0;
}
