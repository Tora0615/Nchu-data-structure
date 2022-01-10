#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "TestData\\test_case_1-1\\input_1.txt"

typedef struct listNode *listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} ListNode;
int nodeCount = 0;
listPointer first = NULL;	// linked list head
FILE *f_write_ptr;			// if want to use need fopen


int stringToInt(char *contents){
	int index = 0, count = 0, isNegative = FALSE;
	
	/* if not space or line end -> read */
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
	
	// printf("%d\n",count);
	return count;
}

void addToEnd(int data){
	/* node init */
	listPointer temp = (listPointer)malloc(sizeof(ListNode));
	temp->data = data;
	temp->link = NULL;
	
	/* if linked list empty */
	if (!first){ 
		first = temp;
		nodeCount += 1;
	}
	/* not empty */
	else{ 
		listPointer tail = first;
		while(tail->link){
			tail = tail->link;
		}
		tail->link = temp;
		nodeCount += 1;
	}
}


void delFromIndex(int index){
	listPointer target;
	
	/* over range delete */
	if(index < 0 || nodeCount < index ){
		return;
	}
	/* delete head */ 
	else if(index == 0){
		target = first;					// del
		first = first->link;			//  A----B----C----D
		free(target);					//target
		nodeCount -= 1;
	}
	/* delete tail */
	else if(index == nodeCount){
		target = first;					//				  del
		while(target->link->link){		//  A----B----C----D
			target = target->link;		//	 		target
		}
		free(target->link);
		target->link = NULL;
		nodeCount -= 1;
	}
	/* delete in the middle */
	else{
		int i;
		target = first;					//	     target(del) targetNext
		for (i=0; i < index-1; i++) {	//  A-------(B->C)-------C---------D
			target = target->link;		//	  	      |		  	           ^
		}								//		      ------- link --------
		listPointer targetNext = target->link;
		target->data = target->link->data;
		target->link = target->link->link;
		free(targetNext);
		nodeCount -= 1; 
	}
}


void insertAfterIndex(int index, int data){
	/* create node*/
	listPointer temp = (listPointer)malloc(sizeof(ListNode));
	temp->data = data;
	
	/* find position*/
	listPointer target = first;
	int i;
	for (i = 0; i < index-1; i++) {
		target = target->link;
	}
	
	/* insert */
	temp->link = target->link;
	target->link = temp;
	nodeCount += 1;
}

void showLinkedList(void){
	int f_output = FALSE;
	listPointer now = first;
	
	f_output ? fprintf(f_write_ptr,"%d ",now->data) : printf("%d ",now->data);
	while(now->link){
		now = (now->link);
		f_output ? fprintf(f_write_ptr,"%d ",now->data) : printf("%d ",now->data); 
	}
	f_output ? fprintf(f_write_ptr,"\n") : printf("\n");
}

void initLinkedList(char *contents){
	int tempNum = 0, readIndex = -1;
	char charBuf = ' ';
	while (TRUE){
		readIndex += 1;
		charBuf = contents[readIndex];
		/* is space */
		if(charBuf == ' ' ){
			/* add num to linked lst and reset tempNum*/
			addToEnd(tempNum);
			tempNum = 0;
		}
		/* end of line */
		else if(charBuf == '\0' || charBuf == '\r'){
			/* add num to linked lst and reset tempNum*/
			addToEnd(tempNum);
			tempNum = 0;
			break;
		}
		/* maybe is more than one digit's number */
		else{
			tempNum = tempNum * 10 + (charBuf - '0');
		}
	}
}

void multipleFromReverseIndex(int r_count, int mult){
	int index = nodeCount - r_count + 1;
	int i;
	listPointer now = first;
	for (i = 0; i < index-1; i++) {
		now = now->link;
	}
	now->data = (now->data) * mult;
}

