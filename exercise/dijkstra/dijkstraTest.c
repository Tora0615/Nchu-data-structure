// TEST DATA IS CORRECT, BUT MAYBE HAVE BUGS (MAYBE IS HEAP PART, IT IS WRITE BY MYSELF)
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 1
#define OPER <

//int testData[] = {1,5,8,6,7,4,2,4,3};
 int testData[] = {1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5};
// int testData[] = {
//   1, 7, 4, 11, 10, 21, 14, 17,
//   7, 2, 1, 11, 9, 20, 11, 1,
//   6, 7, 7, 11, 8, 19, 1, 1,
//   8, 11, 12, 7, 7, 17, 2, 3,
//   4, 13, 14, 6, 7, 1, 19, 18,
//   2, 9, 6, 6, 7, 2, 19,18,
//   9, 9, 2, 7, 1, 10, 2, 9,
//   10, 9, 3, 7, 7, 8, 7, 8,
// };
int size = 5;

typedef struct _node {
  int x;
  int y;
  int cost;
  int isPassed;
  int isSpecial;
  int height;
}node;

typedef struct _point{
  int x;
  int y;
} point;





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
      printf("%d ", (arr + i*size+j)->x);
      printf("%d ", (arr + i*size+j)->y);
      printf("%d ", (arr + i*size+j)->cost);
      printf("%d ", (arr + i*size+j)->isPassed);
      printf("%d ", (arr + i*size+j)->isSpecial);
      printf("%d ", (arr + i*size+j)->height);
      printf("\n");
    }
  }
}

int dijkstra(point start, point end, int size,node array[]){
  int dir[8][2] = {
    //  左     左上      上       右上     右      右下       下      左下
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}
  };

  addToHeap(queue, array[start.x *size + start.y]);

  node temp ;
  while(TRUE){
    temp = deleteFromHeap(queue);
    while(temp.isPassed){
      temp = deleteFromHeap(queue);
    }

    array[temp.x *size + temp.y].isPassed = TRUE;  //走過標記


    printf("temp : %d %d\n",temp.x,temp.y);
    if(temp.x == end.x && temp.y == end.y){
      break;
    }
    int i;
    for(i=0;i<8;i++){
      int tempX = temp.x + dir[i][0];
      int tempY = temp.y + dir[i][1];
      printf("tempXY : %d %d",tempX,tempY);
      if(tempX > -1 && tempY > -1 && tempX < size && tempY < size ){
        array[tempX *size + tempY].cost \
            = heightAbs(array[tempX *size + tempY].height, temp.height) \
                + temp.cost;
        printf(" cost:%d",array[tempX *size + tempY].cost);
        addToHeap(queue, array[tempX *size + tempY]);
      }
      printf("\n");
    }
    printArr(queue,size);
  }
  return temp.cost;
}

int main() {
  int i, j;
  node array[size*size];

  // 初始化
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      array[i*size+j].x = i ;
      array[i*size+j].y = j ;
      array[i*size+j].cost = 0 ;
      array[i*size+j].isPassed = 0 ;
      array[i*size+j].isSpecial = 0 ;
      array[i*size+j].height = testData[i*size+j];
    }
  }

  printArr (array, size);
  printf("\n");

  // queue = calloc(MAX, sizeof(node));
  // for (i = 0; i < 3; i++) {
  //   for (j = 0; j < 3; j++) {
  //     addToHeap(queue,array[i*3+j]);
  //   }
  // }
  //
  // printArr (queue, 4);  // index 0 會印出 00000  //size 設不正確的會重複印

  point start,end;
  start.x = 0;
  start.y = 0;
  end.x = 4;
  end.y = 4;

  queue = calloc(MAX, sizeof(node));
  printf("%d\n",dijkstra(start,end,size,array));
}
