#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 101

typedef struct listNode *listPointer;
struct listNode {
	int data;
	listPointer link;
};

FILE *input;
FILE *output;

int top;
listPointer head, tail;

void show(){
	
	listPointer temp = head;
	while(temp){
		fprintf(output, "%d ", temp->data);
		temp = temp->link;
	}
	fprintf(output, "\n");
	
}

void add(int data){
	
	listPointer next = (listPointer) malloc(sizeof(struct listNode));
	
	next->data = data;
	next->link = NULL;
	
	if(!head) head = next;
	if(tail) tail->link = next;
	
	top++;
	tail = next;
}

void del(int num){

	if(head==NULL)  return;
	
	listPointer now = head, prev = NULL;
	
	while (now!=NULL){
		if (now->data==num && now!=NULL){
			listPointer del;
			del = now;
			now = now->link;
			prev->link = now;
			free(del);
			break;
		}			
		prev = now;
		now = now->link;
	}
	return ;
}

void ins(int num, int data){
	
	if( num <= 0 || num > top)  return;
	
	int i;
	listPointer temp = head, insert = (listPointer) malloc(sizeof(struct listNode));
	
	top++ ;
	
	for(i=1; i<num ; i++, temp = temp->link);
	
	insert->data = data;
	insert->link = temp->link;
	
	temp->link = insert;
	
	if(num == top) tail = insert;
	
}

void mul(int num, int data){
	
	if( num <= 0 || num > top)  return;
	
	int i;
	listPointer temp = head;
	
	num = top - num + 1 ;
	
	for(i=1; i<num ; i++, temp = temp->link);
	
	temp->data *= data;
	
}

listPointer rev(listPointer header, int num){
	
	int i;
	listPointer rear, middle, lead;
	
	rear = NULL;
	middle = NULL;
	lead = header;
	
	for(i=0 ; i<num && lead!=NULL ; i++){
		rear = middle;
		middle = lead;
		lead = lead->link;
		middle->link = rear;
	}
	
	if( i==num && lead!=NULL)
		header->link = rev(lead, num);
	else
		tail = header;
		
	return middle;
	
}

void freeALL(){
	listPointer temp = head;
	while(head){
		head = head->link;
		free(temp);
		temp = head;
	}
}

int main(){
	
	int i, num=0, numCommand, parameterOne, parameterTwo;
	char c, line[max];
	top = 0;
	
	head = NULL;
	tail = NULL;
	
	input = fopen("input_4-5.txt","r");
	output = fopen("output_1.txt","w");
	
	while(1){
		fscanf(input,"%d%c",&num,&c);
		add(num);
		if(c == '\n') break;
	}
	
	fscanf(input,"%d",&numCommand);
	
	for(i=0; i<numCommand; i++){
		
		fscanf(input, "%s", line);
		
		if( !strcmp(line, "add") ){
			fscanf(input, "%d", &parameterOne);
			add(parameterOne);
		}
		else if( !strcmp(line, "del") ){
			fscanf(input, "%d", &parameterOne);
			del(parameterOne);
		}
		else if( !strcmp(line, "ins") ){
			fscanf(input, "%d %d", &parameterOne, &parameterTwo);
			ins(parameterOne, parameterTwo);
		}
		else if( !strcmp(line, "mul") ){
			fscanf(input, "%d %d", &parameterOne, &parameterTwo);
			mul(parameterOne, parameterTwo);
		}
		else if( !strcmp(line, "rev") ){
			fscanf(input, "%d", &parameterOne);
			head = rev(head, parameterOne);
			
		}
		else if( !strcmp(line, "show") ){
			show();
		}
		
	}
	
	freeALL();
	fclose(input);
	fclose(output);
	return 0;
}

