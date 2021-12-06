#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE  "Test_case\\test_case_1-1\\input_1.txt"
#define OUTPUTFILE "output_1.txt"

FILE *f_read_ptr;
FILE *f_write_ptr;

typedef struct _node *nodePointer;
typedef struct _node{
	int data;
	nodePointer left;
	nodePointer right;
} node;


// insert node x
void insertNode(nodePointer root, int data){

	nodePointer temp = (nodePointer)malloc(sizeof(node));
	temp->data = data;

	// root == NULL
	if(!root){

	}
	// check node exist
	if(1){
		return;
	}else{
		// add node
	}
}


// del node x
void deleteNode(nodePointer root, int data){

	if(1){				// check node exist
		return;
	}else{				// del node
		if(1){			// Leaf (next)

		}else if(1){	//	if has left tree

		}else{			//

		}
	}
}


// query node x, get deepth
void queryNode(nodePointer root, int data){
	// check node exist
	if(1){
		return;
	}else{
		// query node
	}
}


// print form node x to y
void printSum(nodePointer root, int pointA, int pointB){
	// check node exist
	if(1 && 1){
		return;
	}else{
		// printSum
	}
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


	while(TRUE){
		fscanf(f_read_ptr,"%[^\n]",contents);
		endLineBuf = fgetc(f_read_ptr);
		int dataCount = -1;
		int opCount = -1;
		char charBuf = ' ';

		// get data count (M)
		int tempNum = 0, readIndex = -1;
		while (TRUE){
		  readIndex += 1;
		  charBuf = contents[readIndex];
		  if(charBuf == ' ' ){
		  	dataCount = tempNum;
		    tempNum = 0;
		    break;
		  }else{
		    tempNum = tempNum * 10 + (charBuf - '0');
		  }
		}


		// get op count (N)
		while (TRUE){
		  readIndex += 1;
		  charBuf = contents[readIndex];
		  if(charBuf == '\0' || charBuf == '\r'){
		    opCount = tempNum;
		    tempNum = 0;
		    readIndex = -1;
		    break;
		  }else{
		    tempNum = tempNum * 10 + (charBuf - '0');
		  }
		}

		//printf("%d %d\n", dataCount, opCount);

		if( dataCount == 0 && opCount == 0){
			break;
		}else{
			/* read data (M datas)*/
			fscanf(f_read_ptr,"%[^\n]",contents);
			endLineBuf = fgetc(f_read_ptr);
			printf("%s\n",contents);

			/* process opers */
			int i;
			for( i = 0 ; i < opCount ; i++){
				fscanf(f_read_ptr,"%[^\n]",contents);
				endLineBuf = fgetc(f_read_ptr);
				printf("%s\n",contents);
			}
		}
		dataCount = -1;
		opCount = -1;
	}


	fclose(f_read_ptr);
	fclose(f_write_ptr);
	printf("Complete !\n");
	return 0;
}
