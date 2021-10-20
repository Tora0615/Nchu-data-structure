#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 4

int queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

// 用不到了
// int isFull(){
//   if(rear == MAX_QUEUE_SIZE - 1){
//     return TRUE;
//   }
//   return FALSE;
// }
//
// int isEmpty(){
//   if(front == rear){
//     return TRUE;
//   }
//   return FALSE;
// }

void queueEmpty(){
  printf("Error : queue is empty ! \n");
  exit(EXIT_FAILURE);
}

void queueFull(){
  printf("Error : queue is full ! \n");
  exit(EXIT_FAILURE);
}

// 不必檢查 isFull() or isEmpty() --> 改為檢查兩者是否重疊
void addq(int data){
  rear = (rear+1) % MAX_QUEUE_SIZE; //important
  if(front == rear){  // isFull() 改來的
    queueFull();
  }
  queue[rear] = data;
}

int deleteq(){
  if(front == rear){  // isEmpty() 改來的
    queueEmpty();
  }
  front = (front+1) % MAX_QUEUE_SIZE; //important
  return queue[front];
}


int main(int argc, char const *argv[]) {
  int i, j=0;

  for (i = 0; i < 3; i++) {
    printf("addq : %d, ",j);
    addq(j++);
    printf("front : %d, rear : %d\n", front, rear);
  }
  printf("-----------\n");
  for (i = 0; i < 3; i++) {
    int temp = deleteq();
    printf("delq : %d, ",temp);
    printf("front : %d, rear : %d\n", front, rear);
  }
  printf("-----------\n");
  for (i = 0; i < 3; i++) {
    printf("addq : %d, ",j);
    addq(j++);
    printf("front : %d, rear : %d\n", front, rear);
  }
  printf("-----------\n");
  for (i = 0; i < 3; i++) {
    int temp = deleteq();
    printf("delq : %d, ",temp);
    printf("front : %d, rear : %d\n", front, rear);
  }
  return 0;
}
