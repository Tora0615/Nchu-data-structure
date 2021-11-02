#include <stdio.h>
#include <stdlib.h>

int testData[] = {1,5,8,6,7,4,2,4,3};
int size = 3;

typedef struct _node {
  int x;
  int y;
  int cost;
  int isPassed;
  int isSpecial;
}node;

void printArr(node *arr,int size){
  int i,j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++){
      printf("%d ", (arr + i*3+j)->x);
      printf("%d ", (arr + i*3+j)->y);
      printf("%d ", (arr + i*3+j)->cost);
      printf("%d ", (arr + i*3+j)->isPassed);
      printf("%d ", (arr + i*3+j)->isSpecial);
      printf("\n");
    }
  }
}

int main() {
  int i, j;
  node array[9];
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      array[i*3+j].x = i ;
      array[i*3+j].y = j ;
      array[i*3+j].cost = -1 ;
      array[i*3+j].isPassed = 0 ;
      array[i*3+j].isSpecial = 0 ;
    }
  }

  printArr (array, 3);
}
