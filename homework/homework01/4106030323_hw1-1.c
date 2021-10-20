#include <stdio.h>
#include <stdlib.h>
# include <string.h>

FILE *f_write_ptr;
const char *filename_output = "HW1_output.txt";




void process(char* input) {
  unsigned long int len = strlen(input)-1;
  printf("%s\n",input);
  printf("%lu\n",len);
  //printf("%c\n",*(input+3)); // print result
  //fprintf(f_write_ptr,"%s",input);  // output to file
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
  }

  // from input file read line
  char endLineBuf = ' ';
  while(endLineBuf != EOF){
    char contents[100];
    fscanf(f_read_ptr,"%[^\n]",contents);
    process(contents);
    //printf("%s",contents);
    endLineBuf = fgetc(f_read_ptr);
  }

  fclose(f_read_ptr);
  fclose(f_write_ptr);

  return 0;
}




/*
some notes

兩者都能用
char *stringBuf = (char*) malloc(sizeof(char)*101);
char stringBuf[101];

自己寫 read line


用函式 readline - CPP
1.
char *contents = NULL;
size_t len = 0;
while (getline(&contents, &len, f_read_ptr) != -1){
  process(contents);  // process strings
}
free(contents);

2.
char endLineBuf = ' ';
while(endLineBuf != EOF){
  char contents[100];
  fscanf(f_read_ptr,"%[^\n]",contents);
  process(contents);
  //printf("%s",contents);
  endLineBuf = fgetc(f_read_ptr);
}

3.
char *contents = (char *)malloc(sizeof(char)*150);  // char contents[150]; 也可
while(fgets(contents, 150, f_read_ptr) != NULL){
  process(contents);
}



scanf :
%[] 讀入一个字符集
"%[^=]" 读入任意多的字符,直到遇到"="停止

函數readline
getline()


char array pointer 取值
--> *(ptr+i)
*/
