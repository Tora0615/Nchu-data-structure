#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

FILE *f_write_ptr;
const char *filename_output = "output_2.txt";

int main(int argc, char const *argv[]) {
  FILE *f_read_ptr;
  char *filename_input = "../testData/test_case_2-1/orders.txt"; // 要注意 input file path

  // input file 01 open
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
  } /*else {
    f_write_ptr = fopen(filename_output,"w");
  }*/
  return 0;
}
