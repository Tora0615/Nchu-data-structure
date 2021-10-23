#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 100

int queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

int isFull(){
  if(rear == MAX_QUEUE_SIZE - 1){
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
  printf("Error : queue is full ! \n");
  exit(EXIT_FAILURE);
}


void addq(int data){
  if(isFull()){
    queueFull();
  }
  queue[++rear] = data;   //
}

int deleteq(){
  if(isEmpty()){
    queueEmpty();
  }
  return queue[++front];
}


int main(int argc, char const *argv[]) {
  int i;
  for (i = 0; i < 5; i++) {
    printf("addq : %d, ",i);
    addq(i);
    printf("front : %d, rear : %d\n", front, rear);
  }
  printf("-----------\n");
  while(!isEmpty()){
    int temp = deleteq();
    printf("delq : %d, ",temp);
    printf("front : %d, rear : %d\n", front, rear);
  }
  deleteq();
  return 0;
}
