#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

// 將 listPointer 定義為 listNode 結構的指標 "資料型態 "，
// 利用 listPointer 宣告出來的變數，會指向 listNode 結構
typedef struct listNode *listPointer;

// 將 listNode 結構定義成 ListNode
typedef struct listNode {
	int data;
	listPointer link;
} ListNode;

FILE *f_write_ptr;
const char *filename_output = "HW1_output_1-1.txt";
listPointer first = NULL;
int nodeCount = 0;
void initLinkedList(char *);
void addToEnd(int);
void decodeOp(char *);
void showLinkedList(void);
int getOpCount(char *);
void decodeOp(char *);
int stringToInt(char *contents);
void delFromIndex(int);
void insertAfterIndex(int, int);
void multipleFromReverseIndex(int, int);
void reverseGroupOfXItems(int);


int main(int argc, char const *argv[]) {
  FILE *f_read_ptr;
  const char *filename_input = "../testData/test_case_1-1/input_1.txt"; // 要注意 input file path

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
  }/*else {
    f_write_ptr = fopen(filename_output,"w");
  }*/


  // from input file read line
  char endLineBuf = ' ';
  char contents[100];

  // 讀入 init list
  fscanf(f_read_ptr,"%[^\n]",contents);  //讀到換行前
  initLinkedList(contents);
  endLineBuf = fgetc(f_read_ptr); //吃掉換行符號
  contents[0] = '\0'; // 歸零 contents

  //showLinkedList();


  // 讀入有幾筆操作
  fscanf(f_read_ptr,"%[^\n]",contents);  //讀到換行前
  int opCount = 0;
  opCount = getOpCount(contents);
  endLineBuf = fgetc(f_read_ptr); //吃掉換行符號
  contents[0] = '\0'; // 歸零 contents



  int i;
  for(i=0;i<opCount;i++){
    fscanf(f_read_ptr,"%[^\n]",contents);  //讀到換行前
    endLineBuf = fgetc(f_read_ptr); //吃掉換行符號
    decodeOp(contents);
  }
  showLinkedList();
  printf("%d\n",nodeCount);
  exit(EXIT_FAILURE);

  fclose(f_read_ptr);
  fclose(f_write_ptr);

  printf("Complete !\n");

  return 0;
}

// 插入尾端
void addToEnd(int data){
  //printf("%d\n",data);
  listPointer temp = (listPointer)malloc(sizeof(ListNode));
  temp->data = data;
  temp->link = NULL;

  if (!first){ // if empty
    first = temp;
    nodeCount += 1;
  }else{ // not empty
    int i;
    listPointer tail = first;
    for(i=0;i<nodeCount-1;i++){
      tail = tail->link;
    }
    tail->link = temp;
    nodeCount += 1;
  }
}

// 刪除第n個
void delFromIndex(int index){
  listPointer now = NULL, next = NULL;
  // get now and next mem position
  now = first+index-1;
  next = now->link;
  // now.data = next.data
  now->data = next->data;
  // now.link = next.link
  now->link = next->link;
  // free next
  free(next);

  nodeCount -= 1;  // 要加不然會 segment fault
}

// 插入到第n個後
void insertAfterIndex(int index, int data){

}

// 後面數過來第幾個元素乘與幾倍
void multipleFromReverseIndex(int r_count, int mult){

}

// 幾個一組 & 反轉
void reverseGroupOfXItems(int groupCount){

}

// 印出全部
void showLinkedList(void){
  listPointer now = first;
  printf("%d\n",now->data);
  while(now->link){
    now = (now->link);
    printf("%d\n",now->data);
  }
}

// list 資料初始化
void initLinkedList(char *contents){
  int tempNum = 0, readIndex = -1;
  char charBuf = ' ';
  while (TRUE){
    readIndex += 1;
    charBuf = contents[readIndex];
    if(charBuf == ' ' ){
      addToEnd(tempNum);
      tempNum = 0;
      continue;
    }else if(charBuf == '\0' || charBuf == '\r'){
      addToEnd(tempNum);
      tempNum = 0;
      break;
    }else{
      tempNum = tempNum * 10 + (charBuf - '0');
    }
  }
}

int getOpCount(char *contents){
  return stringToInt(contents);
}

int stringToInt(char *contents){
  int index = 0, count = 0;
  while(*(contents + index) != '\0' && *(contents + index) != '\r' && *(contents + index) != ' '){
    count = count*10 + (*(contents + index) - '0');
    index += 1;
  }
  // printf("%d\n",count);
  return count;
}

//
void decodeOp(char *contents){
  int startIndex = -1;  // 數字起始位置

  while (!isspace(contents[startIndex++]));

  switch (contents[0]) {
    case 'a':  //add
      addToEnd(stringToInt(&contents[startIndex]));
      break;
    case 'd':  //del
      delFromIndex(stringToInt(&contents[startIndex]));
      break;
    case 'r':  //rev
      //reverseGroupOfXItems();
      break;
    case 's':  //show
      //showLinkedList();
      break;
    case 'i':  //ins
      //insertAfterIndex();
      break;
    case 'm':  //mul
      //multipleFromReverseIndex();
      break;
  }
}
