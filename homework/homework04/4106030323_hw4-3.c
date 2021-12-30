#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

/* NEED Change Before upload*/
#define INPUTFILE "Test_Case\\test_case_3-1\\input_3.txt"
//#define INPUTFILE  "../Test_Case/test_case_3-1/input_3.txt"

#define OUTPUTFILE "output_3.txt"
#define DEBUG 0

FILE *f_read_ptr;
FILE *f_write_ptr;

int stringToInt(char *contents){
  	int index = 0, count = 0, isNegative = FALSE;
  	while(*(contents + index) != '\0' && *(contents + index) != '\r' && *(contents + index) != ' '){
	  	if(*(contents + index) == '-'){
	  		isNegative = TRUE;
		}else{
			count = count*10 + (*(contents + index) - '0');
		}
	    index += 1;
	}
	if(isNegative){
		count = count* (-1);
	}
	//printf("count %d\n",count);
	return count;
}



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
	} /* else {
		f_write_ptr = fopen(OUTPUTFILE,"w");
	}*/

	char endLineBuf = ' ';
	char *contents = (char*)malloc(sizeof(char)*5000000);
	
	fscanf(f_read_ptr,"%[^\n]",contents);
	endLineBuf = fgetc(f_read_ptr);


	fclose(f_read_ptr);
	fclose(f_write_ptr);
	free(contents);
	printf("Complete !\n");
	return 0;
}
