#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 102

// TODO :
// 1. check 相同優先度是否會出錯
// 2. 優先度表是否要更改

int processIndex ;
int lastIsNum = FALSE;

FILE *f_write_ptr;
const char *filename_output = "HW1_output.txt";

/* -- Stack 相關 -- */
char stack[MAX_STACK_SIZE];
int top = -1;

int isFull(){
  return top > MAX_STACK_SIZE - 1;
}

int isEmpty(){
  return top == -1;
}


void stackEmpty(){
  printf("Error : stack is empty ! \n");
  exit(EXIT_FAILURE);
}

void stackFull(){
  printf("Error : stack is full ! \n");
  exit(EXIT_FAILURE);
}


void push(char data){
  if (isFull()) {
    stackFull();
  }else{
    stack[++top] = data;
  }
}


char pop(){
  if(isEmpty()){
    stackEmpty();
  }
  return stack[top--];
}
/* -- Stack 相關 -- */


/* -- Ans Stack 相關 -- */
char ansStack[500];
int ansTop = -1;

int ansIsFull(){
  return ansTop > 500 - 1;
}

int ansIsEmpty(){
  return ansTop;
}


void ansStackEmpty(){
  printf("Error : ans stack is empty ! \n");
  exit(EXIT_FAILURE);
}

void ansStackFull(){
  printf("Error : ans stack is full ! \n");
  exit(EXIT_FAILURE);
}


void ansPush(char data){
  if (ansIsFull()) {
    ansStackFull();
  }else{
    ansStack[++ansTop] = data;
  }
}


char ansPop(){
  if(ansIsEmpty()){
    ansStackEmpty();
  }
  return ansStack[ansTop--];
}

/* -- Ans Stack 相關 -- */



int getLevel(char input){
  if(input == ')' || input == '('){
    if(stack[top] == ')'){
      return 0;
    }
    return 4;
  }else if(input == '*' || input == '%' || input == '/'){
    return 3;
  }else if(input == '+' || input == '-'){
    return 2;
  }else if(input == '>' || input == '<'){
    return 1;
  }else if(input == '&' || input == '^' || input == '|'){
    return 0;
  }else{
    return 0;
  }
}




// 處理每個元素
void processItem (char input) {

  //處理左讀到右會讀到 \r 的問題
  if(input == '\r'){
    input = '\0';
  }

  // 非運算子的判斷
  if (isdigit(input) || (input > 64 && input < 91) || (input > 96 && input < 123) || input == '.'){  //65~90, 97~122
    lastIsNum = TRUE;
    //printf("%c", input);
    ansPush(input);
  }
  //運算子 part
  else{
    // 括號相關，遇到左括號一直 pop (魔改)
    if( input == '(' ){
      while (TRUE){
        char temp = pop();
        if (temp == ')') {
          break;
        }
        //printf(" %c",temp);
        ansPush(' ');
        ansPush(temp);
      }
    }
    //負號(魔改)：右方是數字 或是 在最一開始
    else if ( input == '-' && processIndex == 0 || input == '-' && lastIsNum){
      //printf("%c", input);
      ansPush(input);
    }
    //句尾 (句首) 一直印出
    else if ( input == '\0'){
      while (top != -1){
        //printf(" %c",pop());
        ansPush(' ');
        ansPush(pop());
      }
    }
    else{
      //input 優先度 < stack 優先度 --> pop
      while ( !isEmpty() && (getLevel(stack[top]) > getLevel(input)) ){   // 裡面優先大於外面 --> pop
        //printf(" %c",pop());
        ansPush(' ');
        ansPush(pop());
      }
      // 補空格
      if(input != ')'){
        //printf(" ");
        ansPush(' ');
      }
      //input 優先度 > stack 優先度 --> push
      push(input);
    }
    lastIsNum = FALSE;
  }
}


// 傳入一句，一個一個讀字元，判斷是運算子還是運算元
void postfix(char* input) {
  unsigned long int len = strlen(input);
  //printf("%s\n",input);  //測試讀入句子

  // 倒過來讀並處理，然後將結果丟到 ansStack
  for (processIndex = len - 1 ; processIndex > -1 ; processIndex--){
    processItem( *(input + processIndex) );
  }
  processItem('\0');

  // 從 ansStack 印出結果
  while ( ! ansIsEmpty() ){
    //printf("%c",ansPop());
    fprintf(f_write_ptr,"%c",ansPop());
  }
  //printf("\n");
  fprintf(f_write_ptr,"\n");
}



int main(int argc, char const *argv[]) {

  FILE *f_read_ptr;
  const char *filename_input = "../testData/input_1.txt"; // 要注意 input file path

  // input file open
  if (!(f_read_ptr = fopen(filename_input,"r"))){
    printf("Cannot open file : %s\n", filename_input);
    exit(EXIT_FAILURE);
  }

  // open output file with fool proof.
  if((f_write_ptr = fopen(filename_output,"r"))){
    fclose(f_write_ptr);
    printf("File %s have already exist.\nContinue to overwrite output file ? [Y/N] ",filename_output);
    char temp;
    scanf(" %c",&temp);
    if (temp == 'Y' || temp == 'y'){
        f_write_ptr = fopen(filename_output,"w");
    }else{
      printf("Override canceled\n");
      fclose(f_read_ptr);
      exit(EXIT_FAILURE);
    }
  }else {
    f_write_ptr = fopen(filename_output,"w");
  }

  // from input file read line
  char endLineBuf = ' ';
  while(endLineBuf != EOF){
    char contents[100];
    fscanf(f_read_ptr,"%[^\n]",contents);  //讀到換行前

    // 一句一句處理
    postfix(contents);

    top = -1;  //確認歸零 stack
    endLineBuf = fgetc(f_read_ptr); //吃掉換行符號
  }

  fclose(f_read_ptr);
  fclose(f_write_ptr);

  printf("Complete !\n");
  return 0;
}



/*

// 正常的優先度
int getLevel(char input){
  if(input == '(' || input == ')'){
    if(stack[top] == '('){
      return 0;
    }
    return 4;
  }else if(input == '*' || input == '%' || input == '/'){
    return 3;
  }else if(input == '+' || input == '-'){
    return 2;
  }else if(input == '>' || input == '<'){
    return 1;
  }else if(input == '&' || input == '^' || input == '|'){
    return 0;
  }else{
    return 0;
  }
}

// 正常的中序轉後續
void processItem (char input) {
  if(input == '\r'){
    input = '\0';
  }
  //printf("\ntop : %d\n",top);
  if (isdigit(input) || (input > 64 && input < 91) || (input > 96 && input < 123) || input == '.'){  //65~90, 97~122
    lastIsChar = FALSE;
    printf("%c", input);
  }else{   //運算子 part
    if( input == ')' ){
      while (TRUE){
        char temp = pop();
        if (temp == '(') {
          break;
        }
        printf(" %c",temp);
      }
    }
    else if ( input == '-' && processIndex == 0 || input == '-' && lastIsChar){
      printf("%c", input);
    }
    else if ( input == '\0'){   // 句尾
      // printf("here");
      while (top != -1){
        printf(" %c",pop());
      }
    }
    else{
      //大於 -> push，小於等於一直pop
      while ( !isEmpty() && (getLevel(stack[top]) > getLevel(input)) ){   // 裡面優先大於外面 --> pop
        printf(" %c",pop());
      }
      if(input != '('){
        printf(" ");
      }

      push(input);  //input 優先 > stack 優先 --> push
    }
    lastIsChar = TRUE;
  }
}


*/
