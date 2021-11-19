#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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


void readOrders(FILE*, orderpointer);
void readRecipe(FILE*, recipespointer);

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
  readOrders(f_read_ptr, orderHead);

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


void readOrders(FILE *f_write_ptr, orderpointer orderHead){
  char buf;
  char context[100];
  fscanf(f_write_ptr,"%[^\n]",context);
  buf = fgetc(f_write_ptr);

  int i = 0, range = 0;
  while(context[i] != '\0' && context[i] != '\r'){
    range = range * 10 + context[i] - '0' ;
    i+=1;
  }
  printf("count : %d\n",range);
}

void readRecipe(FILE *f_write_ptr, recipespointer recipeHead){
  char buf;
  char context[100];
  fscanf(f_write_ptr,"%[^\n]",context);
  buf = fgetc(f_write_ptr);

  int i = 0, range = 0;
  while(context[i] != '\0' && context[i] != '\r'){
    range = range * 10 + context[i] - '0' ;
    i+=1;
  }
  printf("count : %d\n",range);
}
