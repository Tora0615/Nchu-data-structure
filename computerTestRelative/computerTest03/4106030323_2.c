#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "TestData\\test_case_2-1\\input_2.txt"


FILE *f_read_ptr;
FILE *f_write_ptr;
int asciiLen = 128;

typedef struct _node *nodePointer;
typedef struct _node {
	int frequency;
	int cost;
	nodePointer next;
}node;

void countFrequency(int *frequencyList, char *contents){
	int index = 0;
	while(contents[index]!='\n' && contents[index]!='\r' && contents[index]!='\0'){
		/* get char's ascii code */
		int asciiCode = contents[index];
		/* it position's value add one*/
		frequencyList[asciiCode] += 1;
		index += 1;
	}
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

nodePointer initLinkedList(int *frequencyList){
	int i;
	nodePointer head = NULL;
	
	for(i=0; i<asciiLen; i++){
		if(frequencyList[i] > 0){
			/* create a node */
			nodePointer temp = (nodePointer)malloc(sizeof(node));
			temp->frequency = frequencyList[i];
			temp->cost = 0;
			temp->next = NULL;
			
			/* let node link to linked list */
			if(!head){	
				head = temp;
			}else{
				/* find tail node */
				nodePointer tail = head;
				while(tail->next){
					tail = tail->next;
				}
				/* link to tail */
				tail->next = temp;
			}
		}
	}
	// dumpLinkedList(head);
	return head;
}


int getCost(nodePointer head){
	/* will keep combine two minimun frequence node to one */
	/* the two node will be delete, the new node will add to tail */
	/* until remain only node, the loop will stop */
	
	/* node more than one -> keep doing*/
	while (head->next){ 
		/* Frequency at least is 1 */
		int targetFrequency = 1;
		
		/* find node A*/
		nodePointer nodeA = NULL;
		nodePointer preA = NULL;
		while(!nodeA){
			nodePointer tempHead = head;
			/* use tempHead see all linked list's node's frequency*/
			while(tempHead){
				/* find -> set value */
				if(tempHead->frequency == targetFrequency){
					nodeA = tempHead;
					break;
				}
				/* dont find -> move to next, untill meet NULL */
				else{
					preA = tempHead;
					tempHead = tempHead->next;
				}
			}
			/* see once dont have -> frequency add and do again */
			targetFrequency += 1;
		}
		
		/* reset frequency */
		targetFrequency = 1;

		/* find node B*/
		nodePointer nodeB = NULL;
		nodePointer preB = NULL;
		while(!nodeB){
			nodePointer tempHead = head;
			/* use tempHead see all linked list's node's frequency*/
			while(tempHead){
				/* find -> set value, NEED DIFFERENT FROM NODE A*/
				if(tempHead->frequency == targetFrequency && tempHead != nodeA){
					nodeB = tempHead;
					break;
				}
				/* dont find -> move to next */
				else{
					preB = tempHead;
					tempHead = tempHead->next;
				}
			}
			/* see once dont have -> frequency add and do again */
			targetFrequency += 1;
		}
		
		/* creat new node to save combined data*/
		nodePointer temp = (nodePointer)malloc(sizeof(node));
		temp->cost = nodeA->cost + nodeB->cost + nodeA->frequency + nodeB->frequency;	// new cost = old (frequency & cost) + old (frequency & cost)
		temp->frequency = nodeA->frequency + nodeB->frequency;							// new frequency = old frequency + old frequency
		temp->next = NULL;
		
		/* find tail and link new node to tail */
		nodePointer tail = head;
		while(tail->next){
			tail = tail->next;
		}
		tail->next = temp;
		
		/* delete nodeA*/
		if(nodeA == head){			// is head
			temp = head;
			head = head->next;
			free(temp);
		}else{						// is body
			temp = nodeA;
			preA->next = nodeA->next;
			free(temp);
		}
		
		/* delete nodeB*/
		if(nodeB == head){			// delete head
			temp = head;
			head = head->next;
			free(temp);
		}else{						// delete body
			temp = nodeB;
			if(preB == nodeA){		// delete in serial
				preB = preA;		
			}						
			preB->next = nodeB->next;	
			free(temp);
		}
		
		// to prove not delete in serial (Continuous deletion will cause errors)
		// example : 	3		3		1		1		4		4
		// 				 				A 		B
		// error case :		  preA	   preB
		// fix case : 		preA/preB
	}
	
	/* return value */
	return head->cost;
}

int main(){
	if ( !(f_read_ptr = fopen(INPUTFILE,"r")) ){
		printf("Cannot open file : %s\n", INPUTFILE);
	}
	
	/* keep reading untill read 0*/
	int dataCount;
	char charBuf = ' ';
	char *contents = (char*)malloc(sizeof(char)*20000);
	while(TRUE){
		fscanf(f_read_ptr, "%d\n", &dataCount);
		/* dataCount not 0*/
		if(dataCount){
			int i;
			
			/* creat a asciiLen size's frequencyList, to save char's show frequency*/
			int frequencyList[asciiLen];
			for(i=0; i<asciiLen; i++){
				/* init value to zero*/
				frequencyList[i] = 0;
			}
			
			/* read a line and count frequency, result will save to */
			for(i=0; i<dataCount; i++){
				/* read line*/
				fscanf(f_read_ptr,"%[^\n]",contents);
				charBuf = fgetc(f_read_ptr);
				/* count */
				countFrequency(frequencyList, contents);
				/* clean char array */
				contents[0] = '\0';
			}
			
			/* create a linked list */
			nodePointer head = initLinkedList(frequencyList);
			
			/* calculate total cost  */
			int cost = getCost(head);
			
			/* print answer */
			printf("%d\n", cost);
		}
		/* dataCount is 0*/
		else{
			break;
		}
	}
	fclose(f_read_ptr);
	return 0;
}
