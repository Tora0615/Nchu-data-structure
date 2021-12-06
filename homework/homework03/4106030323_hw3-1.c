#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE  "Test_case\\test_case_1-1\\input_1.txt"
#define OUTPUTFILE "output_1.txt"

#define COUNT 10   // print 2D

FILE *f_read_ptr;
FILE *f_write_ptr;

typedef struct _node *nodePointer;
typedef struct _node{
	int data;
	nodePointer left;
	nodePointer right;
} node;


void print2DUtil(nodePointer root, int space){
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    int i;
    for (i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(nodePointer root){
   // Pass initial space count as 0
   printf("--------------------------------------------------------------------------------------\n");
   print2DUtil(root, 0);
   printf("--------------------------------------------------------------------------------------\n");
}

// insert node x
nodePointer insertNode(nodePointer root, int data){

	nodePointer temp = (nodePointer)malloc(sizeof(node));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;

	// root == NULL
	if(!root){
		return temp;
	}

	// check wether the node exist or not
	nodePointer visitPointer = root;				// use for visit nodes
	nodePointer insertPointer = NULL;				// use to save the position to insert node
	while (visitPointer) {	// visit nodes untill to NULL
		if(visitPointer->data != data){
			if(data > visitPointer->data){
				if(visitPointer->right == NULL){	// save insert position
					insertPointer = visitPointer;
				}
				visitPointer = visitPointer->right;
			}else{
				if(visitPointer->left == NULL){		// save insert position
					insertPointer = visitPointer;
				}
				visitPointer = visitPointer->left;
			}
		}else{								// node exist
			return root;
		}
	}
	
	// node doesn't exist --> add node
	if(data > insertPointer->data){
		insertPointer->right = temp;
	}else{
		insertPointer->left = temp;
	}
	return root;
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


nodePointer initTree(nodePointer root, char *contents, int dataCount){
	int i;
	for(i=0 ; i<dataCount-1 ; i++){
		//printf("root addr : %p\n",root);
		int temp = stringToInt(contents);
		root = insertNode(root, temp);

		int startIndex = 0;
		while (!isspace(contents[startIndex++]));  // get the index after space
		contents = &contents[startIndex];
	}
	int temp = stringToInt(contents);
	root = insertNode(root, temp);

	return root;
}


// del node x
nodePointer deleteNode(nodePointer root, int data){
	
	// root == NULL
	if(!root){
		return root;
	}
	
	
	// check wether the node exist or not
	nodePointer deletePointer = root;				// use to save the position to delete node
	nodePointer parent = NULL;
	while (deletePointer) {					// visit nodes untill to NULL
		if(deletePointer->data != data){
			if(data > deletePointer->data){
				parent = deletePointer;
				deletePointer = deletePointer->right;
			}else{
				parent = deletePointer;
				deletePointer = deletePointer->left;
			}
		}else{								// node exist
			break;
		}
	}

	nodePointer target = NULL;
	nodePointer targetParent = NULL;
	int haveLeft = -1;
	if(!deletePointer){				// node NOT exist 
		return;
	}else{				// del node
		if(!deletePointer->left  && !deletePointer->right){			// is Leaf (left = null & right = null)
			if(deletePointer == root){				// is also root
				free(deletePointer);
				return NULL;
			}else{									// not root
				free(deletePointer);
				parent->data = NULL;
				return root;
			}
		}else if(deletePointer->left){				// if have left tree
			haveLeft = TRUE;
			if(deletePointer->left->right){			// 
				target = deletePointer->left;
				while(target->right){				// find max node in left tree
					targetParent = target;
					target = target->right;
				}
			}else{									// 
				targetParent = deletePointer;
				if (deletePointer->right){
					target = deletePointer->right;
				}else{
					target = deletePointer->left;
				}
				printf("targetParent : %d\n",targetParent->data);
				printf("target : %d\n",target->data);
			}
			
		}else{			// DONT have left tree but have right tree
			haveLeft = FALSE;
			if(deletePointer->right->left){
				target = deletePointer->right;
				while(target->left){					// find min node in right tree
					targetParent = target;
					target = target->left;
				}
			}else{
				targetParent = deletePointer;
					if (deletePointer->left){
					target = deletePointer->left;
				}else{
					target = deletePointer->right;
				}
				printf("targetParent : %d\n",targetParent->data);
				printf("target : %d\n",target->data);
			}
			
		}
	}
	
	// swap max/min data to deletePoint, and del leaf
	deletePointer->data = target->data;
	if(haveLeft){
		targetParent->right = NULL;
	}else{
		targetParent->left = NULL;
	}
	free(target);	
	return root;
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
	nodePointer treeRoot = NULL;


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

		printf("%d %d\n", dataCount, opCount);

		if( dataCount == 0 && opCount == 0){
			break;
		}else{
			/* read data (M datas)*/
			fscanf(f_read_ptr,"%[^\n]",contents);
			endLineBuf = fgetc(f_read_ptr);
			printf("%s\n",contents);
			treeRoot = initTree(treeRoot, contents, dataCount);
			print2D(treeRoot);		// print tree
			
			treeRoot = deleteNode(treeRoot, 2);
			print2D(treeRoot);		// print tree

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
		treeRoot = NULL;
	}


	fclose(f_read_ptr);
	fclose(f_write_ptr);
	printf("Complete !\n");
	return 0;
}
