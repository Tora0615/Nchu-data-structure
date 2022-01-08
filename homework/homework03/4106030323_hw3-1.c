#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "Test_case\\test_case_1-3\\input_1.txt"
//#define INPUTFILE  "../Test_case/test_case_1-3/input_1.txt"
#define OUTPUTFILE "output_1.txt"
#define DEBUG 0



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
    if (root == NULL){
      return;
		}


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
	 if(!root){
		 //printf("tree is empty\n");
		 return;
	 }
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
		return root;
	}else{		/*printf("data %d",deletePointer->data);*/		// del node
		if(!deletePointer->left  && !deletePointer->right){			// is Leaf (left = null & right = null)
			if(deletePointer == root){				// is also root
				free(deletePointer);
				return NULL;
			}else{									// not root
				if(parent->left == deletePointer){					// left leaf
					parent->left = NULL;
				}else{								// right leaf
					parent->right = NULL;
				}
				free(deletePointer);
				return root;
			}
		}
		// else if(deletePointer == root){
		// 	if(deletePointer->left){
		// 		root = deletePointer->left;
		// 	}else if(deletePointer->right){
		// 		root = deletePointer->right;
		// 	}else{
		// 		root = NULL;
		// 	}
		// 	printf("here\n");
		// 	//free(deletePointer);
		// 	return root;
		// }
		else if(deletePointer->left){				// have left tree
			target = deletePointer->left;

//			printf("deletePointer : %p\n",deletePointer);
//			printf("target : %p\n",target);
//			printf("target->left : %p\n",target->left);
//			printf("target->right : %p\n",target->right);

			if(!target->left && !target->right){	// 3 -> 2(L)
				deletePointer->data = target->data;
				deletePointer->left = NULL;
				free(target);
			}else if(!target->right){				// 3 -> 2(L) -> ....(L)
				deletePointer->data = target->data;
				deletePointer->left = target->left;
				free(target);
			}else{									// 4 -> 2(L) -> 1(L)3(R)
				while(target->right){				// find max node in left tree
					targetParent = target;
					target = target->right;
				}
				deletePointer->data = target->data;	// swap the data of deletePointer & target

				// 第四種情況
				if(target->left){
					targetParent->right = target->left;
				}else{
					targetParent->right = NULL;
				}
				free(target);
			}
			return root;
		}else{										// only have right tree
			target = deletePointer->right;
			if(!target->right && !target->left){	// 3 -> 5(R)
				deletePointer->data = target->data;
				deletePointer->right = NULL;
				free(target);
			}else if(!target->left){				// 3 -> 5(R) -> ....(R)
				deletePointer->data = target->data;
				deletePointer->right = target->right;
				free(target);
			}else{									// 3 ->  5(R) -> 4(R)7(L)
				while(target->left){				// find min node in left tree
					targetParent = target;
					target = target->left;
				}
				deletePointer->data = target->data;	// swap the data of deletePointer & target

				// 第四種情況
				if(target->right){
					targetParent->left = target->right;
				}else{
					targetParent->left = NULL;
				}
				free(target);
			}
			return root;
		}
	}
}


// query node x, get deepth
void queryNode(nodePointer root, int data){
	if(root){
		// check wether the node exist or not
		nodePointer visitPointer = root;				// use for visit nodes
		int deepth = 0;
		while (visitPointer) {	// visit nodes untill to NULL
			deepth += 1;
			if(visitPointer->data != data){
				if(data > visitPointer->data){
					visitPointer = visitPointer->right;
				}else{
					visitPointer = visitPointer->left;
				}
			}else{								// node exist
				//printf("deep : ");
				DEBUG ? printf("node(%d) deep : %d\n",data, deepth) : fprintf(f_write_ptr,"%d\n",deepth);
				//printf("%d\n",deepth);

				break;
			}
		}
	}
}


