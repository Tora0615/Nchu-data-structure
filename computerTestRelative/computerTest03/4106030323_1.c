#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "TestData\\Test_case_1-1\\input_1.txt"

FILE *f_read_ptr;
FILE *f_write_ptr;

void delNode(int *adjMatrix, int *degreeList, int target, int range){
	int i;
	/* horizental fine linked item */
	for(i=0; i<range; i++){
		/* if item not exit */
		if(*(adjMatrix + target*range + i) != 0){
			/* delete (set to 0)*/
			*(adjMatrix + target*range + i) = 0;
			/* del related degree (-1) */
			if (degreeList[i] > 0){
				degreeList[i] = degreeList[i] - 1;		
			}
		}
	}
}

int main(){
	if (!(f_read_ptr = fopen(INPUTFILE,"r"))){
		printf("Cannot open file : %s\n", INPUTFILE);
		return 0;
	}
	
	/* get basic info*/
	int jobCount, relationCount;
	fscanf(f_read_ptr,"%d %d\n", &jobCount, &relationCount);
	
	/* creat adjMatrix and init*/
	int i, j;
	int adjMatrix[jobCount][jobCount];
	for(i=0 ; i<jobCount ; i++){
		for(j=0 ; j<jobCount ; j++){
			adjMatrix[i][j] = 0;
		} 
	} 
	
	/* save data into adjMatrix (it is the directed graph)*/
	for(i=0; i<relationCount; i++){
		int a, b;
		fscanf(f_read_ptr,"%d %d\n", &a, &b);
		adjMatrix[a-1][b-1] = 1;
	} 
	
	/* init degree list */
	int degreeList[jobCount];
	for(i=0 ; i<jobCount ; i++){
		degreeList[i] = 0;
	}
	
	/* calulate degree */
	for(j=0 ; j<jobCount ; j++){
		for(i=0 ; i<jobCount ; i++){
			if (adjMatrix[i][j] == 1){
				degreeList[j] += 1;
			}
		}
	} 
	
	/*    adjMatrix : 
		1	2	3	4	5
	1	0	1	1	0	0
	2	0	0	1	1	0
	3	0	0	0	0	1
	4	0	0	0	0	0
	5	0	0	0	1	0
	     degreeList : 
	A	0	1	2	2	1 */
	
	/* init ans array to save answer, saveIndex to indicate save position */
	int ansArr[jobCount];
	int saveIndex = 0; 
	
	
	/* calculate and save to ansArr */
	for(i=0; i<jobCount; i++){			// save jobCount's count node to ansArr
		/* find 0 in degreeList and delete it (if have many 0, first read first delete) */
		for(j=0; j<jobCount; j++){
			if(degreeList[j] == 0){
				ansArr[saveIndex] = j+1;	// node name
				saveIndex += 1;
				degreeList[j] = -1;			// mark it is OK
				delNode(adjMatrix, degreeList, j, jobCount);	// delete data in the two array
				break;						// hava answer, jump out of this loop
			}
		}
	}
	
	/* check is legal or not */
	/* legal condition : adjMatrix is empty */
	int isLegal = TRUE;
	for(i=0 ; i<jobCount ; i++){
		for (j=0 ; j < jobCount ; j++){
			if (adjMatrix[i][j] != 0){
				isLegal = FALSE;
				break;
			}
		}
		if(!isLegal){
			break;
		}
	}
	
	/* print answer */
	int f_out = FALSE;
	if(!isLegal){
		f_out ? fprintf(f_write_ptr,"not exist") : printf("not exist");
	}else{
		for(i=0 ; i<jobCount ; i++){
			f_out ? fprintf(f_write_ptr, "%d ", ansArr[i]) : printf("%d ", ansArr[i]);
		}
	}
	
	fclose(f_read_ptr);
	return 0;
}
