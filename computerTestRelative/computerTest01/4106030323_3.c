#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "TestCase\\test_case_3-1\\input_3.txt"

typedef struct _color *colorpointer;
typedef struct _color{
	int remain;
	int cost;
} color;


/* array pointer*/
color *colorArr;
int *blockSizeArr;
int *colorCombinationArr;
int **adjMatrix;

int minCost = INT_MAX;	// set to int max, if ans smaller than change
int blockCount, connectCount, colorCount;


void calculateMin(){
	int tempCost = 0;
	int i;
	
	/* use the only path to calculate this path's cost */
	/* this path only have blockCount blocks */
	/* from top to bottom is block 0 to N*/
	for(i=0; i<blockCount; i++){
		/* cost = bolckSize * colorCost*/
		/* colorCombinationArr[i] can get color index */
		tempCost += blockSizeArr[i] * colorArr[colorCombinationArr[i]].cost;
	}
	/* if tempCost smaller than minCost, change it*/
	if(tempCost < minCost){
		minCost = tempCost;		
	}
}

/* find top to current depth's color */
int isColorCanUse(int currentDepth){
	int i;
	/* from top search to current depth*/
	for(i=0; i<currentDepth ; i++){
		/* if target block and parent blocks is linked */
		if(adjMatrix[currentDepth][i] == 1){
			/* if parent color equal pre-coloring color*/
			if(colorCombinationArr[i] == colorCombinationArr[currentDepth]){
				return FALSE;
			}
		}
	}
	return TRUE;
}


void calculateAllFromDepth(int depth){
	/* depther than blockCount -> calculate minCost*/
	if(depth > blockCount-1){
		calculateMin();
	}
	/* use recursive calculate deeper posibles*/
	else{
		int i;
		for(i=0 ; i<colorCount ; i++){
			/* pre-coloring color (save color index to array) */
			/* this will check later (use isColorCanUse)*/
			colorCombinationArr[depth] = i;
			if(isColorCanUse(depth)){
				/* remain color more than (or equal) block size -> can fill the block */
				if(colorArr[colorCombinationArr[depth]].remain >= blockSizeArr[depth]){
					/* minus how much used */
					colorArr[colorCombinationArr[depth]].remain -= blockSizeArr[depth];
					/* go into recursive */
					calculateAllFromDepth(depth+1);
					/* come out from recursive -> add back */
					colorArr[colorCombinationArr[depth]].remain += blockSizeArr[depth];
				}
			}
		}
	}
}


int main(void){
	/* open file */
	FILE *f_read_ptr;
	if( !(f_read_ptr = fopen(INPUTFILE,"r")) ){
		printf("Faild to open file");
	}
	
	/* get blockCount, connectCount, colorCount*/
	int i;
	fscanf(f_read_ptr, "%d %d %d\n", &blockCount, &connectCount, &colorCount);
	
	/* variable init*/
	blockSizeArr = (int*)malloc(sizeof(int)*blockCount);			// save block size
	adjMatrix = calloc(blockCount, sizeof(int*));					// 1-pointer array (blockCount elements)
	colorArr = (colorpointer)malloc(sizeof(color)*colorCount);		// save all color info
	colorCombinationArr =  (int*)malloc(sizeof(int)*blockCount);	// save all color combination 
	
	/* read size and save into array*/
	for(i=0 ; i<blockCount ; i++){
		int scannedSize;
		fscanf(f_read_ptr,"%d ",&scannedSize);
		blockSizeArr[i] = scannedSize;
		adjMatrix[i] = calloc(blockCount, sizeof(int));
	}
	
	/* get adjacency matrix */
	for(i=0 ; i<connectCount ; i++){
		int u,v;
		fscanf(f_read_ptr,"%d %d\n",&u,&v);
		adjMatrix[u-1][v-1] = 1;
		adjMatrix[v-1][u-1] = 1;
	}

	
	/* get colors and save to array*/
	for(i=0 ; i<colorCount ;i ++){
		char nameC;
		int nameN, remain, cost;
		fscanf(f_read_ptr,"%c%d %d %d\n" ,&nameC ,&nameN ,&remain ,&cost);
		colorArr[i].remain = remain;
		colorArr[i].cost = cost;
	}

	/* calculate all possible situation*/	
	calculateAllFromDepth(0);
	
	/* print final answer*/
	printf("%d\n", minCost);

	fclose(f_read_ptr);
	return 0;
}




// from top recursive to end, find the min cost
// all posible situation like tree, calculate like DFS
// 
//   A,B,C is block; 0,1 is color
//   this will get all posible
//
//   A-------
//  0|	    1|
//   B---   B---
//  0| 1|  0| 1|
//   C  C   C  C
// 
//  reference : 
//  https://kknews.cc/zh-tw/tech/99l3z25.html?fbclid=IwAR2F73RPJQNqkb7nU3sDjNapCw2v3Dfz0IjMhFQcVRczYqrpgjUSK_bf_M4
