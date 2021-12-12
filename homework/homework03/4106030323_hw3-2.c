#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "Test_case\\test_case_2-1\\input_2.txt"
#define OUTPUTFILE "output_2.txt"

FILE *f_read_ptr;
FILE *f_write_ptr;
int asciiLen = 128;

typedef struct _node *nodePointer;
typedef struct _node {
	int frequency;
	int cost;
	nodePointer next;
}node;

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

void dumpLinkedList(nodePointer head){
	while(head){
		printf("frequency : %d, cost : %d, addr : %p, next : %p\n", head->frequency, head->cost, head, head->next);
		head = head->next;
	}
	printf("\n");
}

void dumpElementRecord(int *elementRecord){
	int i;
	for(i=0;i<asciiLen;i++){			// init with zero
		printf("%c : %d\n",i, elementRecord[i]);
	}
}

void countFrequency(int *elementRecord, char *contents){
	int index = 0;
	// count char frequency
	while(contents[index] != '\0' && contents[index] != '\r'){
		int asciiCode = contents[index];
		elementRecord[asciiCode] += 1;
		index++;
	}
}

nodePointer initLinkedList(int *elementRecord){
	
	// count non-zero element 
	int elementCount = 0, i;
	for(i=0;i<asciiLen;i++){			
		if(elementRecord[i]>0){
			elementCount+=1;
		}
	}
	//printf("element count : %d\n", elementCount);
	
	// save elements to node linked list
	nodePointer head = NULL;
	int j = -1;
	for(i=0;i<elementCount;i++){
		
		// find the non-zero data's index in elementRecord
		while(j<asciiLen){
			j+=1;
			if(elementRecord[j]>0){
				break;
			}
		}
		
		// setup node
		nodePointer temp = (nodePointer)malloc(sizeof(node));
		temp->frequency = elementRecord[j];
		temp->cost = 0;
		temp->next = NULL;
		
		// link
		if(!head){		// head is NULL
			head = temp;
		}else{
			nodePointer temphead = head;
			while(temphead->next){
				temphead = temphead->next;
			}
			temphead->next = temp;
		}
	}
	
	//dumpLinkedList(head);
	return head;
}


int getCost(nodePointer head){
	while(head->next){		// node > 1
		//dumpLinkedList(head);
		int tempFrequency;
		nodePointer nodeA = NULL, nodeB = NULL, preA = NULL, preB = NULL;
		nodePointer tempHead;
		
		// get node A
		tempFrequency = 1;
		while(!nodeA){
			tempHead = head;
			while(tempHead){
				if(tempHead->frequency == tempFrequency){
					nodeA = tempHead;
					break;
				}
				preA = tempHead;
				tempHead = tempHead->next;
			}
			tempFrequency += 1;
		}
		
		// get node B
		tempFrequency = 1;
		while(!nodeB){
			tempHead = head;
			while(tempHead){
				if(tempHead->frequency == tempFrequency && tempHead != nodeA){		// To get different node form nodeA
					nodeB = tempHead;
					break;
				}
				preB = tempHead;
				tempHead = tempHead->next;
			}
			tempFrequency += 1;
		}
		
		//printf("AFreq : %d -- %p, BFreq : %d -- %p\n", nodeA->frequency, nodeA, nodeB->frequency, nodeB);
		//printf("preA : %p, preB : %p\n", preA, preB);
		
		// creat new node and save data
		nodePointer temp = (nodePointer)malloc(sizeof(node));
		temp->cost = nodeA->cost + nodeB->cost + nodeA->frequency + nodeB->frequency;
		temp->frequency = nodeA->frequency + nodeB->frequency;
		temp->next = NULL;
		
				
		// add one node to tail
		tempHead = head;
		while(tempHead->next){
			tempHead = tempHead->next;
		}
		tempHead->next = temp;
		
		// del two node
		if(nodeA == head){			// delete head
			temp = head;
			head = head->next;
			free(temp);
		}else{						// delete body
			temp = nodeA;
			preA->next = nodeA->next;
			free(temp);
		}
		
		if(nodeB == head){			// delete head
			temp = head;
			head = head->next;
			free(temp);
		}else{						// delete body
			temp = nodeB;
			if(preB == nodeA){		// to prove not delete in serial (Continuous deletion will cause errors) 
				preB = preA;		// example : 	3		3		1		1		4		4 
			}						// 				 				A 		B
			preB->next = nodeB->next;	//        		  preA	   preB
			free(temp);
		}
	}
	//dumpLinkedList(head);
	return head->cost;
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
	}/** else {
		f_write_ptr = fopen(OUTPUTFILE,"w");
	}**/
	
	char endLineBuf = ' ';
	char contents[10000];
	
	while(TRUE){
		fscanf(f_read_ptr,"%[^\n]",contents); 
		endLineBuf = fgetc(f_read_ptr);
		int dataCount = stringToInt(contents);
		if(dataCount){				// bigger than 0
			int i, cost = 0;
			
			
			int elementRecord[asciiLen];		// creat an array have 128 element
			for(i=0;i<asciiLen;i++){			// init with zero
				elementRecord[i] = 0;
			}
			
			for(i=0;i<dataCount;i++){
				fscanf(f_read_ptr,"%[^\n]",contents); 
				endLineBuf = fgetc(f_read_ptr);
				countFrequency(elementRecord, contents);
			}
			
			//dumpElementRecord(elementRecord);
			nodePointer head = initLinkedList(elementRecord);
			cost = getCost(head);
			
			printf("%d\n\n",cost);
		}else{
			break;
		}
	}
	
	fclose(f_read_ptr);
	fclose(f_write_ptr);
	printf("Complete !\n");
	return 0;
}


