#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define orderPATH "../testData/test_case_2-1/orders.txt"
#define recipePATH "../testData/test_case_2-1/recipes.txt"


FILE *f_write_ptr;
const char *filename_output = "output_2.txt";

typedef struct _ordernode *orderpointer;
typedef struct _ordernode{
  int order_ID;
  char *recipe_name;
  int arrival;
  int deadline;
  int money;
  int punishment;
  orderpointer pre;
  orderpointer next;
} ordernode;

typedef struct _componentnode *componentpointer;
typedef struct _componentnode {
  char *name;
  componentpointer pre;
  componentpointer next;
} componentnode;

typedef struct _recipesnode *recipespointer;
typedef struct _recipesnode {
  char* recipe_name;
  componentpointer stove;
  componentpointer cut;
  componentpointer others;
  recipespointer pre;
  recipespointer next;
} recipesnode;


orderpointer readOrders(FILE*, orderpointer);
void readRecipe(FILE*, recipespointer);
int getValue(char*);

int main(int argc, char const *argv[]) {
  FILE *f_read_ptr;
  char *filename_input = orderPATH; // define in macro
  orderpointer orderHead = NULL;
  recipespointer recipeHead = NULL;

  // input file order open
  if (!(f_read_ptr = fopen(filename_input,"r"))){
    printf("Cannot open file : %s\n", filename_input);
    exit(EXIT_FAILURE);
  }
  orderHead = readOrders(f_read_ptr, orderHead);  //傳指標進去是複製一份....，要再傳出來


  filename_input = recipePATH; // 要注意 input file path
  // input file recipe open
  if (!(f_read_ptr = fopen(filename_input,"r"))){
    printf("Cannot open file : %s\n", filename_input);
    exit(EXIT_FAILURE);
  }
  readRecipe(f_read_ptr, recipeHead);

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
  } /*else {
    f_write_ptr = fopen(filename_output,"w");
  }*/
  return 0;
}


orderpointer readOrders(FILE *f_write_ptr, orderpointer orderHead){
  char buf;
  char context[100];
  fscanf(f_write_ptr,"%[^\n]",context);
  buf = fgetc(f_write_ptr);
  orderpointer pre = NULL;

  // get data count
  int i = 0, range = 0;
  while(context[i] != '\0' && context[i] != '\r'){
    range = range * 10 + context[i] - '0' ;
    i+=1;
  }
  //printf("count : %d\n",range);

  // save data to linked list
  for(i = 0; i<range ; i++){  //幾筆資料
    // 宣告節點
    orderpointer temp = malloc(sizeof(ordernode));
    char* tempc = malloc(sizeof(char)*50);

    // 節點初始化
    temp -> order_ID = -1;
    temp -> recipe_name = malloc(sizeof(char)*50);
    temp -> recipe_name[0] = '\0';
    temp -> arrival = -1;
    temp -> deadline = -1;
    temp -> money = -1;
    temp -> punishment = -1;
    temp -> pre = NULL;
    temp -> next = NULL;


    int j;
    for (j = 0; j < 6; j++) {
      fscanf(f_write_ptr,"%[^ &&[^\n]]",context);
      buf = fgetc(f_write_ptr);

      //change here
      switch (j) {
        case 0:
          //printf("order_ID : %s\n",context);
          //printf("value : %d\n",getValue(context));
          temp -> order_ID = getValue(context);
          break;
        case 1:
          //printf("recipe_name : %s\n",context);
          // temp -> recipe_name = context; 會出錯，因為是給位置
          strcpy(tempc, context);
          temp -> recipe_name = tempc;
          break;
        case 2:
          //printf("arrival : %s\n",context);
          temp -> arrival = getValue(context);
          break;
        case 3:
          //printf("deadline : %s\n",context);
          temp -> deadline = getValue(context);
          break;
        case 4:
          //printf("money : %s\n",context);
          temp -> money = getValue(context);
          break;
        case 5:
          //printf("punishment : %s\n",context);
          temp -> punishment = getValue(context);
          break;
      }
    }
    // node insert to main linked list
    if(!orderHead){
      orderHead = temp;
      pre = temp;
    }else{
      //printf("%p\t%p\t%p\t%p\n", temp->pre, temp, temp->next, pre);
      temp->pre = pre;
      pre->next = temp;
      pre = temp;
      //printf("%p\t%p\t%p\t%p\n", temp->pre, temp, temp->next, pre);
    }
  }
  return orderHead;
}

void readRecipe(FILE *f_write_ptr, recipespointer recipeHead){
  char buf;
  char context[100];
  fscanf(f_write_ptr,"%[^\n]",context);
  buf = fgetc(f_write_ptr);

  // get data count
  int i = 0, range = 0;
  while(context[i] != '\0' && context[i] != '\r'){
    range = range * 10 + context[i] - '0' ;
    i+=1;
  }
  //printf("count : %d\n",range);

  // save data to linked list
  for(i = 0; i<range ; i++){
    int j;
    for (j = 0; j < 4; j++) {
      // fscanf(f_write_ptr,"%[^ ]",context);
      fscanf(f_write_ptr,"%[^ &&[^\n]]",context);  //不等於空格(^ )以及不等於換行符號(^\n)
      buf = fgetc(f_write_ptr);
      //printf("%s\n",context);

      int k = 0;
      char *tempStr = malloc(sizeof(char)*100);
      int startIndex = 0;
      tempStr[0] = '\0';
      while(context[k] != '\r' && context[k] != '\n' && context[k] != '\0'){
        if(context[k] == ','){
          tempStr = &context[startIndex];
          tempStr[k] = '\0';

          //change here
          switch (j) {
            case 0:
              printf("recipe_name : %s\n",tempStr);
              break;
            case 1:
              printf("stove : %s\n",tempStr);
              break;
            case 2:
              printf("cut : %s\n",tempStr);
              break;
            case 3:
              printf("others : %s\n",tempStr);
              break;
          }

          // 歸零 & Index 初始位置移動
          tempStr[0] = '\0';
          startIndex = k+1;
        }
        k+=1;
      }
      tempStr = &context[startIndex];
      tempStr[k] = '\0';

      //change here
      switch (j) {
        case 0:
          printf("recipe_name : %s\n",tempStr);
          break;
        case 1:
          printf("stove : %s\n",tempStr);
          break;
        case 2:
          printf("cut : %s\n",tempStr);
          break;
        case 3:
          printf("others : %s\n",tempStr);
          break;
      }

    }
  }
}


int getValue(char *str){
  int k, num = 0;
  while(str[k]!='\0'){
    num = num*10 + str[k]-'0';
    k+=1;
  }
  return num;
}


// 排序到達的，先到的先做


// %[ ]	一个字符集
