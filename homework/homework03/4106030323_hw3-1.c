#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "Test_case\\test_case_1-1\\input_1.txt"
#define OUTPUTFILE "output_1.txt"

FILE *f_read_ptr;
FILE *f_write_ptr;


int main(int argc, char const *argv[]) {
	
	if (!(f_read_ptr = fopen(INPUTFILE,"r"))){
		printf("Cannot open file : %s\n", INPUTFILE);
		exit(EXIT_FAILURE);
	}
	
	if((f_write_ptr = fopen(OUTPUTFILE,"r"))){
		fclose(f_write_ptr);
		printf("File %s have already exist.\nContinue to overwrite output file ? [Y/N] ",OUTPUTFILE);
		char temp;
		scanf(" %c",&temp);
		if (temp == 'Y' || temp == 'y'){
		    f_write_ptr = fopen(OUTPUTFILE,"w");
		}else{
		  printf("Override canceled\n");
		  fclose(f_read_ptr);
		  exit(EXIT_FAILURE);
		}
	}else {
		f_write_ptr = fopen(OUTPUTFILE,"w");
	}
	
	char endLineBuf = ' ';
	char contents[10000];
	
	
	fscanf(f_read_ptr,"%[^\n]",contents); 
	
	
	fclose(f_read_ptr);
	fclose(f_write_ptr);
	printf("Complete !\n");
	return 0;
}
