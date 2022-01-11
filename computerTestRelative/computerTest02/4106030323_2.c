#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
//#define INPUTFILE "TestData\\test_case_2-3\\input_2.txt"
#define INPUTFILE "TestData\\5\\input_5-5.txt"

typedef struct _node{
	int isLinked;
	int len;
}node;
node **adjMatrix;
int *orderArr;
int *totalCostList;
int nodeCount;
int *visited;


void dfs (int node, int len, int order){ 
	visited[node] = TRUE;
	int i;
		
	/* find another nodes linked with input node*/
	/* in tail will not go to dfs*/
	for(i=0; i<nodeCount; i++){
		/* isLinked and not visited */
		if(adjMatrix[node][i].isLinked == 1 && visited[i]==FALSE){
			/* pass next node, add len, start point's order */
			dfs(i, adjMatrix[node][i].len + len, order);
		}
	}
	
	/* direct write to totalCostList */
	totalCostList[node] = totalCostList[node] + order*len*2;
}

/* create a node to other nodes' cost*/
void getVisitCost(){
	/* init recordList*/
	int i, j;	
	
	/* visited list */
	visited = (int*)malloc(sizeof(int) * nodeCount);
	
	/* calculate */ 
	for(i=0; i<nodeCount; i++){	
		/* reset visited array*/
		for(j=0; j<nodeCount; j++){
			visited[j] = FALSE;
		}
		/* dfs : set node i as start point, and pass current len */
		/* dfs(start node, len, order)*/
		if(orderArr[i]){
			dfs(i, 0, orderArr[i]);
		}
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
	totalCostList = (int*)malloc(sizeof(int) * nodeCount);
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