void reverseGroupOfXItems(int groupCount){
	
	// operation step
	// 123 456 78 ---relink---> 78 456 123 ---reverseAll---> 321 654 87
	
	/* 1 item a group -> do nothing*/
	if(groupCount == 1){
	    return;
	}
	
	/* count haw many complete group(middlePartCount+1) and remain items(remainItems) */
	int remainItems = nodeCount % groupCount;
	int middlePartCount = nodeCount / groupCount - 1;
	// if divisible, middlePartCount will be one less
	remainItems ? middlePartCount : (middlePartCount -= 1);		
	
	// group's tags (3 item a group) :
	// |  _   _   _   |   _    _    _   |   _    _  ...
	//   pre           ghead     gtail    next
	
	// link situation
	//                                     first (3)
	//                                       |
	//                     -----------(2)----------
	//                     |                 |    |
	//     ------------(1)------------       |    |
	//     |               |         |       |    |
	//     v               V         |       v    |
	//  |  _   _   _   |   _    _    _   |   _    _  ...
	// (1) pre             head      tail   next
	// (2)                 pre              head  tail

	/* three parts : start(1) - middle(0-N) - end(0-1)*/
	// if only hava one group : only do start part
	// if have two group : do start and end part
	// else : tree part 
	
	/*---- relink part ----- */
	listPointer pre = NULL, groupHead = NULL, groupTail = NULL, next = NULL, now = NULL;
	int i,j;
	
	/* start part */
	/* record tags and let groupTail point to NULL*/
	groupHead = first;
	groupTail = first;
	for(i=0; i<groupCount-1; i++){
		groupTail = groupTail->link;
	}
	next = groupTail->link;
	groupTail->link = NULL;
	
	/* middle part */
	/* record tags and let groupTail point to previous group's head*/
	/* if total only have 1 or 2 group (AKA middlePartCount == 0 or 1) will not execute*/
	for(i=0; i<middlePartCount; i++){
		pre = groupHead;
		groupHead = next;
		groupTail = next;
		for(j=0; j<groupCount-1; j++){
			groupTail = groupTail->link;
		}
		next = groupTail->link;
		groupTail->link = pre;
	}
	
	/* end part */
	/* have last part (maybe a complete group or not)*/
	if(next){
		pre = groupHead;
		groupHead = next;
    	groupTail = next;
    	while (groupTail->link) {
	        groupTail = groupTail->link;
	    }
	    groupTail->link = pre;
    	first = groupHead;
	}
	
	//	printf("before reverse : ");
	//	showLinkedList();
	
	/*---- reverse part ----- */
	pre  = NULL;
	now  = first;
	next = first->link;
	
	/* head part (turn to tail)*/		//  A------B------C------D
	now->link = NULL;					// now    next
								
	
	/* body part (reverse link)*/
	while (next->link){					//  A------B------C------D
	    pre = now;						// pre    now    next
	    now = next;
	    next = next->link;
	    now->link = pre;
	}
	
	/* tail part (turn to head)*/
	next->link = now;					//  A------B------C------D
	first = next;						//       pre    now    next
}

void decodeOp(char *contents){
	/* first num position*/
	int startIndex = -1;  
	/* second num position*/
	int secondStartIndex = -1;
	
	/* get first num position*/
	while (!isspace(contents[startIndex++]));

	switch (contents[0]) {
		/* add */
		case 'a':  
		  addToEnd(stringToInt(&contents[startIndex]));
		  break;
		/* delete */
		case 'd':  
		  delFromIndex(stringToInt(&contents[startIndex]));
		  break;
		/* reverse */  
		case 'r':  
		  reverseGroupOfXItems(stringToInt(&contents[startIndex]));
		  break;
		/* show */
		case 's':  
		  showLinkedList();
		  break;
		/* insert */
		case 'i':  
		  secondStartIndex = startIndex;
		  while (!isspace(contents[secondStartIndex++]));
		  insertAfterIndex(
		    stringToInt(&contents[startIndex]),
		    stringToInt(&contents[secondStartIndex])
		  );
		  break;
		/* multiple */
		case 'm':  
		  secondStartIndex = startIndex;
		  while (!isspace(contents[secondStartIndex++]));
		  multipleFromReverseIndex(
		      stringToInt(&contents[startIndex]),
		      stringToInt(&contents[secondStartIndex])
		  );
		  break;
	}
}

int main(void){
	/* open file */
	FILE *f_read_ptr;
	if( !(f_read_ptr = fopen(INPUTFILE,"r")) ){
		printf("Failed to open file");
	}
	
	char endLineBuf = ' ';
	char content[1000];
	
	/* read a line and init linked list*/
	fscanf(f_read_ptr,"%[^\n]",content);
	endLineBuf = fgetc(f_read_ptr); 
	initLinkedList(content);
	content[0] = '\0';
	
	/* get operation count */
	int opCount = 0;
	fscanf(f_read_ptr, "%d\n", &opCount);
  	
  	/* process operations */
	int i;
	for(i=0; i<opCount; i++){
		/* read line */
		fscanf(f_read_ptr,"%[^\n]",content);  
		endLineBuf = fgetc(f_read_ptr); 
		decodeOp(content);
		content[0] = '\0';
	}
	fclose(f_read_ptr);
	return 0;
}
