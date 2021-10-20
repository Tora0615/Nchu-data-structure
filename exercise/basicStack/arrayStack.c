#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

# define MAX_STACK_SIZE 100
int stack[MAX_STACK_SIZE];
int top = -1;

int isFull(){
  if(top > MAX_STACK_SIZE - 1){
    return TRUE;
  }
  return FALSE;
}

int isEmpty(){
  if(top == -1){
    return TRUE;
  }
  return FALSE;
}



void push(int data){
  if (isFull()) {
    printf("Error : stack is full ! \n");
    //exit(EXIT_FAILURE);
  }else{
    stack[++top] = data;
  }
}


int pop(){
  if(isEmpty()){
    printf("Error : stack is empty ! \n");
    //exit(EXIT_FAILURE);
  }
  return stack[top--];
}




int main(int argc, char const *argv[]) {
  int i;
  for (i = 0; i < 10; i++) {
    printf("Push : %d\n",i);
    push(i);
  }
  printf("-----------\n");
  while(!isEmpty()){
    printf("Pop : %d\n",pop());
  }
  pop();
  return 0;
}
