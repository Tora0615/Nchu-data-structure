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
//char *dict = " !,-.:;?0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";  
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
		printf("frequency : %d, cost : %d, addr : %p\n", head->frequency, head->cost, head);
		head = head->next;
	}
	printf("\n");
}


int getStringCost(char *contents){
	int cost = 0, index = 0;
	
	int elementRecord[asciiLen], i;		// creat an array have 128 element
	for(i=0;i<asciiLen;i++){			// init with zero
		elementRecord[i] = 0;
	}
	
	// count char frequency
	while(contents[index] != '\0' && contents[index] != '\r'){
		int asciiCode = contents[index];
		elementRecord[asciiCode] += 1;
		index++;
	}
	
	//dump element count
//	int temp=0;
//	while(temp<128){
//		if(elementRecord[temp]){
//			printf("%c %d\n",temp,elementRecord[temp]);	
//		}
//		temp+=1;
//	}

	// count non-zero element 
	int elementCount = 0;
	for(i=0;i<asciiLen;i++){			
		if(elementRecord[i]>0){
			elementCount+=1;
		}
	}
	printf("element count : %d\n", elementCount);
	
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
	//return 0;

	int frequency = 1;
	nodePointer pointStack = NULL, pointTemp = NULL;
	while(head->next){
		
 		nodePointer temphead = head;
		nodePointer pre = NULL;
		while(temphead->next){
			dumpLinkedList(head);
			printf("temphead : %p, pre : %p\n",temphead, pre);
			// not equal -> chenk next
			if(temphead->frequency != frequency){
				pre = temphead;
				//temphead = temphead->next;
			}else{		// equal -> del node
				if(temphead == head){
					head = head->next;
					
					if(!pointStack){				// pointStack is empty
						pointStack = temphead;		// move to stack
					}else{
						pointTemp = pointStack;		// stack element move to temp
						pointStack = NULL;			// stack set to empty
						
						// add value
						pointTemp->cost = pointTemp->cost + temphead->cost + pointTemp->frequency + temphead->frequency;
						pointTemp->frequency = pointTemp->frequency + temphead->frequency;
						pointTemp->next = NULL;
						
						// add to tail
						nodePointer tail = head;
						while(tail->next){
							tail = tail -> next;
						}
						tail->next = pointTemp;
						
						// set to 0
						pointTemp = NULL;
						//free(temphead);
					}
				}else{
					pre->next = temphead->next;
					if(!pointStack){				// pointStack is empty
						pointStack = temphead;		// move to stack
					}else{
						pointTemp = pointStack;		// stack element move to temp
						pointStack = NULL;			// stack set to empty
						
						// add value
						pointTemp->cost = pointTemp->cost + temphead->cost + pointTemp->frequency + temphead->frequency;
						pointTemp->frequency = pointTemp->frequency + temphead->frequency;
						pointTemp->next = NULL;
						
						// add to tail
						nodePointer tail = head;
						while(tail->next){
							tail = tail -> next;
						}
						tail->next = pointTemp;
						
						// set to 0
						pointTemp = NULL;
						//free(temphead);
					}
				}
				//elementCount -= 1;
				pre = NULL;
			}
			
			temphead = temphead->next;
		}
		frequency += 1;	
	}
	
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
			for(i=0;i<dataCount;i++){
				fscanf(f_read_ptr,"%[^\n]",contents); 
				endLineBuf = fgetc(f_read_ptr);
				//printf("%s\n",contents);
				cost = cost + getStringCost(contents);
			}
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


