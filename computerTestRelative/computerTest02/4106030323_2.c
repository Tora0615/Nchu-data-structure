#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "TestData\\test_case_2-3\\input_2.txt"

typedef struct _node{
	int isLinked;
	int len;
}node;
node **adjMatrix;
int *orderArr;
int **recordList;
int *totalCostList;
int nodeCount;
int *visited;


int dfs (int node, int len){ 
	visited[node] = TRUE;
	int i, returnVal = 0;	
		
	/* find another nodes linked with input node*/
	/* in tail will not go to dfs*/
	for(i=0; i<nodeCount; i++){
		/* isLinked and not visited */
		if(adjMatrix[node][i].isLinked == 1 && visited[i]==FALSE){
			/* add catched return value*/
			returnVal = returnVal + dfs(i, adjMatrix[node][i].len + len);
		}
	}
	
	/* check this node have order or not -> if have -> return this node's cost */
	if(orderArr[node]){
		/* current cost = len * order * 2 */
		return (len * orderArr[node] * 2) + returnVal;
	}
	/* if don't have : return origin value*/
	else{
		return returnVal;
	}
}

/* create a node to other nodes' cost*/
void getVisitCost(){
	/* init recordList*/
	int i, j;
	// malloc 
	recordList = (int**)malloc(sizeof(int*) * nodeCount);
	for(i=0; i<nodeCount; i++){
		recordList[i] = (int*)malloc(sizeof(int) * nodeCount);
	}
	// set value to max
	for(i=0; i<nodeCount; i++){
		for(j=0; j<nodeCount; j++){
			recordList[i][j] = INT_MAX;
		}
	}
	
	
	/* visited list */
	visited = (int*)malloc(sizeof(int) * nodeCount);
	
	/* calculate */ 
	totalCostList = (int*)malloc(sizeof(int) * nodeCount);
	for(i=0; i<nodeCount; i++){	
		/* reset visited array*/
		for(j=0; j<nodeCount; j++){
			visited[j] = FALSE;
		}
		/* dfs : set node i as start point, and pass current len */
		/* dfs(start node, len)*/
		totalCostList[i] = dfs (i, 0);
		//printf("%d\n",totalCostList[i]);
	}
}


int main(void){
	/* file open */
	FILE* f_read_ptr;
	if ( !(f_read_ptr = fopen(INPUTFILE,"r")) ){
		printf("Cannot open file : %s\n", INPUTFILE);
		return 0;
	}
	
	/* read node count and order count*/
	int orderCount;
	fscanf(f_read_ptr,"%d %d\n",&nodeCount, &orderCount);
	
	/* init 2-D (node) adjMatrix*/
	int i;
	adjMatrix = (node **)malloc(sizeof(node*) * nodeCount);
	for(i=0; i<nodeCount; i++){
		adjMatrix[i] = (node *)malloc(sizeof(node) * nodeCount);	
	}
	
	/* save nodes */
	for(i=0; i<nodeCount-1; i++){
		int start, end, len;
		fscanf(f_read_ptr,"%d %d %d\n",&start, &end, &len);
		start-=1;  end-=1;	// testdata start from 1
		adjMatrix[start][end].isLinked = TRUE;
		adjMatrix[end][start].isLinked = TRUE;
		adjMatrix[start][end].len = len;
		adjMatrix[end][start].len = len;
	}
	
	/* init 1-D (int) order array*/
	orderArr = (int *)malloc(sizeof(int) * nodeCount);
	for(i=0; i<nodeCount; i++){
		orderArr[i] = 0;
	}
	
	/* save orders */
	for(i=0; i<orderCount; i++){
		int location, order;
		fscanf(f_read_ptr,"%d %d\n",&location, &order);
		orderArr[location-1] = order;
	}
	
	/* calculate point to point cost */
	getVisitCost();
	
	/* find min */
	int min = INT_MAX;
	for(i=0; i<nodeCount; i++){
		// printf("%d ",totalCostList[i]);
		if(totalCostList[i] < min){
			min = totalCostList[i];
		}
	}
	printf("%d\n",min);
	
	/* find min's index */
	for(i=0; i<nodeCount; i++){
		if(totalCostList[i] == min){
			printf("%d ",i+1);
		}
	}
	printf("\n");
	
	fclose(f_read_ptr);
	return 0;
}


