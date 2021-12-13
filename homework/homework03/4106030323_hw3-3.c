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

typedef struct _node *nodePointer;
typedef struct _node{
	int start;
	int end;
	nodePointer left;
	nodePointer right;
	char color;
} node ;

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

void paintWall(nodePointer root, int start, int end, char color){
	// printf("P : %d %d %c\n",start, end, color);
	
	// if paint range equal root node range
	if(root->start == start && root->end == end){
		root->color = color;
		root->left = NULL;
		root->right = NULL;
		// free tree
	}else{
		int range = (root->end - root->start) / 2 ;
		// creat left child (half range)
		if(!root->left){
			nodePointer temp = (nodePointer)malloc(sizeof(node));
			temp->left = NULL;
			temp->right = NULL;
			temp->start = root->start;
			temp->end = root->start + range;
			temp->color = root->color;
			root->left = temp;
		}
		
		// creat right child (half range)
		if(!root->right){
			nodePointer temp = (nodePointer)malloc(sizeof(node));
			temp->left = NULL;
			temp->right = NULL;
			temp->start = root->start + range + 1;
			temp->end = root->end;
			temp->color = root->color;
			root->right = temp;
		}
		
		
		// recursive process two child (set them as new root)
		if(mid > start && mid < end || mid+1 > start && mid+1 <end || mid == start && mid+1 ==end){
			paintWall(node->left, start, end, color);
			paintWall(node->right, start, end, color);
			node->color = '?';
			return;
		}
		// if need range in left child  or current node's start in need range
		else if( (root->left->start <= start && root->left->end >= end)  ||  (root->start >= start && root->start <= end) ){
			// use left node as root and do again
			paintWall(node->left, start, end, color);
			node->color = '?';
			return;
		}
		
		// if need range in right child or current node's end in need range
		else if( (root->right->start <= start && root->right->end >= end)  ||  (root->end >= start && root->end <= end) ){
			// use right node as root and do again
			paintWall(node->right, start, end, color);
			node->color = '?';
			return;
		}	
	}
}

void queryRange(nodePointer root, int start, int end){
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
	
	nodePointer treeRoot;
	treeRoot = (nodePointer)malloc(sizeof(node));
	treeRoot->start = 0;
	treeRoot->end = wallLen;
	treeRoot->left = NULL;
	treeRoot->right = NULL;
	treeRoot->color = '_';
	
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
			paintWall(treeRoot, start, end, color);
		}else{
			queryRange(treeRoot, start, end);
		}
	}


	fclose(f_read_ptr);
	fclose(f_write_ptr);
	printf("Complete !\n");
	return 0;
}
