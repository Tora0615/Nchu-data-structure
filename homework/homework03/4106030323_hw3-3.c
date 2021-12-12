#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "Test_case\\test_case_3-1\\input_3.txt"
#define OUTPUTFILE "output_3.txt"

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
	return count;
}

void paintWall(int start, int end, char color){
	// printf("P : %d %d %c\n",start, end, color);
}

void queryRange(int start, int end){
	// printf("Q : %d %d\n",start, end);
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
	} /*else {
		f_write_ptr = fopen(OUTPUTFILE,"w");
	}*/

	char endLineBuf = ' ';
	char contents[10000];

	
	fscanf(f_read_ptr,"%[^\n]",contents);
	int wallLen = stringToInt(contents);
	endLineBuf = fgetc(f_read_ptr);
	
	fscanf(f_read_ptr,"%[^\n]",contents);
	int dataCount = stringToInt(contents);
	endLineBuf = fgetc(f_read_ptr);

	int i;
	for(i=0;i<dataCount;i++){
		fscanf(f_read_ptr,"%[^\n]",contents);
		endLineBuf = fgetc(f_read_ptr);
		
		int index = 0;
		while(!isspace(contents[index++]));
		int start = stringToInt(&contents[index]);
		
		while(!isspace(contents[index++]));
		int end = stringToInt(&contents[index]);
		
			
		if(contents[0] == 'P'){
			while(!isspace(contents[index++]));
			char color = contents[index];
			paintWall(start, end, color);
		}else{
			queryRange(start, end);
		}
	}


	fclose(f_read_ptr);
	fclose(f_write_ptr);
	printf("Complete !\n");
	return 0;
}
