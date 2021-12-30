#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

/* NEED Change Before upload*/
#define INPUTFILE "Test_Case\\test_case_1-3\\input_1.txt"
//#define INPUTFILE  "../Test_Case/test_case_1-1/input_1.txt"

#define OUTPUTFILE "output_1.txt"
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

void delNode(int *array, int *degree, int target, int range){
	int i;
	for (i=0 ; i < range ; i++){
		if(*(array + target*range + i) != 0){
			*(array + target*range + i) = 0;		// del connect
			if (*(degree+i) > 0){
				*(degree+i) = *(degree+i) - 1;		// del related degree 
			}
		}
	}
}

void printArr(int *array, int jobCount){
	int i, j;
	// print array
	for(i=0 ; i<jobCount ; i++){
		for(j=0 ; j<jobCount ; j++){
			printf("%d ",*(array + i*jobCount + j));
		} 
		printf("\n");
	} 
}

void printDeg(int *degreeList, int jobCount){
	int i;
	printf("\n");
	for(i=0 ; i<jobCount ; i++){
		printf("%d ",degreeList[i]);
	} 
	printf("\n");
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
	} else {
		f_write_ptr = fopen(OUTPUTFILE,"w");
	}

	char endLineBuf = ' ';
	char *contents = (char*)malloc(sizeof(char)*5000000);
	int jobCount = -1, relationCount = -1, index = 0, i = 0, j=0, k=0;	// jobCount is node's count
		
	fscanf(f_read_ptr,"%[^\n]",contents);
	endLineBuf = fgetc(f_read_ptr);
	
	jobCount = stringToInt(contents);
	while(!isspace(contents[index++]));
	relationCount = stringToInt(&contents[index]);
	
	// Use jobCount to create 2-dimention Node array and init it
	int array[jobCount][jobCount];
	
	for(i=0 ; i<jobCount ; i++){
		for(j=0 ; j<jobCount ; j++){
			array[i][j] = 0;
		} 
	} 
	
	// save data into array
	for(i=0 ; i < relationCount ; i++){
		fscanf(f_read_ptr,"%[^\n]",contents);
		endLineBuf = fgetc(f_read_ptr);
		index = 0;
		int x = stringToInt(contents);
		while(!isspace(contents[index++]));
		int y = stringToInt(&contents[index]);
		// printf("%d %d\n", x, y);
		array[x-1][y-1] = 1;
	}
	
	/* ---- calculate degree ---- */
	int degreeList[jobCount];
	// init list
	for(i=0 ; i<jobCount ; i++){
		degreeList[i] = 0;
	}
	// calulate
	for(j=0 ; j<jobCount ; j++){
		for(i=0 ; i<jobCount ; i++){
			if (array[i][j] == 1){
				degreeList[j] += 1;
			}
		}
	} 
	

	
	// find answers
	for(i=0 ; i<jobCount ; i++){
		for (j=0 ; j < jobCount ; j++){
			if (degreeList[j] == 0){
				//printf("%d ", j+1);
				fprintf(f_write_ptr, "%d ", j+1);
				degreeList[j] = -1;
				delNode(array, degreeList, j, jobCount);
				break;
			}
		}
	} 
	//printf("\n");
	

	fclose(f_read_ptr);
	fclose(f_write_ptr);
	free(contents);
	printf("Complete !\n");
	return 0;
}


// key word : topological sort