// print form node x to y
void printSum(nodePointer root, int pointA, int pointB){

	int maxNode, minNode;
	if (pointA > pointB){
		maxNode = pointA;
		minNode = pointB;
	}else{
		maxNode = pointB;
		minNode = pointA;
	}

	// check node exist
	if(root){

		// find brench node
		if(maxNode > root->data && minNode < root->data){
			root = root;
		}else{
			nodePointer visitPointer = root;				// use for visit nodes
			while (visitPointer) {	// visit nodes untill to NULL
				if(visitPointer->data < minNode){
					visitPointer = visitPointer->right;
				}else if(visitPointer->data > maxNode){
					visitPointer = visitPointer->left;
				}else {
					break;
				}
			}
			root = visitPointer;
		}


		// check wether the node exist or not
		nodePointer visitPointer = root;				// use for visit nodes
		int total = 0, sumA = 0, isALegal = FALSE;
		while (visitPointer) {	// visit nodes untill to NULL
			if( visitPointer->data >= 0){
				sumA = sumA + visitPointer->data;
			}
			if(visitPointer->data != minNode){
				if(minNode > visitPointer->data){
					visitPointer = visitPointer->right;
				}else{
					visitPointer = visitPointer->left;
				}
			}else{								// node exist
				total = total + sumA;
				isALegal = TRUE;
				break;
			}
		}
		//printf("sumA %d\n", sumA);


		if (pointA == pointB){
			if(isALegal){
				//prinf("%d\n",pointA);
				fprintf(f_write_ptr,"%d\n",pointA);
			}
		}else{
			int sumB = 0;
			int isBLegal = FALSE;
			visitPointer = root;
			while (visitPointer) {	// visit nodes untill to NULL
				if( visitPointer->data >= 0){
					sumB = sumB + visitPointer->data;
				}
				if(visitPointer->data != maxNode){
					if(maxNode > visitPointer->data){
						visitPointer = visitPointer->right;
					}else{
						visitPointer = visitPointer->left;
					}
				}else{								// node exist
					total = total + sumB;
					isBLegal = TRUE;
					break;
				}
			}
			//printf("sumB %d\n", sumB);

			if(isALegal && isBLegal){
				if (root->data > 0){
					total = total - root->data;
				}else{
					total = total;
				}
				//printf("total:");
				//printf("%d\n",total);

				DEBUG ? printf("A(%d) to B(%d) sum : %d\n",pointA,pointB,total) : fprintf(f_write_ptr,"%d\n",total);
			}
		}
	}
}

void decodeOP(nodePointer root, char *content){
	int index = 0;
	while(!isspace(content[index++]));

	if(content[0] == 'I'){
		root = insertNode(root, stringToInt(&content[index]));
	}else if(content[0] == 'D'){
		root = deleteNode(root, stringToInt(&content[index]));
		//print2D(root);
	}else if(content[0] == 'Q'){
		queryNode(root, stringToInt(&content[index]));
	}else if(content[0] == 'P'){
		int index2 = index;
		while(!isspace(content[index2++]));
		printSum(root, stringToInt(&content[index]), stringToInt(&content[index2]));
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
	} else {
		f_write_ptr = fopen(OUTPUTFILE,"w");
	}

	char endLineBuf = ' ';
	char *contents = (char*)malloc(sizeof(char)*5000000);
	nodePointer treeRoot = NULL;
	int totalTestCase = 0;

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
			//printf("%s\n",contents);
			treeRoot = initTree(treeRoot, contents, dataCount);
			//printf("%s\n",contents);
			//print2D(treeRoot);		// print tree

			DEBUG ? printf("# %d\n",++totalTestCase) : fprintf(f_write_ptr,"# %d\n",++totalTestCase);

			/* process opers */
			int i;
			for( i = 0 ; i < opCount ; i++){
				fscanf(f_read_ptr,"%[^\n]",contents);
				endLineBuf = fgetc(f_read_ptr);
				//printf("%s\n",contents);
				decodeOP(treeRoot, contents);
			}
		}
		dataCount = -1;
		opCount = -1;
		treeRoot = NULL;
	}


	fclose(f_read_ptr);
	fclose(f_write_ptr);
	free(contents);
	printf("Complete !\n");
	return 0;
}
