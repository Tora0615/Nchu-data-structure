#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

/* NEED Change Before upload*/
#define INPUTFILE "Test_Case\\test_case_2-1\\input_2.txt"
//#define INPUTFILE  "../Test_Case/test_case_2-1/input_2.txt"

#define OUTPUTFILE "output_2.txt"
#define DEBUG 0

FILE *f_read_ptr;
FILE *f_write_ptr;

typedef struct _node *nodepointer;
typedef struct _node{
	int data;
	nodepointer next;
	int cost;  // to this node cost how muxh
}node;

typedef struct _header{
	nodepointer start;
	//int visited;
}header;


void DFS(int *visitedArr, ){
	
}

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
	int index = 0;
	int maxNodes = stringToInt(contents);
	while(!isspace(contents[index++]));
	int orders = stringToInt(&contents[index]);
//	printf("%d %d",maxNodes,orders);

	// init header
	header headerList[maxNodes];
	int i;
//	for(i=0 ; i<maxNodes ; i++){
//		headerList[i].visited = 0;
//	}
	
	
	for(i=0 ; i<maxNodes-1 ; i++){
		int index = 0;
		int u = stringToInt(contents);
		while(!isspace(contents[index++]));
		int v = stringToInt(&contents[index]);
		while(!isspace(contents[index++]));
		int p = stringToInt(&contents[index]);
		nodepointer tempA = (nodepointer)malloc(sizeof(node));
		tempA->data = v;
		tempA->next = NULL;
		tempA->cost = p;
		if(!headerList[u-1].start){
			headerList[u-1].start = tempA;
		}else{
			nodepointer head = headerList[u-1].start;
			while(head->next){
				head = head->next; 
			}
			head->next = tempA;
		}
		
		nodepointer tempB = (nodepointer)malloc(sizeof(node));
		tempB->data = u;
		tempB->next = NULL;
		tempB->cost = p;
		if(!headerList[u-1].start){
			headerList[u-1].start = tempB;
		}else{
			nodepointer head = headerList[u-1].start;
			while(head->next){
				head = head->next; 
			}
			head->next = tempB;
		}
	}

	fclose(f_read_ptr);
	fclose(f_write_ptr);
	free(contents);
	printf("Complete !\n");
	return 0;
}
