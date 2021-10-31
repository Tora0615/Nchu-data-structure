#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define SINK 1
#define FLOAT_UP 1
#define MAX 1
#define OPER >
// 最小堆積


int *queue ;

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
void queueEmpty(){
  printf("Error : queue is empty ! \n");
  exit(EXIT_FAILURE);
}

void queueFull(){
  // 印出錯誤並退出
  // printf("Error : queue is full ! \n");
  // exit(EXIT_FAILURE);


  //加倍
  printf("full ! ~ x2 \n");
  queue = realloc(queue, sizeof(int) * MAX * multiply);
  multiply *= 2;
}
/* queue ralated */

void swapNode(int *arr, int index1, int index2){
  int temp = -1;
  temp = *(arr+index1);
  *(arr+index1) = *(arr+index2);
  *(arr+index2) = temp;
}

// void reAllocateNode(){
//
// }

void addToHeap(int *arr, int value){

  // check heap size
  if(isFull()){
    queueFull();
  }

  // Add to rear
  *(arr + ++rear) = value;
  //printf("%d\n", *(arr + rear));

  // compare and float to root    // >=1
  while( (*(arr + rear) OPER *(arr + rear/2)) && (rear/2 >= front)){
    swapNode(arr, rear, rear/2 );

  }

}

int deleteFromHeap(int *arr){
  int returnVal = -1;

  // root and rear swap
  swapNode(arr, rear, front);

  // delete rear
  returnVal = queue [rear--];

  // root sink
  int index = 1;
  while( ( *(arr + index*2 ) OPER *(arr + index) ) && (index*2 < rear)){
    //printf("%d\n",index);
    // 下沉要比較，最大堆積要沉到比較大那邊
    printf("r%d\n",rear);
    if( *(arr + index*2) OPER *(arr + index*2 + 1) ){
      swapNode(arr, index, index*2 );
      index = index * 2;
    }else{
      swapNode(arr, index, index*2+1 );
      index = index * 2 + 1;
    }

  }

  return returnVal;
}





int main(int argc, char const *argv[]) {
  queue = calloc(MAX, sizeof(int));

  addToHeap(queue, 10);
  addToHeap(queue, 28);
  addToHeap(queue, 20);
  addToHeap(queue, 22);
  addToHeap(queue, 24);
  addToHeap(queue, 13);
  addToHeap(queue, 10);
  addToHeap(queue, 28);
  addToHeap(queue, 20);
  addToHeap(queue, 22);
  addToHeap(queue, 24);
  addToHeap(queue, 13);
  addToHeap(queue, 10);
  addToHeap(queue, 28);
  addToHeap(queue, 20);
  addToHeap(queue, 22);
  addToHeap(queue, 24);
  addToHeap(queue, 13);


  int i;

  for (i=0;i<18;i++){
    printf("%d\n", *(queue+i+1));
  }
  printf("\n");

  for (i=0;i<18;i++){
    printf("%d\n",deleteFromHeap(queue));
  }
  return 0;
}



// [0]    [1]   [2]   [3]
// front              rear
