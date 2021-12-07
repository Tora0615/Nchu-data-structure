#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "Test_case\\test_case_2-1\\input_2.txt"
#define OUTPUTFILE "output_2.txt"

FILE *f_read_ptr;
FILE *f_write_ptr;
char *dict = " !,-.:;?0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";  
int dictLen = 70;


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
	}/** else {
		f_write_ptr = fopen(OUTPUTFILE,"w");
	}**/
	
	char endLineBuf = ' ';
	char contents[10000];
	
	while(TRUE){
		fscanf(f_read_ptr,"%[^\n]",contents); 
		endLineBuf = fgetc(f_read_ptr);
		int dataCount = stringToInt(contents);
		if(dataCount){				// bigger than 0
			int i;
			for(i=0;i<dataCount;i++){
				fscanf(f_read_ptr,"%[^\n]",contents); 
				endLineBuf = fgetc(f_read_ptr);
				printf("%s\n",contents);
				
			}
		}else{
			break;
		}
	}
	
	
	
	
	fclose(f_read_ptr);
	fclose(f_write_ptr);
	printf("Complete !\n");
	return 0;
}


