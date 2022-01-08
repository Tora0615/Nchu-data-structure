#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "TestCase\\test_case_1-0\\input_0.txt"

FILE *f_read_ptr;
typedef struct _node *nodepointer;
typedef struct _node{
	int data;
	nodepointer left;
	nodepointer right;
}node;

int COUNT = 10;
void print2DUtil(nodepointer root, int space){
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
void print2D(nodepointer root){
   // Pass initial space count as 0
   printf("--------------------------------------------------------------------------------------\n");
	 if(!root){
		 //printf("tree is empty\n");
		 return;
	 }
	 print2DUtil(root, 0);
   printf("--------------------------------------------------------------------------------------\n");
}

void printMaxSum(nodepointer root, int x, int y){
	//printf("Sum : %d and %d \n",x,y);
	
	/* if x == y */
	if(x==y){
		if(x>0){
			printf("%d\n", x);
			return;
		}
	}
	
	/* set min and max */
	int minNode, maxNode;
	if(x > y){
		maxNode = x;
		minNode = y;
	}else{
		maxNode = y;
		minNode = x;
	}
	
	/* find root between two num*/
	if(maxNode > root->data && minNode < root->data){
		root = root;
	}else{
		nodepointer temproot = root;
		while(temproot){
			if(temproot->data > maxNode){
				temproot = temproot->left;
			}else if(temproot->data < minNode){
				temproot = temproot->right;
			}else{
				break;
			}
		}
		root = temproot;
	}
	//printf("root data : %d\n", root->data);
	
	int tempsumA = 0, tempsumB = 0, rootVal = 0;
	int isOK = FALSE;
	nodepointer visitpointer;
	
	/* get nodeA exist or not and get temp sum*/
	visitpointer = root;
	while(visitpointer){
		if(visitpointer->data > minNode){
			if(visitpointer->data > 0){
				tempsumA = tempsumA + visitpointer->data;
			}
			visitpointer = visitpointer->left;
		}else if(visitpointer->data < minNode){
			if(visitpointer->data > 0){
				tempsumA = tempsumA + visitpointer->data;
			}
			visitpointer = visitpointer->right;
		}
		/* find */
		else{
			if(visitpointer->data > 0){
				tempsumA = tempsumA + visitpointer->data;
			}
			isOK = TRUE;
			break;
		}
	}

	/* check partA*/
	if(isOK){
		isOK = FALSE;
	}else{
		return;
	}

	/* get nodeB exist or not and get temp sum*/
	visitpointer = root;
	while(visitpointer){
		if(visitpointer->data > maxNode){
			if(visitpointer->data > 0){
				tempsumB = tempsumB + visitpointer->data;
			}
			visitpointer = visitpointer->left;
		}else if(visitpointer->data < maxNode){
			if(visitpointer->data > 0){
				tempsumB = tempsumB + visitpointer->data;
			}
			visitpointer = visitpointer->right;
		}else{
			if(visitpointer->data > 0){
				tempsumB = tempsumB + visitpointer->data;
			}
			isOK = TRUE;
			break;
		}
	}
	
	// check root->data whether positive or not
	if(root->data > 0){
		rootVal = root->data;
	}
	
	// check part B
	if(isOK){
		//	printf("%d\n",tempsumA);
		//	printf("%d\n",tempsumB);
		//	printf("%d\n",rootVal);
		printf("%d\n", tempsumA + tempsumB - rootVal);
	}
}

nodepointer insertNode(nodepointer root, int data){
	
	/*init node*/
	nodepointer temp = (nodepointer)malloc(sizeof(node));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	
	/* root is empty*/ 
	if(!root){
		return temp;
	}
	
	/* not empty*/
	nodepointer visitpointer = root;
	nodepointer insertpointer = NULL;
	/* find node*/
	while(visitpointer){
		if(visitpointer->data != data){
			if(data > visitpointer->data){
				if(visitpointer->right == NULL){
					insertpointer = visitpointer;
				}
				visitpointer = visitpointer -> right;
			}else{
				if(visitpointer->left == NULL){
					insertpointer = visitpointer;
				}
				visitpointer = visitpointer -> left;
			}
		}else{
			/* exist -> direct return root*/
			return root;
		}
	}
	
	
	/* node not exist -> add */
	if(data > insertpointer->data){
		insertpointer->right = temp;
	}else{
		insertpointer->left = temp;
	}
	return root;
}

nodepointer deleteNode(nodepointer root, int data){
	//	printf("del : %d\n",data);
	
	/* root == null*/
	if(!root){
		return root;
	}
	
	/* find node exist or not*/
	nodepointer delpointer = root;
	nodepointer delparent = NULL;
	while(delpointer){
		if(data != delpointer->data){
			if(data > delpointer->data){
				delparent = delpointer;
				delpointer = delpointer->right;
			}else{
				delparent = delpointer;
				delpointer = delpointer->left;
			}
		}else{
			break;
		}
	}
	
	
	/* del node*/
	nodepointer swaptarget = NULL;
	nodepointer swapparent = NULL;
	/* Dont exist*/
	if(!delpointer){
		return root;
	}
	/* exist */
	else{
		/* is leaf */
		if(delpointer->left == NULL && delpointer->right==NULL){
			/* is also root*/
			if(delpointer == root){
				free(delpointer);
				return NULL;
			}
			/* not root */
			else{
				if(delpointer == delparent->right){
					delparent->right = NULL;
				}else{
					delparent->left = NULL;
				}
				return root;
			}
		}
		/* have left */
		else if(delpointer->left){
			swaptarget = delpointer->left;
			/* swaptarget have one left child and don't have right*/
			if(swaptarget->left == NULL && swaptarget->right == NULL){
				delpointer->data = swaptarget->data;
				delpointer->left = NULL;
				free(swaptarget);
			}
			/* swaptarget have MORE THAN ONE left child and don't have right*/
			else if(swaptarget->right == NULL){
				delpointer->data = swaptarget->data;
				delpointer->left = swaptarget->left;
				free(swaptarget);
			}
			/* swaptarget have right (have or dont have left)*/
			else{
				/* find max value*/
				while(swaptarget->right){
					swapparent = swaptarget;
					swaptarget = swaptarget->right;
				}
				/* swap data*/
				delpointer->data = swaptarget->data;
				/* swapparent point to swaptarget->left (because maybe have left) */
				if(swaptarget->left){
					swapparent->right = swaptarget->left;
				}else{
					swapparent->right = NULL;
				}
				free(swaptarget);
			}
			return root;
		}
		/* only have right */
		else{
			swaptarget = delpointer->right;
			/* swaptarget have one right child and don't have left*/
			if(swaptarget->right == NULL && swaptarget->left == NULL){
				delpointer->data = swaptarget->data;
				delpointer->right = NULL;
				free(swaptarget);
			}
			/* swaptarget have MORE THAN ONE right child and don't have left*/
			else if(swaptarget->left == NULL){
				delpointer->data = swaptarget->data;
				delpointer->right = swaptarget->right;
				free(swaptarget);
			}
			/* swaptarget have left (have or dont have right)*/
			else{
				/* find min value*/
				while(swaptarget->left){
					swapparent = swaptarget;
					swaptarget = swaptarget->left;
				}
				/* swap data*/
				delpointer->data = swaptarget->data;
				/* swapparent point to swaptarget->right (because maybe have left) */
				if(swaptarget->right){
					swapparent->left = swaptarget->right;
				}else{
					swapparent->left = NULL;
				}
				free(swaptarget);
			}
			return root;
		}
	}
}



int main(void){
	
	/* open file */
	if(!(f_read_ptr = fopen(INPUTFILE, "r"))){
		printf("failed to open");
	}
	int nodeCount, opCount;
	fscanf(f_read_ptr, "%d %d\n", &nodeCount, &opCount);
	//	printf("%d %d\n", nodeCount, opCount); return;
	

	/* init tree */
	nodepointer root = NULL;
	int i ;
	for(i=0; i<nodeCount; i++){
		int temp;
		fscanf(f_read_ptr, " %d", &temp);
		//printf("~~%d~~",temp);  return;
		root = insertNode(root, temp);
	}
	//print2D(root);
	
	/* Do operations */
	char charbuf = getc(f_read_ptr);	// eat "\n"
	for(i=0; i<opCount; i++){
		char opcode;
		int data, data2;
		fscanf(f_read_ptr, "%c", &opcode);
		if(opcode == 'I' || opcode == 'D'){
			fscanf(f_read_ptr, " %d\n", &data);
			if (opcode == 'I'){
				root = insertNode(root, data);
			}else{
				root = deleteNode(root, data);
			}
		}else if(opcode == 'Q'){
			fscanf(f_read_ptr, " %d\n", &data);
			printf("\n");
		}else{
			fscanf(f_read_ptr, " %d %d\n", &data, &data2);
			printMaxSum(root, data, data2);
		}
		//print2D(root);
	}

	fclose(f_read_ptr);
}
