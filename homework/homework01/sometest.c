#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 1
#define OPER >


int testData[] = {1,5,8,6,7,4,2,4,3};
int size = 3;

typedef struct _node {
  int x;
  int y;
  int cost;
  int isPassed;
  int isSpecial;
  int height;
}node;

// int bfs(){
//
//   int dir[8][2] = {
//     //  左     左上      上       右上     右      右下       下      左下
//     {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}
//   };
//
// }

int heightAbs(int a, int b){
  if (a>b){
    return a-b;
  }else{
    return b-a;
  }
}

node *queue ;

/* queue ralated */
int rear = 0;  //後面    1開始存，
int front = 1;  //前面
int multiply = 2;

int isFull(){
  if(rear == MAX * multiply / 2 - 1){
    return TRUE;
  }
  return FALSE;
}

int isEmpty(){
  if(front == rear){
    return TRUE;
  }
  return FALSE;
}

void queueFull(){
  //加倍
  queue = realloc(queue, sizeof(node) * MAX * multiply);
  multiply *= 2;
}

void swapNode(node *arr, int index1, int index2){
  node temp;
  temp = *(arr+index1);
  *(arr+index1) = *(arr+index2);
  *(arr+index2) = temp;
}

node deleteFromHeap(node *arr){
  node returnVal;
  // root and rear swap
  swapNode(arr, rear, front);
  // delete rear
  returnVal = queue[rear--];
  // root sink
  int index = 1;
  while( ( (arr + index*2)->cost OPER (arr + index)->cost || (arr + index*2+1)->cost OPER (arr + index)->cost ) && (index*2 < rear)){
    // 下沉要比較，最大堆積要沉到比較大那邊
    if( (arr + index*2)->cost OPER (arr + index*2 + 1)->cost ){
      swapNode(arr, index, index*2 );
      index = index * 2;
    }else{
      swapNode(arr, index, index*2+1 );
      index = index * 2 + 1;
    }
  }
  return returnVal;
}

void addToHeap(node *arr, node value){
  // check heap size
  if(isFull()){
    queueFull();
  }
  // Add to tail
  *(arr + ++rear) = value;
  // compare and float to root    // >=1
  int index = rear;
  while( ( (arr + index)->cost OPER (arr + index/2)->cost ) && (index/2 >= front)){
    swapNode(arr, index, index/2 );
    index = index / 2 ;
  }
}

void printArr(node *arr,int size){
  int i,j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++){
      printf("%d ", (arr + i*3+j)->x);
      printf("%d ", (arr + i*3+j)->y);
      printf("%d ", (arr + i*3+j)->cost);
      printf("%d ", (arr + i*3+j)->isPassed);
      printf("%d ", (arr + i*3+j)->isSpecial);
      printf("%d ", (arr + i*3+j)->height);
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
      array[i*3+j].height = testData[i*3+j];
    }
  }

  printArr (array, 3);
  printf("\n");

  queue = calloc(MAX, sizeof(node));
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      addToHeap(queue,array[i*3+j]);
    }
  }

  printArr (queue, 4);  // index 0 會印出 00000  //size 設不正確的會重複印
	//BFS(0);
}
